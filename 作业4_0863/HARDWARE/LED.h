#ifndef __LED_H
#define __LED_H
#include "stm32f4xx.h"
#include <stdbool.h>
void LED_Init(void);
void LED_SET(u16 led_num,bool led_state);
void LED_Tick(u8 key_state);
void LED_off(void);
#endif
