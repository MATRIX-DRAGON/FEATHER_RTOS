/*
 * user_uart.c
 *
 *  Created on: Jan 12, 2026
 *  Author: rony paul chakiyath
 */
#include <stdio.h>
#include "user_uart.h"

#define GPIO_A_EN			(1<<0)
#define USART_2_EN			(1<<17)
#define SYS_FREQ			(16000000)
#define APB1_CLK			SYS_FREQ
#define UART_BAUDRATE 		(115200)
#define UART_CR1_TE			(1<<3)
#define UART_CR1_EN			(1<<13)
#define UART_SR_TXE_FLG     (1<<7)

static uint32_t uart_compute_br(uint32_t PERI_clk,uint32_t BD_rate);
static void set_uart_baudrate(uint32_t PERI_clk,uint32_t BD_rate);
static void uart_write(int msg);

int __io_putchar(int msg)
{
	/*this will be called inside printf*/
	uart_write(msg);
	return msg ;
}

/*we will have to map PA2 AF register for USART2 periferal*/
void uart_tx_init(void)
{
	/*enable clock access to GPIO port A */
	RCC->AHB1ENR |= GPIO_A_EN;

	/*enable the AF for PA4 */
	GPIOA->MODER &= (~(1<<4));
	GPIOA->MODER |= (1<<5);

	/*set alternate function type as AF7 for PA2 for UART2_TX*/
	GPIOA->AFR[0] |= (1<<8);
	GPIOA->AFR[0] |= (1<<9);
	GPIOA->AFR[0] |= (1<<10);
	GPIOA->AFR[0] &= (~(1<<11));

	/*enable clock access to USART2*/
	RCC->APB1ENR |=USART_2_EN;

	/*configure baudrate*/
	set_uart_baudrate(APB1_CLK,UART_BAUDRATE);

	/*configure TX direction and reset all other registers*/
	USART2->CR1 = UART_CR1_TE;

	/*enable the UART Module*/
	USART2->CR1 |=UART_CR1_EN;

}

static uint32_t uart_compute_br(uint32_t PERI_clk,uint32_t BD_rate)
{
	return ((PERI_clk+(BD_rate/2))/BD_rate);
}

static void set_uart_baudrate(uint32_t PERI_clk,uint32_t BD_rate)
{
	USART2->BRR = uart_compute_br(PERI_clk,BD_rate);
}

static void uart_write(int msg)
{
	/*make sure the UART TX data register is empty*/
	while(!(USART2->SR & UART_SR_TXE_FLG)){}

	/*write to UART transmit data register*/
	USART2->DR = (msg & 0xFF);
}
