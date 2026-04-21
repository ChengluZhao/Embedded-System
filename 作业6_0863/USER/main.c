#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "timer.h"
#include "led.h"
#include "lcd1602.h"
#include "stdio.h"
#include "string.h"
#include "adc.h"
#include "exti.h"
#include "KEY.h"

u16 n=0; //记录中断次数
char name[8];
//--------ADC参数----------//
u16 adcx;
float temp;
float temp1;
float temp2;

u8 flag=0;
int main(void)
{	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	uart_init(115200);	//串口初始化波特率为115200
	EXTIx_Init();
	LED_Init2();
	LCD_Init();
	KEY_Init();
	Adc_Init();
	LCD_Display_Str(1,1,"ADC:");
	LCD_Display_Str(2,1,"u=");
	LCD_Display_Str(2,4,".");
	TIM_SetCompare3(TIM2,20-1);
	TIM6_Int_Init(10000-1,8400-1);
	while(1)
		{	
		}
		
}

void TIM6_DAC_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) == SET) // 溢出中断
	{
		if(flag)
		{
			adcx=Get_Adc_Average(ADC_Channel_5,20);
			n++;
			printf("adc：%u",adcx);
			LCD_Display_Str(1,8," ");
			sprintf(name,"%u",adcx);
			LCD_Display_Str(1,5,name);
			temp=(float)adcx*(3.3/4096);
			adcx=temp;
			temp1=adcx;
			sprintf(name,"%u",adcx);
			LCD_Display_Str(2,3,name);
			temp-=adcx;
			temp*=1000;
			temp2=temp;
			sprintf(name,"%u",(int)temp);
			LCD_Display_Str(2,5,name);
			printf("u：%u.%u",(int)temp1,(int)temp2);
			LCD_Display_Str(2,10,"YES");
			LED0=!LED0;
		}
		else
			LCD_Display_Str(2,10,"NO ");
	}
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update); // 清除中断标志位
}

void EXTI0_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line4);
	delay_ms(10);	//消抖
	if(WK_UP==1)	 
	{
		flag=!flag;
		LED1=!LED1;
	}		
	
}


