/*
 * user_os_kernal.c
 *
 *  Created on: Jan 21, 2026
 *  Author: rony paul chakiyath
 */
/*most of this is done in referance to ARM CORTEX-M GENERIC USER GUIDE (EXEPTION MODEL)*/

#include"user_os_kernal.h"

#define NUM_OF_THREADS		(3)
#define STACK_SIZE			(256)		//256 *32 bit  => 1024 Bytes
#define BUS_FREQUENCY       (16000000)

#define CLK_CTRL_EN			(1<<0)
#define CLK_CTRL_INT		(1<<1)
#define CLK_CTRL_SRC		(1<<2)			//internal clock source
#define CLK_CTRL_CNT		(1<<16)
#define CLK_CTRL_REST		(0)

#define INTCTRL				(*((volatile uint32_t*)0xE000ED04)) // the address of ICSR form ARM M4 TRM
#define PENDSTEN			(1<<26)//This sets the pending interupt for systick in ICSR register


uint32_t milli_s_prescaler ;
void os_scheduler_launch(void);

typedef struct tcb
{
	int32_t *stackpt;
	struct tcb *nextpt;

}tcb_type;

tcb_type tcbs[NUM_OF_THREADS];
tcb_type *currentpt;

/*each task with a stack size of 400 Bytes*/
int32_t tcb_stack[NUM_OF_THREADS][STACK_SIZE];

/*
 * this is how each of the kernel stack for each tasks will be
-------------------------------------------------
| xPSR            |  ← hardware stacked         |
| PC              |                              |
| LR              |                              |
| R12             |                              |
| R3              |                              |
| R2              |                              |
| R1              |                              |
| R0              |                              |
-------------------------------------------------
| R11             |  ← software stacked         |
| R10             |                              |
| R9              |                              |
| R8              |                              |
| R7              |                              |
| R6              |                              |
| R5              |                              |
| R4              |                              |
-------------------------------------------------
↓  PSP (saved in TCB_A) will be pointing to R4
   since it will be lowest adress from top
   and that will be where the sp will point last

*/
void os_kernal_stack_init(int i)
{
	/*PSP will be pointing to adress of R4.*/
	tcbs[i].stackpt = &tcb_stack[i][STACK_SIZE-16];

	/*set bit 21 (T-bit) in PSR to 1 , to operate in thump mode*/
	tcb_stack[i][STACK_SIZE-1] = (1<<24);//tcb_stack[i][STACK_SIZE-1] will be PSR.

	/*the below initialisation is not mandatory*/

	// tcb_stack[i][STACK_SIZE-2] will be PC which has to be selectively initialised

	tcb_stack[i][STACK_SIZE-3]  = 0xAAAAAAAA;   //R14 aka  LR    (return address / debug pattern)
	tcb_stack[i][STACK_SIZE-4]  = 0xAAAAAAAA;   // R12
	tcb_stack[i][STACK_SIZE-5]  = 0xAAAAAAAA;   // R3
	tcb_stack[i][STACK_SIZE-6]  = 0xAAAAAAAA;   // R2
	tcb_stack[i][STACK_SIZE-7]  = 0xAAAAAAAA;   // R1
	tcb_stack[i][STACK_SIZE-8]  = 0xAAAAAAAA;   // R0

	/* ---- Software-stacked registers (saved by PendSV) ---- */

	tcb_stack[i][STACK_SIZE-9]  = 0xAAAAAAAA;   // R11
	tcb_stack[i][STACK_SIZE-10] = 0xAAAAAAAA;   // R10
	tcb_stack[i][STACK_SIZE-11] = 0xAAAAAAAA;   // R9
	tcb_stack[i][STACK_SIZE-12] = 0xAAAAAAAA;   // R8
	tcb_stack[i][STACK_SIZE-13] = 0xAAAAAAAA;   // R7
	tcb_stack[i][STACK_SIZE-14] = 0xAAAAAAAA;   // R6
	tcb_stack[i][STACK_SIZE-15] = 0xAAAAAAAA;   // R5
	tcb_stack[i][STACK_SIZE-16] = 0xAAAAAAAA;   // R4

}

uint8_t os_kernal_add_thread(void(*thread0)(void),void(*thread1)(void),void(*thread2)(void))
{
	/*disable global interupt*/
	__disable_irq();

	/*in the create TCB for each tasks link one threads
	 * tcb to anothers next to crate a circular link list*/
	tcbs[0].nextpt = &tcbs[1];
	tcbs[1].nextpt = &tcbs[2];
	tcbs[2].nextpt = &tcbs[0];

	/*initialising thread_0*/
	os_kernal_stack_init(0);
	/*let us initialise the pc of thread_0 in its corresponding stack frame*/
	tcb_stack[0][STACK_SIZE-2]= (uint32_t)thread0;


	/*initialising thread_1*/
	os_kernal_stack_init(1);
	/*let us initialise the pc of thread_1 in its corresponding stack frame*/
	tcb_stack[1][STACK_SIZE-2]= (uint32_t)thread1;

	/*initialising thread_2*/
	os_kernal_stack_init(2);
	/*let us initialise the pc of thread_2 in its corresponding stack frame */
	tcb_stack[2][STACK_SIZE-2]= (uint32_t)thread2	;

	/*currentpt is assigned with the adres of thread_0 to start with thread_0 */
	currentpt = &tcbs[0];

	/*enable global interupt*/
	__enable_irq();

	return 1;

}

