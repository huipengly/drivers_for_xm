/************************************************************
  Copyright (C), 2015 - 2015, ZhA.
  FileName: main.c
  Author: NaTel   Version : 0.0      Date: 2015/08/04
  Description: ��������    // ģ������     
  Version:   // �汾��Ϣ
  Function List:   // ��Ҫ�������书��
    1. 
  History:         // ��ʷ�޸ļ�¼
      <author>  <time>   <version >   <desc>
      David    96/10/12     1.0     build this moudle 
***********************************************************/
  
#include "stm32f10x.h"
#include "Key.h"
#include "delay.h"
#include "nokia_5110.h"

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
	Key_GPIO_Init();
	delay_init(72);
	LCD_init();
	LCD_write_chinese_string(2,0,12,3,0,2);
	while(1)
	{	key = Key_Scan();
		if( KEY_CANCLE == key )
		{
			LCD_clear();
			LCD_write_english_string(45,0,"CANCLE");
		}
		if( KEY_NEXT == key )
		{
			LCD_clear();
			LCD_write_english_string(45,0,"NEXT");
		}
		if( KEY_OK == key )
		{
			LCD_clear();
			LCD_write_english_string(45,0,"OK");
		}
		LCD_write_chinese_string(2,0,12,3,0,2);
	}
}

/*********************************************END OF FILE**********************/
