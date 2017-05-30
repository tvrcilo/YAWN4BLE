/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

void InitApp(void)

//depends on the application
    /*
   //disable analog functions
   ANSELA = 0x00; 
   ANSELB = 0x00;  
   ANSELC = 0x00;
   
   TRISCbits.TRISC0 = 1; //SWD
   TRISCbits.TRISC1 = 1; //SWC
   TRISCbits.TRISC2 = 0;
   TRISCbits.TRISC3 = 0;
   TRISCbits.TRISC4 = 0; //green led output
   TRISCbits.TRISC5 = 0;
   TRISCbits.TRISC6 = 0;
   TRISCbits.TRISC7 = 0;
   
   TRISAbits.TRISA4 = 0;
   TRISAbits.TRISA5 = 0;
   //TRISA = 0;
   
   TRISBbits.TRISB4 = 0;
   TRISBbits.TRISB5 = 0;
   TRISBbits.TRISB6 = 0;
   TRISBbits.TRISB7 = 0;
   
   //RA1 on positive edge
   IOCAPbits.IOCAP0 = 1;
   IOCAPbits.IOCAP1 = 1;
   
   //Enable interrupts
   INTCONbits.IOCIE = 1;    // Enable IOC Interrups
   INTCONbits.PEIE = 1;     // Enable Perpherial Interrups
   INTCONbits.GIE = 1;      // Enable Global Interrupt
   */
}




