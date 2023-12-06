/*
 * timer1_hal.h
 *
 * Created: 11/26/2023 2:09:50 PM
 *  Author: tim
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void timer1_init(void);
void pwm_sweep(void);
void servo_set(uint16_t deg,uint16_t max_deg);

#endif /* TIMER1_H_ */