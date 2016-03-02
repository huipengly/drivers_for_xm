/************************************************************
  Copyright (C), 2015 - 2015, ZhA.
  FileName: usart3.c
  Author: NaTel   Version : 0.1      Date: 2016/01/18
  Description: �����趨    
			   Ӳ������ �� PB10 TX  PB11 RX // ģ������     
  Version:1.0         // �汾��Ϣ
  Function List:   // ��Ҫ�������书��
    1. void USART_NVIC_Configuration(void)
		//
	2. void USART3_Config(void)
		//USART1 GPIO ����,����ģʽ����
	3. int fputc(int ch, FILE *f)
		�ض���c�⺯��printf��USART3
  History:         // ��ʷ�޸ļ�¼
      <author>  <time>   <version >   <desc>
      David    96/10/12     1.0     build this moudle 
***********************************************************/

#include "stm32f10x.h"
#include "usart3.h"

void USART_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/*
 * ��������USART3_Config
 * ����  ��USART3 GPIO ����,����ģʽ����
			115200 
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void USART3_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	/* config USART3 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	/* USART3 GPIO config */
	/* Configure USART1 Tx (PB.10) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);    
	/* Configure USART1 Rx (PB.11) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* USART3 mode config */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART3, ENABLE);
	
	USART_NVIC_Configuration();
}


/*
 * ��������fputc
 * ����  ���ض���c�⺯��printf��USART3
 * ����  ����
 * ���  ����
 * ����  ����printf����
 */
int fputc(int ch, FILE *f)
{
	/* ��Printf���ݷ������� */
	USART_SendData(USART3, (unsigned char) ch);
	while (!(USART3->SR & USART_FLAG_TXE));
	
	return (ch);
}

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

