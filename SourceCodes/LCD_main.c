/* 
 * File:   LEDBlink.c
 * Author: prabr
 *
 * Created on 25 December, 2019, 1:47 PM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "lcd_library.h"



#include <stdio.h>
#include <stdlib.h>

// Device configuration register settings must be defined in the bootloader.
// Applications must just re-use these settings from bootloader.
    // #pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF
    // #pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1
//void InitializeSystem(void);
/*
 * 
 */
// LED1 (RD0)
#define LED1            LATDbits.LATD0
#define TRIS_LED1       TRISDbits.TRISD0
#define LED1_SET()      LATDSET = _LATD_LATD0_MASK;
#define LED1_CLR()      LATDCLR = _LATD_LATD0_MASK;
#define LED1_INV()      LATDINV = _LATD_LATD0_MASK;

// LED2 (RD1)
#define LED2            LATDbits.LATD1
#define TRIS_LED2       TRISDbits.TRISD1
#define LED2_SET()      LATDSET = _LATD_LATD1_MASK;
#define LED2_CLR()      LATDCLR = _LATD_LATD1_MASK;
#define LED2_INV()      LATDINV = _LATD_LATD1_MASK;

// LED3 (RD2)
#define LED3            LATDbits.LATD2
#define TRIS_LED3       TRISDbits.TRISD2
#define LED3_SET()      LATDSET = _LATD_LATD2_MASK;
#define LED3_CLR()      LATDCLR = _LATD_LATD2_MASK;
#define LED3_INV()      LATDINV = _LATD_LATD2_MASK;

// LED4 (RG15)
#define LED4            LATGbits.LATG15
#define TRIS_LED4       TRISGbits.TRISG15
#define LED4_SET()      LATGSET = _LATG_LATG15_MASK;
#define LED4_CLR()      LATGCLR = _LATG_LATG15_MASK;
#define LED4_INV()      LATGINV = _LATG_LATG15_MASK;

#define SW1_PRESS (!(PORTD&(1<<13)))
#define SW3_PRESS (!(PORTE&(1<<8)))

//Switches 2, 4 need to be connected to RB1 and RB0 to use weak pull-ups
#define SW2_PRESS   (!(PORTB&(1<<_PORTB_RB0_POSITION))) //CN2-AN0 -make ANx pins as digital by setting bit PCFGx in AD1PCFG
#define SW4_PRESS   (!(PORTB&(1<<_PORTB_RB1_POSITION))) //CN3-AN1

#define T1_PSCLR1_1     (T1CONbits.TCKPS=0)
#define T1_PSCLR1_8     (T1CONbits.TCKPS=1)
#define T1_PSCLR1_64    (T1CONbits.TCKPS=2)
#define T1_PSCLR1_256   (T1CONbits.TCKPS=3)
//INT2- RE9- Connect S3 to RE9 using jumper wire
void delay(uint16_t ms)
{
    uint16_t i,j;
    for(j=0;j<=ms;j++)
    {
        for(i=0;i<=8888;i++);
    }
}

int main(int argc, char** argv)
{
    lcd_init();
    clear_display();
    lcd_display("SWADESHEE");
    while(1)
    {
        LED3_INV();
        delay(500);
               
    }

    return (EXIT_SUCCESS);
}

//ISR
void __ISR(_TIMER_1_VECTOR, IPL7SOFT) T1_ISR(void)
{

}
