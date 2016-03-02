/************************************************************
  Copyright (C), 2015 - 2015, ZhA.
  FileName: main.c
  Author: NaTel   Version : 0.0      Date: 2015/08/04
  Description: 按键驱动    // 模块描述     
  Version:   // 版本信息
  Function List:   // 主要函数及其功能
    1. 
  History:         // 历史修改记录
      <author>  <time>   <version >   <desc>
      David    96/10/12     1.0     build this moudle 
***********************************************************/
  
#include "stm32f10x.h"
#include "Key.h"
#include "delay.h"
#include "nokia_5110.h"

/*************************************************
  Function:main       // 函数名称
  Description:主函数    // 函数功能、性能等的描述
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Input:          // 输入参数说明，包括每个参数的作
                  // 用、取值说明及参数间关系。
  Output:         // 对输出参数的说明。
  Return:         // 函数返回值的说明
  Others:         // 其它说明
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
