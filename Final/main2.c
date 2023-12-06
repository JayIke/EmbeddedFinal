/*
 * EmbeddedFinalProject.c
 *
 * Created: 11/26/2023 8:56:07 AM
 * Author : tim
 */ 

#include "config.h"
#include "uart.h"
#include "lcd.h"
#include "font.h"
#include "i2c.h"

 #define TRIG_PIN PB2
 #define ECHO_PIN PB0
 
 #define SERVO_PIN PB1
 
 volatile unsigned long pulseStart, pulseEnd;
 volatile unsigned long distance, duration;
 volatile static uint8_t update_pwm_rdy = 0;
 
 // Timer1 overflow vector
 ISR(TIMER1_OVF_vect) {
	 update_pwm_rdy = 0; // reset
 }
 
 // Initialize
 void init(void) {
	 DDRB |= (1 << SERVO_PIN) | (1 << TRIG_PIN); // servo and trigger pins -> output
	 DDRB &= ~(1 << ECHO_PIN); // echo pin -> input
	 
	 // Fast PWM mode
	 TCCR1A	|= (1 << COM1A1) | (1 << WGM11);
	 
	 // Overflow timer enable
	 TIMSK1 |= (1 << TOIE1);
	 
	 OCR1AH = (SERVO_MIN & 0xFF00) >> 8;
	 OCR1AL = (SERVO_MIN & 0x00FF);
	 ICR1H = (PWM_TOP & 0xFF00) >> 8;
	 ICR1L = (PWM_TOP &0x00FF);
	 
	 TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11); // prescaler -> 8
	 
	 sei(); // enable interrupts
 }
 
 void triggerPulse(void) {
	 PORTB &= ~(1 << TRIG_PIN); // trigger -> low
	 _delay_us(2);
	 PORTB |= (1 << TRIG_PIN); // trigger -> high
	 _delay_us(10);
	 PORTB &= ~(1 << TRIG_PIN); // trigger -> low
 }
 
 void measureDistance(void) {
	 pulseStart = 0;
	 pulseEnd = 0;
	 
	 while (!(PINB & (1 << ECHO_PIN))); // waiting for echo -> high
	 pulseStart = TCNT1;
	 
	 while (PINB & (1 << ECHO_PIN)); // waiting for echo -> low
	 pulseEnd = TCNT1;
	 
	 duration = pulseEnd - pulseStart;
	 distance = (duration / 58);
	 
 }
 
 static void update_pwm(uint16_t i) {
	 update_pwm_rdy = 1;
	 while(update_pwm_rdy != 0);
	 OCR1AH = (i & 0xFF00) >> 8;
	 OCR1AL = (i & 0x00FF);
 }
 
 void servo_set(uint16_t deg, uint16_t max_deg) {
	 float set = (float)deg / (float)max_deg;
	 set = (((float)SERVO_MAX-(float)SERVO_MIN)*set) + (float)SERVO_MIN;
	 uint16_t point = (uint16_t)set;
	 update_pwm(point);
 }

int main(void) {
	uint16_t i = 0;
	uint8_t detection = 0;
	
	uart_init(9600, 0);
	init();
	uint8_t sweep_right = 107;
	uint8_t sweep_left = 21;
	lcd_init(LCD_DISP_ON);    // init lcd and turn on
	
	//lcd_puts("Hello World");  // put string from RAM to display (TEXTMODE) or buffer (GRAPHICMODE)
	//lcd_gotoxy(0,2);          // set cursor to first column at line 3
	//lcd_puts_p(PSTR("String from flash"));  // puts string form flash to display (TEXTMODE) or buffer (GRAPHICMODE)
	#ifdef GRAPHICMODE
	//lcd_drawCircle(64,32,7,WHITE); // draw circle to buffer white lines
	//lcd_display();                 // send buffer to display
	//lcd_clear_buffer();
	lcd_set_contrast(80);
		


	#endif
	servo_set(0, 128);
	
	while(1) {	
				
		// Rotate 120 degrees from 30 degrees to 150 
		for (i = 11; i <= 117; i++) {
			triggerPulse();
			
			measureDistance();
			lcd_drawRadar();
			lcd_drawLine(64,60,i,10,WHITE);
			
			lcd_display();
			
			
			lcd_clear_buffer();
			if(distance <= 30) {
				detection = 1;
				while(detection == 1) {
					triggerPulse();
					measureDistance();
					
					if (distance > 30) { detection = 0; }
					else {
						uart_send_string("Object detected!\n");
						char distance_str[10];
						sprintf(distance_str, "%u", distance);
						uart_send_string("Distance: ");
						uart_send_string(distance_str);
						uart_send_string("\n");
						lcd_gotoxy(i,distance);
						lcd_puts(distance_str);
						lcd_drawRadar();
						lcd_fillCircle(i,distance,3,WHITE);
						lcd_drawLine(64,60,i,distance,WHITE);
						lcd_display();
						_delay_ms(500);
					}
				}
			}
			servo_set(128-i, 128);
			lcd_clear_buffer();
			_delay_ms(5);
		}

		// Rotate back
		for (i = 117; i >= 11; i--) {
			triggerPulse();
			
			measureDistance();
			lcd_drawRadar();
			lcd_drawLine(64,60,i,10,WHITE);
			
			lcd_display();
			lcd_clear_buffer();
			if(distance <= 30) {
				detection = 1;
				while(detection == 1) {
					triggerPulse();
					measureDistance();
					
					if (distance > 30) { detection = 0; }
					else {
						uart_send_string("Object detected!\n");
						char distance_str[10];
						sprintf(distance_str, "%u", distance);
						uart_send_string("Distance: ");
						uart_send_string(distance_str);
						uart_send_string("\n");
						lcd_gotoxy(i,distance);
						lcd_puts(distance_str);
						lcd_drawRadar();
						lcd_fillCircle(i,distance,3,WHITE);
						lcd_drawLine(64,60,i,distance,WHITE);
						lcd_display();
						_delay_ms(500);
					}
				}
			}
			servo_set(128-i, 128);
			lcd_clear_buffer();
			_delay_ms(5);
		}
	}
}