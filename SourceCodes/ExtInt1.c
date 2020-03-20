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
    TRISDbits.TRISD0=0;
    TRISDbits.TRISD1=0;
    LATDbits.LATD0=0;
    LATDbits.LATD1=1;
    TRISESET= _LATE_LATE8_MASK; // Set RE8 as input
    // Interrupt Config
    INTCONSET=_INTCON_MVEC_MASK | _INTCON_INT1EP_MASK; //Enable Multi vectored interrupt and External Interrupt 1 Edge Polarity Control bit- 1 = Rising edge 0 = Falling edge
    IFS0CLR= _IFS0_INT1IF_MASK; // Clear INT1 Flag bit
    IEC0SET=_IEC0_INT1IE_MASK; // INT1 enable
    IPC1bits.INT1IP= 0x04;// Priority
    IPC1bits.T1IS= 0x03;//Sub priority
    __builtin_enable_interrupts();
    while(1)
    {
        LATDINV= _LATD_LATD0_MASK;
        delay(1000);
        LATDINV= _LATD_LATD0_MASK;
        delay(1000);
        
    }

    return (EXIT_SUCCESS);
}

//ISR
void __ISR(_EXTERNAL_1_VECTOR, IPL7SOFT) EI_ISR(void)
{
    // clear the interrupt flag
    IFS0CLR= _IFS0_INT1IF_MASK; // Clear INT1 Flag bit
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