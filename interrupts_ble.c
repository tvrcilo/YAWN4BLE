/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "uart.h"
#include "system.h"


/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

  
void interrupt ISR(void)
{
   
   // Determine which flag generated the interrupt
   if(PIR1bits.RCIF)        // If UART Rx Interrupt occured
	{
       
		if(RCSTAbits.OERR) // If over run error, then reset the receiver
		{
			RCSTAbits.CREN = 0;
            __delay_us(10);
			RCSTAbits.CREN = 1;
		}
       
        buffer[cc] = RCREG; // read received character
        cc++;               // increase buffer counter
       
     }
  PIR1bits.RCIF = 0;   //reset interrupt flag
  
 }

