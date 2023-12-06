//****main.c****//
#include "lcd.h"
#include <avr/common.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "i2c.h"
#include "font.h"
#include "config.h"


int main(void){
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
  lcd_set_contrast(150);
 


#endif
  for(;;){
	  uint8_t temp = 3;
	 for(uint8_t i = sweep_right; i>sweep_left; i--){
		
		//lcd_drawLine(0,45,127,45,WHITE);
		if (i > 111 || i<21){
			if (temp <5){
				temp++;
				
			}
		}
		
		lcd_drawRadar();
		lcd_drawLine(64,60,i,16+temp,WHITE);
		
		lcd_display();
		lcd_clear_buffer();
		i--;
	 }
	 temp = 3;
	 for(uint8_t j = sweep_left; j<sweep_right; j++){
		
		 if (j > 111 || j<21){
			 if (temp <6){
			 temp++;
			 }
		 }
		 lcd_drawRadar();
		 lcd_drawLine(64,60,j,10+temp,WHITE);
		 
		 lcd_display();
		 lcd_clear_buffer();
		 j++;
	 }
  }
  return 0;
}