void os_kernel_init(void)
{
	milli_s_prescaler=(BUS_FREQUENCY/1000);

}

void os_kernal_lanch(uint32_t quanta)
{
	/*reset sys-tik*/
	SysTick->CTRL =CLK_CTRL_REST;
	/*clear sys-tick current value register*/
	SysTick->VAL =0;
	/*load quanta*/
	SysTick->LOAD = (quanta * milli_s_prescaler)-1;

	/*set sys-tick to low priority*/
	NVIC_SetPriority(SysTick_IRQn,15);

	/*enable sys-tick*/
	SysTick->CTRL |= CLK_CTRL_EN;

	/*select internal clock source*/
	SysTick->CTRL |= CLK_CTRL_SRC;

	/*enable interrupt*/
	SysTick->CTRL |= CLK_CTRL_INT;

	/*launch sheduler*/
	os_scheduler_launch();

}

__attribute__((naked))void SysTick_Handler(void)
{
	/*the folowing asembly code will be writen wrt GNU ASSEMBLY PROGRAMING FOR ARM */
	/*when exception occurs (stack frame)
	 * r0,r1,r2,r3,r12,LR,PSR
	 *  are automatically pushed to stack */

	//////*suspend and save the currend thread*//////

	/*disable global interupt*/
	__asm("CPSID I");
	/*save r4,r5,r6,r7,r8,r9,r10,r11*/
	__asm("push {R4-R11}");
	/*load address of currentpt into r0*/
	__asm("LDR R0,=currentpt");
	/*load r1 from address equals r0 , i.e. r1=currentpt */
	__asm("LDR R1,[R0]");
	/*store cortex-M SP at address equals r1 ,i.e. save SP into tcb*/
	__asm("STR SP,[R1]");

	//////*now to choose and load the next thread*///////

	/*load r1 from a location 4-bytes above address r1 , i.e. r1=currentpt->next */
	__asm("LDR R1,[R1,#4]");
	/*store r1 at address equals r0, i.e. currentpt = r1 */
	__asm("STR R1,[R0]");
	/*load cortex-m SP from address equals r1, i.e. SP= currentpt->stackpt */
	__asm("LDR SP,[R1]");
	/*restore r4,r5,r6,r7,r8,r9,r10,r11 from the given task stack*/
	__asm("POP {R4-R11}");
	/*enable global interupts*/
	__asm("CPSIE I");

	//////*return from exeption and restore r0,r1,r2,r3,r12,LR,PSR *//////
	__asm("BX LR");
}

__attribute__((naked))void os_scheduler_launch(void)
{
	/*load address of currentpt into r0*/
	__asm("LDR R0,=currentpt");
	/*load r2 from address r0, i.e. r2=currentpt  */
	__asm("LDR R2,[R0]");
	/*load cortex-M SP from address equals r2  , i.e. SP = currentpt->stackpt */
	__asm("LDR SP,[R2]");
	/*restore r4,r5,r6,r7,r8,r9,r10,r11 from the given task stack*/
	__asm("POP {R4-R11}");
	/*restore r12 ir LR */
	__asm("POP {R12}");
	/*restore r0,r1,r2,r3 */
	__asm("POP {R0-R3}");
	/*skip LR */
	__asm("ADD SP,SP,#4");
	/*create a new start location by poping LR */
	__asm("POP {LR}");
	/*skip PSR by adding 4 to SP*/
	__asm("ADD SP,SP,#4");
	/*enable global interupts*/
	__asm("CPSIE I");
	/*return from exeption */
	__asm("BX LR");

}

void os_thread_yeald(void)
{
	/*clear sys-tick current value register*/
	SysTick->VAL =0;

	/*triger systick interupt before it hits the counter value to basically call the handler to context switch */
	INTCTRL = PENDSTEN;


}

void os_spinlock_init(uint32_t *spinlock,uint32_t value)
{
	*spinlock=value;
}

void os_spinlock_set(uint32_t *spinlock)
{
	__disable_irq();
	*spinlock += 1;
	__enable_irq();
}

void os_spinlock_wait(uint32_t *spinlock)
{
	__disable_irq();
	while(*spinlock <= 0)
	{
		__disable_irq();
		__enable_irq();
	}
	*spinlock -= 1;
	__enable_irq();
}
