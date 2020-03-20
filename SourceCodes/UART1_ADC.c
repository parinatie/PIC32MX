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
    
    lcd_init();
    clear_display();
    lcd_display("SWADESHEE");
    // Init ADC
    TRISDCLR= _TRISD_TRISD0_MASK|_TRISD_TRISD1_MASK|_TRISD_TRISD2_MASK; // LEDs 
    TRISBSET= _TRISB_TRISB2_MASK; // ADC at RB2
    
    //UART1 config
    U1MODESET= _U1MODE_ON_MASK|_U1MODE_RTSMD_MASK; //UART1 is enabled; UxRTS pin is in Simplex mode
    U1MODEbits.UEN=0;//UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/UxBCLK pins are controlled by PORT latches
    U1MODEbits.PDSEL=0;// 8-bit data, no parity
    U1MODECLR= _U1MODE_IREN_MASK|_U1MODE_ABAUD_MASK | _U1MODE_BRGH_MASK |_U1MODE_STSEL_MASK; //IrDA is disabled, Baud rate measurement disabled, Standard Speed mode, 1 Stop bit
    
    U1STACLR= _U1STA_ADM_EN_MASK|_U1STA_ADDEN_MASK; //Automatic Address Detect mode is disabled,Address Detect mode disabled
    U1STASET= _U1STA_URXEN_MASK | _U1STA_UTXEN_MASK; //UARTx receiver is enabled, UARTx transmitter enabled

    // if(!(U1STA &(1<<_U1STA_UTXBF_POSITION))) // check if Transmit Buffer Full Status bit
    //while(!(U1STA &(1<<_U1STA_TRMT_POSITION))); //Transmit shift register is not empty, a transmission is in progress or queued in the transmit buffer
    //if((U1STA &(1<<_U1STA_RXDA_POSITION))) // Receive buffer has data, at least one more character can be read
    U1STAbits.URXISEL=0;//Interrupt flag bit is set when a character is received
    //U1TXREG, U1RXREG:
    U1BRG=UxBRG; // UxBRG is defined
    IFS0CLR= _IFS0_U1TXIF_MASK | _IFS0_U1RXIF_MASK|_IFS0_U1EIF_MASK; // CLEAR UART 1, TX, RX AND Error Interrupt Request Flag bit
    
    IEC0CLR=_IEC0_U1TXIE_MASK|_IEC0_U1EIE_MASK; // UART1 Interrupt is disabled
    IEC0SET=_IEC0_U1RXIE_MASK; // RXIE interrupt enable
    IPC6bits.U1IP=7; // U1 Interrupt priority
    IPC6bits.U1IS=3;
    //if(IFS0 &(1<<_IFS0_U1TXIF_POSITION)) // TXIF FLAG IS  SET
     __builtin_enable_interrupts();
     INTCONSET=_INTCON_MVEC_MASK; //Enable Multi vectored interrupt 
    while(1)
    {
        if(!(U1STA &(1<<_U1STA_UTXBF_POSITION))) // check if Transmit Buffer Full Status bit
        {
            while(!(U1STA &(1<<_U1STA_TRMT_POSITION))); //Transmit shift register is not empty, a transmission is in progress or queued in the transmit buffer
            U1TXREG='R';
            delay(500);
        }
        
    }
    
    AD1PCFG&=~(1<<LM32_RB2); //Analog input pin in Analog mode
    
        
    AD1CHSCLR= _AD1CHS_CH0NA_MASK; //
    AD1CHSbits.CH0SA=LM32_RB2;// AN3
    
    AD1CHSCLR= _AD1CHS_CH0NB_MASK; //
    AD1CHSbits.CH0SB=LM32_RB2;// AN3
    
    AD1CON1bits.FORM=0; // Integer 16-bit
    AD1CON1bits.SSRC=0; // Clearing SAMP bit ends sampling and starts conversion
    AD1CON1CLR=_AD1CON1_CLRASAM_MASK|_AD1CON1_ASAM_MASK; //Sampling begins when SAMP bit is set
    //Stop conversions when the first ADC interrupt is generated. Hardware clears the ASAM bit when the ADC interrupt is generated
    
    AD1CON2bits.VCFG=0;// Voltage Reference Configuration bits AVDD AVSS
    AD1CON2CLR=_AD1CON2_CSCNA_MASK;//Do not scan inputs
    AD1CON2bits.SMPI=0;//Interrupts at the completion of conversion for each sample/convert sequence
    
    AD1CON2CLR= _AD1CON2_BUFM_MASK |_AD1CON2_ALTS_MASK;   //Buffer configured as one 16-word buffer ADC1BUF(15...0.), Always use MUX A input multiplexer settings
    
    AD1CON3CLR=_AD1CON3_ADRC_MASK;//ADC internal RC clock
    AD1CON3bits.SAMC=0;//Auto-Sample Time bits 0- not allowed   
    AD1CON3bits.ADCS=15;// ADC Conversion Clock Select bits

    
   // AD1CSSL|=(1<<POT_RB3);//Select ANx for input scan
    

    
