#include "stdlib.h"
#include "user_led.h"
#include "user_uart.h"
#include"user_os_kernal.h"

volatile int task_profile_a,task_profile_b,task_profile_c;
uint32_t spinlock_1;
uint32_t spinlock_2;
uint32_t spinlock_3;

volatile int i=0;
void user_thread_a(void)
{
	while(1)
		{
			os_spinlock_wait(&spinlock_1);
			task_profile_a++;
			led_on();
			i=0;
			while(i<1000)
			{
				i++;
			}

			printf("led ON thread a running \n\r");
			os_spinlock_set(&spinlock_2);
			//os_thread_yeald();

		}

}
void user_thread_b(void)
{
	while(1)
		{
		    os_spinlock_wait(&spinlock_2);
			task_profile_b++;
			led_off();
			i=0;
			while(i<1000)
			{
				i++;
			}

			printf("led OFF task b running  \n\r");
			os_spinlock_set(&spinlock_3);
			//os_thread_yeald();
		}

}
void user_thread_c(void)
{
	while(1)
		{
			os_spinlock_wait(&spinlock_3);
			task_profile_c++;
			led_on();
			i=0;
			while(i<1000)
			{
				i++;
			}

			printf("led ON task c running \n\r");
			os_spinlock_set(&spinlock_1);
			//os_thread_yeald();

		}

}

int main()
{
	led_init();
	uart_tx_init();

	os_spinlock_init(&spinlock_1,1);
	os_spinlock_init(&spinlock_2,0);
	os_spinlock_init(&spinlock_3,0);

	/*initialise the kernal*/
	os_kernel_init();
	/*add three threads*/
	os_kernal_add_thread(user_thread_a,user_thread_b,user_thread_c);
	/*set round robin time quanta*/
	os_kernal_lanch(2);//10 ms is set now

	while(1)
	{
		//the code is not supposed to come here
	}
}
