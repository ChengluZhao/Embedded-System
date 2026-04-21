#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "LED.h"



void abset(u16 *sz,u16 a,u16 b,u16 c, u16 d,u16 e)
{
	sz[0]=a;
	sz[1]=b;
	sz[2]=c;
	sz[3]=d;
	sz[4]=e;
}


int main(void)
{	
	

	u16 ab[5]={0xbb,0x00,0x07,0x07,0xee};
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	uart_init(9600);	//串口初始化波特率为9600
 	LED_Init();
	LED_SET(8,true);
	while(1)
		{
		
		if(USART_RX_STA&0x8000)
		{					   
			
			if(USART_RX_BUF[0]==0xbb&&USART_RX_BUF[4]==0xee&&USART_RX_BUF[3]==(USART_RX_BUF[1]^USART_RX_BUF[2]))
			{
				switch(USART_RX_BUF[1])
				{
					case 0xa0:abset(ab,0xbb,0x00,ab[3],(0x00^ab[3]),0xee);usart1_sendrtu(ab);break;
					case 0xa1:
						ab[3]=USART_RX_BUF[2];
						if(USART_RX_BUF[2]<=0x07)
						{
							abset(ab,0xbb,0x00,ab[3],(0x00^ab[3]),0xee);usart1_sendrtu(ab);LED_off();LED_SET(USART_RX_BUF[2]+1,true);
						}
						else
						{
							abset(ab,0xbb,0x02,ab[3],(0x02^ab[3]),0xee);usart1_sendrtu(ab);
						}break;
					default:abset(ab,0xbb,0x01,ab[3],(0x01^ab[3]),0xee);usart1_sendrtu(ab);break;
				}
			}
			
			
			USART_RX_STA=0;
		}
		}
		
}