//    //Interrupt config
    INTCONSET=_INTCON_MVEC_MASK; //Enable Multi vectored interrupt 
    IFS1CLR=_IFS1_AD1IF_MASK; //Clear ADC INT flag
    IEC1SET=_IEC1_AD1IE_MASK; // Enable ADC INT
    IPC6bits.AD1IP=5;//Interrupt Priority is 5
    IPC6bits.AD1IS=3;//Interrupt Subpriority is 3
    
    __builtin_enable_interrupts();
    
    AD1CON1SET= _AD1CON1_ON_MASK;// A/D converter module is operating
    while(1)
    {  
        IFS1CLR=_IFS1_AD1IF_MASK; //Clear ADC INT flag
        AD1CON1CLR=_AD1CON1_DONE_MASK;// Clear done bit in manual mode
        AD1CON1SET=_AD1CON1_SAMP_MASK;//When ASAM = 0, writing 1 to this bit starts sampling.
        //adc_inprogress=1;
        delay(1);
        AD1CON1CLR=_AD1CON1_SAMP_MASK;//When SSRC = 000, writing 0 to this bit will end sampling and start conversion.   
        
        //while(!IFS1&(1<<1));
        while(!AD1CON1&(1<<0));
        delay(10);
        //if(adc_inprogress)
        //while(~AD1CON1&(1<<0));
        LED3_INV();
        delay(100);
               
    }

    return (EXIT_SUCCESS);
}

//ISR
void __ISR(_UART_1_VECTOR, IPL7SOFT) UART1_ISR(void)
{
    if(IFS0 &(1<<_IFS0_U1TXIF_POSITION)) // TXIF FLAG IS  SET
    {
        
    }
    if(IFS0 &(1<<_IFS0_U1RXIF_POSITION)) // RXIF FLAG IS  SET
    {
        char rcvd;
        rcvd=U1RXREG;
        send_data(rcvd);
        U1TXREG=rcvd;
        IFS0CLR=_IEC0_U1RXIE_MASK;
    }
    if(IFS0 &(1<<_IFS0_U1EIF_POSITION)) // EIF FLAG IS  SET
    {
        
    }
    
}
void __ISR(_ADC_VECTOR, IPL7SOFT) LM35_ISR(void)
{    
    uint32_t result;
    float temp=0;
    //adc_inprogress=0;  
    result=(unsigned int)ADC1BUF0;
    temp=result*3.3*100.0/1023.0;
        //result=99999;
    clear_display();
    //display_int(result);
    display_float(temp);
    //AD1CON1CLR=_AD1CON1_DONE_MASK;// Clear done bit in manual mode
    IFS1CLR=_IFS1_AD1IF_MASK; //Clear ADC INT flag
    //LED3_INV();

}
