#include "stm32f4xx.h"
#include "LED.h"
#include "KEY.h"
#include "exti.h"
#include "timer.h"
extern u8 key_state;
int main(void)
{
	TIM3_Int_Init(1000-1,8400-1);
	LED_Init(); 
	KEY_Init();
	EXTIx_Init();
	while(1)
	{
	}
}
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) 
	{
		LED_Tick(key_state);
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}
