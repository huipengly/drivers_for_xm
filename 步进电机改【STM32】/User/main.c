#include "stm32f10x.h"
#include "stepping_motor.h"
int main(void)
{
//	SystemInit();
	uint32_t i;
	stepping_motor_Init();
	
		for( i = 0xffff; i > 0; i--);
	stepping_motor_step_change( 10, 1, 0, 1, 2, -1 );

	
	while(1)
	{
//		GPIO_SetBits(GPIOB, GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
		for( i = 0xffff; i > 0; i--);
		stepping_motor_step_change( 10, -1, 5, 1, 2, -1 );
//		GPIO_ResetBits(GPIOB, GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
//		for( i = 0xffff; i > 0; i--);
	}
}
