/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
/*************************************************
  Function: USART3_IRQHandler      // ��������
  Description:  ����3�жϣ��Է��͵����ݽ��д���
				�������룺
				FF AA 00 00 00 00 00 00 00 00 00
				֡��ʽ:
				FF AA ֡ͷ
				00 00 Rotation
				00 00 Stretch
				00 00 Height
				00 00 hand angle
				00 Grab 01 Release 02 Catch
                                  // �������ܡ����ܵȵ�����
  Calls: 
   1.printf//�����յ������������ʵ��ʹ��ʱ��ɾ��    
								// �����������õĺ����嵥
  Others:         // 
*************************************************/

#include "usart3.h"

uint8_t ustart_0 = 0;//��¼�������ݴ��������������־FF
uint8_t ustart_1 = 0;//��¼�������ݴ��������������־AA
extern uint8_t position_state[11];//�洢���ڷ��͵�λ��״̬
uint8_t usart_i = 0;//��¼�������ݽ�����Ŀ

void USART3_IRQHandler(void)
{
	u8 c;//c�����洢���ڽ��ܵ����ַ���i��������
	int i;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		c=USART3->DR;
		
		if ( (1 == ustart_0) && (1 == ustart_1) )//�洢֡��Ϣ
		{
			position_state[usart_i] = c;
			usart_i++;
			if (11 == usart_i)
			{
				usart_i = 0;
				ustart_0 = ustart_1 = 0;
				for (i = 0; i < 11; i++)
				{
					printf( "%c", position_state[i]);//�����֡����
				}
			}
		}
		
		if ( (0 == usart_i) && (1 == ustart_0) && (0 == ustart_1) )//�ж�֡ͷ�ڶ��ֽ�
		{
			if ( 0xAA == c )
			{
				ustart_1 = 1;
				position_state[0] = 0xFF;
				position_state[1] = 0xAA;
				usart_i = 3;
			}
			if ( 0xAA != c )
			{
				ustart_0 = 0;
				usart_i = 0;
			}
		}//end of if ( 1 == ustart_0 )

		if ( (0xFF == c) && (0 == usart_i) )//�ж�֡ͷ��һ�ֽ�
		{
			ustart_0 = 1;//��־����ͨ�����ݿ�ʼ
		}
	}
}


/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
