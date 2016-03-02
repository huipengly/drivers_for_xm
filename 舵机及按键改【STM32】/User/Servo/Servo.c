/************************************************************
  Copyright (C), 2015 - 2016, ZhA.
  FileName: Servo.c
  Author: NaTel   Version : 0.1      Date: 2015/08/12
  Description: ������ƣ����GPIOΪPA0    // ģ������
  Version:0.1   // �汾��Ϣ
  Function List:   // ��Ҫ�������书��
    1. void Servo_position(int32_t sangle) 
		//���λ������
	2. void Servo_GPIO_Config(void)
		//���GPIO����
	3. void	Servo_Mode_Config(void);
		//���PWMģʽ����
	4. void Servo_Init(void)
		//�����ʼ��
  History:         // ��ʷ�޸ļ�¼
      <author>  <time>   <version >   <desc>
      David    96/10/12     1.0     build this moudle 
***********************************************************/

#include "stm32f10x.h"
#include "include.h"

/*************************************************
  Function: Servo_position   // ��������
  Description: ����Ƕȿ���
                                  // �������ܡ����ܵȵ�����
  Calls: 
   1.----?   // �����������õĺ����嵥
  Others:         // ����˵��
*************************************************/
void Servo_position(int32_t sangle)
{
	if ( sangle > 180 )
		sangle = 179;
	if ( sangle < 0 )
		sangle = 1;
	TIM3->CCR3 = ( ((float)sangle / 180) ) * 2000 + 499;//��0-180����ת��Ϊʱ��0.5ms~2.5ms
}

 /**
  * @brief  ����PWM��I/O��PWM�����I/O�ڰ���PA0
  * @param  ��
  * @retval ��
  */
void Servo_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ����TIM3CLK Ϊ 72MHZ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/* GPIOA clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	/*GPIOA Configuration: TIM2 channel 1 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*************************************************
  Function: PWM_Mode_Config   // ��������
  Description: PWM��ʼ������
                                  // �������ܡ����ܵȵ�����
  Calls: 
   1.----?   // �����������õĺ����嵥
  Others:         // ����˵��
*************************************************/
void Servo_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  /* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 20000-1;       //����ʱ����0������19999����Ϊ20000�Σ�Ϊһ����ʱ����
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;	    //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//���ö�ʱ��2

  /* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse = 1499;	   //��������ֵ�������������������ֵʱ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��valueʱΪ�ߵ�ƽ
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);	 //ʹ��ͨ��1
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_Cmd(TIM2, ENABLE); //ʹ�ܶ�ʱ��3
}

/******************************
������Ƴ�ʼ��
******************************/

void Servo_Init(void)
{
	Servo_GPIO_Config();
	Servo_Mode_Config();
}

/*********************************************END OF FILE**********************/
