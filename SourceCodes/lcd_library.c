				/*This program is written for lcd interface in 4-bit mode in pic16 series */

#include<xc.h>
#include "lcd_library.h"
//#define _XTAL_FREQ 1000000
//#include "mcc_generated_files/mcc.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
#define command rs=0
#define data rs=1
#define	high			1
#define	low				0
////////////////////////////////////////////////////////////////////////////////////////////////////////
								/* LCD function deffinitions*/

//#define clear_display 					0x01
#define desplay_curser_home 			0x02
#define	bit4_2line_10_7					0x28
#define	bit8_2line_10_7					0x38
#define	set_zero_address				0x80
#define	disp_on_curs_underl_curs_blink	0x0C
////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Public functions
//void lcd_init(void);
//void lcd_display( char display[]);
//void clear_display(void);
//void display_float(float floatnum);
//void display_int(int digit5);
//void send_data(char data_);
//void send_command(char command_);

//Private functions
void sub_data_command(char value);
void __delay_ms(uint16_t ms)
{
    uint16_t i,j;
    for(j=0;j<=ms;j++)
    {
        for(i=0;i<=8888;i++);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Function lcd_init
 * This function initializes the rs, e, DBb4, DB5, DB6, DB7 pins as output.
 * Before calling this function, modify the #define for 
 *  rs, e, DBb4, DB5, DB6, DB7 as per the LCD connections
 *  in the lcd_library.h
 */
void lcd_init(void)
{
	__delay_ms(1);
	LCD_pin_init1;LCD_pin_init2;
	clearnibble;
	command;
	sub_data_command(bit8_2line_10_7>>4);
	sub_data_command(bit8_2line_10_7>>4);
	sub_data_command(bit8_2line_10_7>>4);
	////////////////////////////////////initialise with 8bit mode
	sub_data_command(bit4_2line_10_7>>4);
	/////////////////////////////////////switch to 4bit mode
	send_command(bit4_2line_10_7);
	//////////////////////////////////////4bit mode,double line
	send_command(disp_on_curs_underl_curs_blink);
	data;
}

/*Function clear_display
 * The function clears the lcd display
 */
void clear_display(void)
{
	send_command(0x01);
}

/*Function lcd_display
 * The function displays a string on lcd display 
 * Parameter: string to be displayed 
*/
void lcd_display( char display[])
{
	int i;
	for(i=0;display[i]!='\0';i++)
	{
		if(i==0)
			{
				//command;
				send_command(0x80);
				//data;
			}
		else if(i==display_charect)
			{
				//command;
				send_command(0xc0);
				//data;
			}

		send_data(display[i]);	
	}
}

/*Function display_int
 * This function displays a 5 digit integer on the lcd 
 * Parameter digit5: 5 digit integer
 */
void display_int(unsigned int digit5)
{
    char str[6];
    str[4]=(digit5%10)+0x30;
    digit5=digit5/10;
    str[3]=(digit5%10)+0x30;
    digit5=digit5/10;
    str[2]=(digit5%10)+0x30;
    digit5=digit5/10;
    str[1]=(digit5%10)+0x30;
    digit5=digit5/10;
    str[0]=(digit5%10)+0x30;
    str[5]='\0';
    lcd_display(str);
}

/*Function display_float
 The function displays a floating number on lcd
 Parameter floatnum: A floating number in the range 0.00 to 9999.99*/
void display_float(double floatnum)
{
    long int digit5=0;
    int dig2=0;
    char str[8]="9999.99";
    digit5=(long int) (floatnum*100.0);  
    //dig2=((floatnum-digit5)*100.00);
//    str[7]=(digit5%10)+0x30;
//    digit5=digit5/10;
    str[6]=(digit5%10)+0x30;
    digit5=digit5/10;
    str[5]=(digit5%10)+0x30;
    digit5=digit5/10;
    str[3]=(digit5%10)+0x30;
    digit5=digit5/10;
    str[2]=(digit5%10)+0x30;
    digit5=digit5/10;
    str[1]=(digit5%10)+0x30;
    digit5=digit5/10;
    str[0]=(digit5%10)+0x30;
    lcd_display(str);
}

/*Function LCD_Lshift
 This function shifts the lcd content to left by one position*/
void LCD_Lshift(void)
{
    send_command(0x18);
}

/*Function LCD_Rshift
 This function shifts the lcd content to right by one position*/
void LCD_Rshift(void)
{
    send_command(0x1c);
}

/*Function LCD_home
 This function sets the lcd to home position*/
void LCD_home(void)
{
    send_command(0x80);
}
/*Function send_data
 * Sends a byte of data to data register of LCD
 * Paramter: data_ A byte of data
 */
void send_data(char data_)
{
	data;
	sub_data_command(data_>>4);
	sub_data_command(data_);
}

/*Function send_command
 * Sends a byte of data to command register of LCD
 * Paramter: data_ A byte of command
 */
void send_command(char command_)
{
	command;
	sub_data_command(command_>>4);
	sub_data_command(command_);
	data;
}
// Private function
void sub_data_command(char value)
{
	e=1;
	DB7=value>>3;
	DB6=value>>2;
	DB5=value>>1;
	DB4=value>>0;		
	__delay_ms(2);
	e=0;
	__delay_ms(2);
}