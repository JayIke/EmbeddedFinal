/*
 * timer1_hal.h
 *
 * Created: 11/26/2023 2:09:50 PM
 *  Author: tim
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include "config.h"

void timer0_init(void);
uint32_t millis(void);
uint8_t millis_end(uint32_t start_time,uint32_t delay_time);


#endif /* TIMER0_H_ */