#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "pwm.h"
#include "key.h"
#include "led.h"
#include "24cxx.h"

volatile u8 TEXT_Buffer[]={0};
#define SIZE sizeof(TEXT_Buffer)	 
	
int main(void)
{ 
	volatile u16 CCR=0;    
  volatile u8 key;
	u8 datatemp[SIZE];	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	AT24CXX_Init();
	delay_init(168);  
	uart_init(115200);
	KEY_Init();
 	TIM14_PWM_Init(100-1,84-1);	  
	AT24CXX_Read(0,datatemp,SIZE);
	CCR=datatemp[0];
   while(1)
	{
		key=KEY_Scan(0);	
		if(key)
		{						   
			switch(key)
			{				 
				case KEY0_PRES:	
				{	CCR++;
					break;
				}
				case WKUP_PRES:
				{
					TEXT_Buffer[0]=CCR;
					AT24CXX_Write(0,(u8*)TEXT_Buffer,SIZE);
					break;
				}
				
			}
		}else delay_ms(10); 
		if(CCR==101)
			CCR=0;
		TIM_SetCompare1(TIM14,CCR);
	}
}
