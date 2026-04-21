#include "stm32f4xx.h"
#include <stdbool.h>
#include "delay.h"  
#include "LED.h"
#include "KEY.h"
int main(void)
{
	u8 key;
	u8 i;
	delay_init(168);
	LED_Init(); 
	KEY_Init();
	while(1)
	{
		//LED_water(1);
		for(i=0;i<3;i++)
		
			LED_water(2);
		
		//LED_water(3);
		key = KEY_Scan(1);
		if(key)
		{
			switch(key)
			{
				case WKUP_PRES:{LED_water(5);break;}
				case KEY0_PRES:{LED_water(4);break;}
			}
		}
	}
}


