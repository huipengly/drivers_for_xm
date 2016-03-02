#ifndef _SERVO_H
#define _SERVO_H

#include "stm32f10x.h"

void Servo_position(int32_t sangle);
void Servo_Init(void);
void Servo_GPIO_Config(void);
void Servo_Mode_Config(void);

#endif	/*_SERVO_H*/
