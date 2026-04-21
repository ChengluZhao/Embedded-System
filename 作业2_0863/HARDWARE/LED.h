#ifndef __LED_H
#define __LED_H
#include "stm32f4xx.h"
#include <stdbool.h>
void LED_Init(void);
void LED_SET(int led_num,bool led_state);
void LED_turn(int led_num);
void LED_water(int mode);
#endif
