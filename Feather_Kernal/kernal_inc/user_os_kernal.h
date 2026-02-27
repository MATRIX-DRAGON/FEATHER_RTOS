/*
 * user_os_kernal.h
 *
 *  Created on: Jan 21, 2026
 *  Author: rony paul chakiyath
 */

#ifndef USER_OS_KERNAL_H_
#define USER_OS_KERNAL_H_

#include<stdint.h>
#include "stm32f4xx.h"

extern void os_kernel_init(void);

/*this is where we add new tasks and allocate the stack area and TCB for each */
extern uint8_t os_kernal_add_thread(void(*thread0)(void),void(*thread1)(void),void(*thread2)(void));

/*this is to set the time quanta in the sys-tick reload value register*/
extern void os_kernal_lanch(uint32_t quanta);

/*yield will allow the systic raise a pending interupt and hence
 *  engaging the systick-handler prior to the count hiting the
 *  reload value (Time quanta in case of RR scheduling) */
extern void os_thread_yeald(void);

/*this is to initialize a semaphore by passing a value */
extern void os_spinlock_init(uint32_t *spinlock,uint32_t value);

/*this is to set a semaphore while a spinlock has to be made*/
extern void os_spinlock_set(uint32_t *spinlock);

/*this is to wait while the semaphore is locked*/
extern void os_spinlock_wait(uint32_t *spinlock);


#endif /* USER_OS_KERNAL_H_ */
