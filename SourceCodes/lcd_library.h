/* 
 * File:   lcd_library.h
 * Author: Prabhu
 *
 * Created on January 5, 2018, 7:57 PM
 */

#ifndef LCD_LIBRARY_H
#define	LCD_LIBRARY_H

#ifdef	__cplusplus
extern "C" {
#endif
			/*These are the deffinitions need to be defined for different hardwares connections*/

#define LCD_pin_init1 		TRISD&=~((1<<4)|(1<<5)|(1<<6)|(1<<7))	  //making all lcd pins as output pins
#define LCD_pin_init2       TRISG&=~((1<<0)|(1<<1))
#define rs 				LATGbits.LATG0													
#define e				LATGbits.LATG1													
#define	DB7				LATDbits.LATD7
#define	DB6				LATDbits.LATD6
#define	DB5				LATDbits.LATD5
#define	DB4				LATDbits.LATD4
#define clearnibble		(DB7=DB6=DB5=DB4=0)
#define	display_charect	16

// Public functions
void lcd_init(void);
void lcd_display( char display[]);
void clear_display(void);
void display_float(double floatnum);
void display_int(unsigned int digit5);
void LCD_Lshift(void);
void LCD_Rshift(void);
void LCD_home(void);
void send_data(char data_);
void send_command(char command_);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_LIBRARY_H */

