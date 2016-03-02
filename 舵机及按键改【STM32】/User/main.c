/************************************************************
  Copyright (C), 2015 - 2016, ZhA.
  FileName: main.c
  Author: NaTel   Version : 1.0      Date: 2016/01/19
  Description: �������     // ģ������     
  Version:   // �汾��Ϣ
  Function List:   // ��Ҫ�������书��
    1. 
  History:         // ��ʷ�޸ļ�¼
      <author>  <time>   <version >   <desc>
      David    96/10/12     1.0     build this moudle 
***********************************************************/
  
#include "stm32f10x.h"
#include "Key.h"
#include "Servo.h"
#include "delay.h"

/*************************************************
  Function:main       // ��������
  Description:������    // �������ܡ����ܵȵ�����
  Calls:          // �����������õĺ����嵥
  Called By:      // ���ñ������ĺ����嵥
  Input:          // �������˵��������ÿ����������
                  // �á�ȡֵ˵�����������ϵ��
  Output:         // �����������˵����
  Return:         // ��������ֵ��˵��
  Others:         // ����˵��
*************************************************/
int main(void)
{
	uint8_t key;
	int32_t angle;
	angle = 90;
	delay_init(72);
	Key_GPIO_Init();
	Servo_Init();
	while(1)
	{
		key = Key_Scan();
		if( KEY_CANCLE == key )
		{
			angle += 5;
		}
		if( KEY_NEXT == key )
		{
			angle = 90;
		}
		if( KEY_OK == key )
		{
			angle -= 5;
		}
		Servo_position(angle);
	}
}

/*********************************************END OF FILE**********************/

