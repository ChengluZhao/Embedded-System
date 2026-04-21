#include "stm32f4xx.h"
#include <stdbool.h>
u32 led_count=0;
void LED_Init(void)
{
	GPIO_InitTypeDef GPIOA_InitStructure;
	GPIO_InitTypeDef GPIOC_InitStructure;    //放在这里的原因是 不允许初始化变量在函数的中间
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIOA_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIOA_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIOA_InitStructure.GPIO_Pin = (GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7);
	GPIOA_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIOA_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIOA_InitStructure);
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	GPIOC_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIOC_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIOC_InitStructure.GPIO_Pin = (GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
	GPIOC_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIOC_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOC,&GPIOC_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7);
	GPIO_SetBits(GPIOC,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4);
}
void LED_SET(u16 led_num,bool led_state)
{
	switch(led_num)
	{
		case 1:
		{
			if(led_state==false)
				GPIO_SetBits(GPIOA,GPIO_Pin_2);
			else
				GPIO_ResetBits(GPIOA,GPIO_Pin_2);
			break;
		}
		case 2:
		{
			if(led_state==false)
				GPIO_SetBits(GPIOC,GPIO_Pin_2);
			else
				GPIO_ResetBits(GPIOC,GPIO_Pin_2);
			break;
		}
		case 3:
		{
			if(led_state==false)
				GPIO_SetBits(GPIOA,GPIO_Pin_4);
			else
				GPIO_ResetBits(GPIOA,GPIO_Pin_4);
			break;
		}
		case 4:
		{
			if(led_state==false)
				GPIO_SetBits(GPIOA,GPIO_Pin_7);
			else
				GPIO_ResetBits(GPIOA,GPIO_Pin_7);
			break;
		}
		case 5:
		{
			if(led_state==false)
				GPIO_SetBits(GPIOC,GPIO_Pin_3);
			else
				GPIO_ResetBits(GPIOC,GPIO_Pin_3);
			break;
		}
		case 6:
		{
			if(led_state==false)
				GPIO_SetBits(GPIOA,GPIO_Pin_3);
			else
				GPIO_ResetBits(GPIOA,GPIO_Pin_3);
			break;
		}
		case 7:
		{
			if(led_state==false)
				GPIO_SetBits(GPIOA,GPIO_Pin_5);
			else
				GPIO_ResetBits(GPIOA,GPIO_Pin_5);
			break;
		}
		case 8:
		{
			if(led_state==false)
				GPIO_SetBits(GPIOC,GPIO_Pin_4);
			else
				GPIO_ResetBits(GPIOC,GPIO_Pin_4);
			break;
		}
	}
}
void LED_Tick(u8 key_state)
{
	
	
	switch(key_state)
	{
		case 1:
			LED_SET(1,true);LED_SET(2,true);LED_SET(3,true);LED_SET(4,true);LED_SET(5,true);LED_SET(6,true);LED_SET(7,true);LED_SET(8,true);
			break;
		case 2:
			if(led_count==45)
			{
				led_count=0;
			}
			if(led_count%5==0)
			{
				LED_SET(1,false);LED_SET(2,false);LED_SET(3,false);LED_SET(4,false);LED_SET(5,false);LED_SET(6,false);LED_SET(7,false);LED_SET(8,false);
				LED_SET(led_count/5,true);
			}break;
		case 3:
			if(led_count==10)
			{
				led_count=0;
			}
			switch(led_count)
			{	
				case 0:LED_SET(1,false);LED_SET(2,false);LED_SET(3,false);LED_SET(4,false);LED_SET(5,false);LED_SET(6,false);LED_SET(7,false);LED_SET(8,false);break;
				case 5:LED_SET(1,true);LED_SET(2,true);LED_SET(3,true);LED_SET(4,true);LED_SET(5,true);LED_SET(6,true);LED_SET(7,true);LED_SET(8,true);break;
			}break;
			
	}
	led_count ++;
}

void LED_off(void)
{
	LED_SET(1,false);LED_SET(2,false);LED_SET(3,false);LED_SET(4,false);LED_SET(5,false);LED_SET(6,false);LED_SET(7,false);LED_SET(8,false);
}
