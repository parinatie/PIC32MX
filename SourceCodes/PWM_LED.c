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

#define T2_PSCLR1_1     (T2CONbits.TCKPS=0)
#define T2_PSCLR1_2     (T2CONbits.TCKPS=1)
#define T2_PSCLR1_4     (T2CONbits.TCKPS=2)
#define T2_PSCLR1_8     (T2CONbits.TCKPS=3)
#define T2_PSCLR1_16    (T2CONbits.TCKPS=4)
#define T2_PSCLR1_32    (T2CONbits.TCKPS=5)
#define T2_PSCLR1_64    (T2CONbits.TCKPS=6)
#define T2_PSCLR1_256   (T2CONbits.TCKPS=7)

#define T2_32BITMODE    (T2CONbits.T32=1)
#define T2_16BITMODE    (T2CONbits.T32=0)

#define POT_RB3         3 //AN3
#define LM32_RB2        2 //AN2

#define BAUDRATE (2400)
#define FPB_CLK (80000000L)
#define UxBRG ((FPB_CLK/(16*BAUDRATE))-1)
//INT2- RE9- Connect S3 to RE9 using jumper wire
void delay(uint16_t ms)
{
    uint16_t i,j;
    for(j=0;j<=ms;j++)
    {
        for(i=0;i<=8888;i++);
    }
}
unsigned char adc_inprogress;
int main(int argc, char** argv)
{
    uint16_t duty_cycle=10; 
    char up=1;
    lcd_init();
    clear_display();
    lcd_display("SWADESHEE");
    TRIS_LED1=0;
    // PWM config
    //LED1_SET();
    OC1CONCLR=_OC1CON_OC32_MASK | _OC1CON_OCTSEL_MASK ;// OCxR<15:0> and OCxRS<15:0> are used for comparisons to the 16-bit timer source, Timer2 is clock source
    OC1CONbits.OCM= 6; //PWM mode on OCx; Fault pin disabled
    OC1R= 000; // initial duty cycle - becomes read-only during the module is running
    OC1RS= 1000; // duty cycle for subsequent pulses 
    IFS0CLR= _IFS0_OC1IF_MASK; //Output Compare 1 Interrupt Request Flag bit
    IEC0CLR= _IEC0_OC1IE_MASK; //Output Compare 1 Interrupt Enable bit
    IPC1bits.IC1IP=5; IPC1bits.IC1IS=3; //Output Compare 1 Interrupt Priority bits
    
    // Timer2 Config
     T2CONCLR=_T2CON_TCS_MASK; // Internal clock
     T2CONCLR=_T2CON_TGATE_MASK; //Gated time accumulation disabled
    // TRISCSET=_TRISC_TRISC14_MASK;//RC14 as gated input-T1CK
    T2_PSCLR1_16; // 1:1
    T2_16BITMODE; //16 bit mode

    TMR2=0; 
    PR2=0xFFFF;  
    T2CONSET=_T2CON_ON_MASK; //Timer 1 on
    OC1CONSET= _OC1CON_ON_MASK; //Output Compare peripheral is enabled
    while(1)
    {
        if(IFS0& (1<<_IFS0_T2IF_POSITION) ) // After every timer period match change duty cycle
        {
            IFS0CLR= _IFS0_T2IF_MASK;
            delay(10);
            if(up)
            {
                duty_cycle=duty_cycle+1;
            }
            else
            {
                duty_cycle=duty_cycle-1;
            }
            if(duty_cycle==100)
                up=0;
            if(duty_cycle==00)
                up=1;            
            OC1RS= duty_cycle*652;
        }
    }
    
    return (EXIT_SUCCESS);
}


