#include <stm32f4xx.h>
#include "delay.h"
#include "key.h"

void KEY_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
} 
u8 KEY_Scan(u8 mode)
{
	static u8 key_up=1;
	if(mode)key_up=1; 
		if(key_up&&(KEY0==1||WK_UP==1))
		{
			delay_ms(10);
			key_up=0;
			if(KEY0==1)
				return KEY0_PRES;
			if(WK_UP==1)
				return WKUP_PRES;
		}	
	else 
		if(KEY0==0&&WK_UP==0)key_up=1; 
return 0;
}
