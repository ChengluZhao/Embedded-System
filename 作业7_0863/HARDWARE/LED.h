#ifndef __LED_H
#define __LED_H
#include "stm32f4xx.h"
#include <stdbool.h>
#include "sys.h"

#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1	 

void LED_Init2(void);//≥ı ºªØ	

void LED_Init(void);
void LED_SET(u16 led_num,bool led_state);
void LED_Tick(u8 key_state);
void LED_off(void);
#endif
