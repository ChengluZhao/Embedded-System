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
#include "dac.h"

u16 n=0; //记录中断次数
char name[8];
//--------ADC参数----------//
u16 adcx;
float temp;
float temp1;
float temp2;
u16 u[100]={500,548,596,644,692,740,788,836,884,932,980,1028,1076,1124,1172,1220,1268,1316,1364,1412,1460,1508,1556,1604,1652,1700,1748,1796,1844,1892,1940,1988,2036,2084,2132,2180,2228,2276,2324,2372,2420,2468,2516,2564,2612,2660,2708,2756,2804,2852,2900,2852,2804,2756,2708,2660,2612,2564,2516,2468,2420,2372,2324,2276,2228,2180,2132,2084,2036,1988,1940,1892,1844,1796,1748,1700,1652,1604,1556,1508,1460,1412,1364,1316,1268,1220,1172,1124,1076,1028,980,932,884,836,788,740,692,644,596,548};
u8 flag=0;
int main(void)
{	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	uart_init(115200);	//串口初始化波特率为115200
	EXTIx_Init();
	LED_Init2();
	KEY_Init();
	Adc_Init();
	Dac1_Init();

	TIM6_Int_Init(2-1,84-1);
	while(1)
		{	
		}
		
}

void TIM6_DAC_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) == SET) // 溢出中断
	{
			adcx=Get_Adc_Average(ADC_Channel_5,20);
			n++;
			//printf("adc:%u\n",adcx);
			temp=(float)adcx*(3.3/4095);
			adcx=temp;
			temp1=adcx;
			temp-=adcx;
			temp*=1000;
			temp2=temp;
			if(temp2<100)
			{
				printf("u:%u.0%u\n",(int)temp1,(int)temp2);
			}
			else
				printf("u:%u.%u\n",(int)temp1,(int)temp2);
			LED0=!LED0;
			if(n==99)
				n=0;
			Dac1_Set_Vol((int)u[n]);

	}
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update); // 清除中断标志位
}



