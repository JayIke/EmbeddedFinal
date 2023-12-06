/*
 * IncFile1.h
 *
 * Created: 11/26/2023 1:41:05 PM
 *  Author: tim
 */ 

#ifndef CONFIG_H_
#define CONFIG_H_

#define F_CPU 16000000UL
#define SPEED_OF_SOUND 346
#define PWM_TOP (39999u)
#define SERVO_MIN (1999u)
#define SERVO_MAX (4999u)
#define RX_BUFFER_SIZE 128

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#endif /* CONFIG_H_ */