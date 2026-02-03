/*
 * user_led.c
 *
 *  Created on: Jan 12, 2026
 *  Author: rony paul chakiyath
 */


#include "user_led.h"

#define GPIO_D_EN	(1<<3)
#define LED_ON		(1<<13)
#define LED_OFF		(~(1<<13))


void led_init(void)
{
	/*enable clock to the GPIO PORT */
	RCC->AHB1ENR |= GPIO_D_EN;
	/*set LED conected to PD13 as output*/
	GPIOD->MODER |=(1<<26);
	GPIOD->MODER &= (~(1<<27));
}

void led_on(void)
{
	/*set LED 3 (PD13) on discovery board high*/
	GPIOD->ODR |= LED_ON;
}

void led_off(void)
{
	/*set LED 3 (PD13) on discovery board low*/
	GPIOD->ODR &= LED_OFF;
}
