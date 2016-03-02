/************************************************************
  Copyright (C), 2015 - 2016, ZhA.
  FileName: Servo.c
  Author: NaTel   Version : 0.1      Date: 2015/08/12
  Description: 舵机控制，舵机GPIO为PA0    // 模块描述
  Version:0.1   // 版本信息
  Function List:   // 主要函数及其功能
    1. void Servo_position(int32_t sangle) 
		//舵机位置设置
	2. void Servo_GPIO_Config(void)
		//舵机GPIO设置
	3. void	Servo_Mode_Config(void);
		//舵机PWM模式设置
	4. void Servo_Init(void)
		//舵机初始化
  History:         // 历史修改记录
      <author>  <time>   <version >   <desc>
      David    96/10/12     1.0     build this moudle 
***********************************************************/

#include "stm32f10x.h"
#include "include.h"

/*************************************************
  Function: Servo_position   // 函数名称
  Description: 舵机角度控制
                                  // 函数功能、性能等的描述
  Calls: 
   1.----?   // 被本函数调用的函数清单
  Others:         // 其它说明
*************************************************/
void Servo_position(int32_t sangle)
{
	if ( sangle > 180 )
		sangle = 179;
	if ( sangle < 0 )
		sangle = 1;
	TIM3->CCR3 = ( ((float)sangle / 180) ) * 2000 + 499;//将0-180度数转换为时间0.5ms~2.5ms
}

 /**
  * @brief  配置PWM的I/O，PWM输出的I/O口包括PA0
  * @param  无
  * @retval 无
  */
void Servo_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 设置TIM3CLK 为 72MHZ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/* GPIOA clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/*GPIOA Configuration: TIM2 channel 1 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*************************************************
  Function: PWM_Mode_Config   // 函数名称
  Description: PWM初始化设置
                                  // 函数功能、性能等的描述
  Calls: 
   1.----?   // 被本函数调用的函数清单
  Others:         // 其它说明
*************************************************/
void Servo_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  /* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 20000-1;       //当定时器从0计数到19999，即为20000次，为一个定时周期
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;	    //设置预分频：不预分频，即为72MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频(这里用不到)
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//配置定时器2

  /* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse = 1499;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于value时为高电平
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);	 //使能通道1
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_Cmd(TIM2, ENABLE); //使能定时器3
}

/******************************
舵机控制初始化
******************************/

void Servo_Init(void)
{
	Servo_GPIO_Config();
	Servo_Mode_Config();
}

/*********************************************END OF FILE**********************/
