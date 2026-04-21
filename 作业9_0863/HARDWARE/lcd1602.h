#ifndef __lcd1602_H
#define __lcd1602_H
#include "stm32f4xx.h"                  // Device header
#include "sys.h"

/*
RS:是命令 / 数据选择引脚;	当 RS为低电平时，选择命令；当RS为高电平时，选择数据。
RW:是读 / 写选择引脚;			当 RW为低电平时，向 LCD1602写入命令或数据；当 RW为高电平时，从 LCD1602读取状态或数据。（如果不需要进行读取操作，可以直接将其接 VSS。）
E:执行命令的使能引脚，接单片机的一个 I/O 。

LCD1602的基本操作分为四种：
1. 读状态：输入 RS=0， RW=1 ， E=高脉冲。输出： D0—D7为状态字。
2. 读数据：输入 RS=1， RW=1 ， E=高脉冲。输出： D0—D7为数据。
3. 写命令：输入 RS=0， RW=0 ， E=高脉冲。输出：无。
4. 写数据：输入 RS=1， RW=0 ， E=高脉冲。输出：无。

*/

//拉高功能引脚
#define Set_RS	GPIO_SetBits(GPIOC,GPIO_Pin_10)
#define Set_RW	GPIO_SetBits(GPIOC,GPIO_Pin_11)
#define Set_EN	GPIO_SetBits(GPIOC,GPIO_Pin_12)
//拉低功能引脚
#define Clr_RS	GPIO_ResetBits(GPIOC,GPIO_Pin_10)
#define Clr_RW	GPIO_ResetBits(GPIOC,GPIO_Pin_11)
#define Clr_EN	GPIO_ResetBits(GPIOC,GPIO_Pin_12)


void LCD_Init(void);//LCD初始化
void LCD_Clear(void);//LCD清屏操作
void LCD_Display_Char(u8 x,u8 y,char dat);//LCD显示字符
void LCD_Display_Str(u8 x,u8 y,char *str);//LCD显示字符串
void LCD_RunDisplay(u8 x,u8 y,u8 *str,u8 RL);//LCD整屏滚动显示


#endif




