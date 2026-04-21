#ifndef __KEY_H
#define __KEY_H
#include <stm32f4xx.h>

#define KEY0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
#define WK_UP 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	//PA0
#define KEY0_PRES 1
#define WKUP_PRES 2
void KEY_Init(void);
u8 KEY_Scan(u8 mode);
#endif
