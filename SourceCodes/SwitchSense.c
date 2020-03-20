/* 
 * File:   LEDBlink.c
 * Author: prabr
 *
 * Created on 25 December, 2019, 1:47 PM
 */

#include <xc.h>
#include <sys/attribs.h>



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
   // SYSTEMConfig(FCY, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
    //InitializeSystem();
    //INTCONbits.MVEC = 1;    
    //asm volatile("ei");
    unsigned int i=0,j=0,k=0;
    //LEDs as output
    TRISDCLR= _TRISD_TRISD0_MASK|_TRISD_TRISD1_MASK|_TRISD_TRISD2_MASK;
    TRISGCLR= _TRISG_TRISG15_MASK;    

            
    LED1_SET(); LED2_SET();LED3_SET();LED4_SET();
    delay(1000);
    LED1_CLR(); LED2_CLR();LED3_CLR();LED4_CLR();
    
    TRISESET= _TRISE_TRISE8_MASK; // Set RE8 as input
    TRISDSET= _TRISD_TRISD13_MASK; // RD13 as input
     
    TRISBSET= _TRISB_TRISB0_MASK|_TRISB_TRISB1_MASK; //RB0 and RB1 as switches
    //Enable pullups on RB0 and RB1
    AD1PCFGSET= _AD1PCFG_PCFG0_MASK|_AD1PCFG_PCFG1_MASK; // Setting the bits makes it digital Page no 603 in FRM
    CNPUESET= _CNPUE_CNPUE2_MASK |_CNPUE_CNPUE3_MASK; //CN0 and CN1
    
    // Interrupt Config
    INTCONSET=_INTCON_MVEC_MASK | _INTCON_INT2EP_MASK; //Enable Multi vectored interrupt and External Interrupt 2 Edge Polarity Control bit- 1 = Rising edge 0 = Falling edge
    IFS0CLR= _IFS0_INT2IF_MASK; // Clear INT2 Flag bit
    IEC0SET=_IEC0_INT2IE_MASK; // INT2 enable
    IPC2bits.INT2IP= 0x04;// Priority
    IPC2bits.T2IS= 0x03;//Sub priority
    //__builtin_enable_interrupts();
    while(1)
    {
 
        //SW3
        if(SW1_PRESS)
        {
            LED1_SET();  
            delay(300);
        }
        else
        {
            LED1_CLR(); 
        }
        //SW4
        if(SW2_PRESS)
        {
            LED2_SET();
            delay(300);            
        }
        else
        {
            LED2_CLR(); 
        }
        if(SW3_PRESS)
        {
            LED3_SET();
            delay(300);            
        }
        else
        {
            LED3_CLR(); 
        }
        if(SW4_PRESS)
        {
            LED4_SET();
            delay(300);             
        } 
        else
        {
            LED4_CLR(); 
        }
       
    }

    return (EXIT_SUCCESS);
}

//ISR
void __ISR(_EXTERNAL_2_VECTOR, IPL7SOFT) EI2_ISR(void)
{
    // clear the interrupt flag
    IFS0CLR= _IFS0_INT2IF_MASK; // Clear INT1 Flag bit
    LATDINV= _LATD_LATD1_MASK;
    delay(10);
}
//
//void __ISR(_CORE_TIMER_VECTOR, IPL2SOFT) CoreTimerHandler(void)
//{
//    
//}

//void InitializeSystem(void)
//{
//    // PIC32MX CPU Speed Optimizations (Cache/Wait States/Peripheral Bus Clks)
//    // On reset, and after c-startup:
//    // - Prefetch Buffer is disabled,
//    // - I Cache is disabled,
//    // - PFM wait States set to max setting (7 = too slow!!!)
//    // - Data Memory SRAM wait states set to max setting (1 = too slow!!!)
//    
//    // PBCLK - already set to SYSCLK/8 via config settings
//    
//    // Data Memory SRAM wait states: Default Setting = 1; set it to 0
//    BMXCONbits.BMXWSDRM = 0;
//
//    // Flash PM Wait States: MX Flash runs at 2 wait states @ 80 MHz
//    CHECONbits.PFMWS = 2;
//
//    // Prefetch-cache: Enable prefetch for cacheable PFM instructions
//    CHECONbits.PREFEN = 1;
//
//    // PIC32MX695-Specific
//    // JTAG: Disable on PORTA
//    DDPCONbits.JTAGEN = 0;
//    
//
//  /* For Interrupts */
//    /* Set Interrupt Controller for multi-vector mode */
//  //  INTCONSET = _INTCON_MVEC_MASK;
//
//    /* Enable Interrupt Exceptions */
//    // set the CP0 status IE bit high to turn on interrupts globally
// //   __builtin_enable_interrupts();
//
//
//
//} 