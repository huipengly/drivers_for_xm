/************************************************************
  Copyright (C), 2015 - 2016, ZhA.
  FileName: main.c
  Author: NaTel   Version : 0.1      Date: 2016/01/18
  Description: 主函数     // 模块描述     
  Version: 测试串口驱动用  // 版本信息
  Function List:   // 主要函数及其功能
    1. main
	2. Init
  History:         // 历史修改记录
      <author>  <time>   <version >   <desc>
      David    96/10/12     1.0     build this moudle 
***********************************************************/
	
#include "stm32f10x.h"
#include "usart3.h"
uint8_t position_state[11] = {0,};//存储串口发送的位置状态

void Init(void)
{
	/* 串口3初始化 */
	USART3_Config();
}

/*************************************************
  Function: main      // 函数名称
  Description: 主函数 // 函数功能、性能等的描述
  Calls: 
	                 // 被本函数调用的函数清单
  Called By: 无      // 调用本函数的函数清单
  Input: 无          // 输入参数说明，包括每个参数的作
                    // 用、取值说明及参数间关系
  Output: 无        // 对输出参数的说明
  Return: 无        // 函数返回值的说明
  Others:          // 其它说明
*************************************************/
	
int main(void)
{
	Init();//初始化
	while (1)
	{
	}
}

/*********************************************END OF FILE**********************/
