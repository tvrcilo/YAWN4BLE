/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

//#if defined(__XC)
//    #include <xc.h>         /* XC8 General Include File */
//#elif defined(HI_TECH_C)
//    #include <htc.h>        /* HiTech General Include File */
//#endif
#include <xc.h> 
#include <htc.h> 
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <pic16lf1459.h>
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "uart.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (ECH, External Clock, High Power Mode (4-20 MHz): device clock supplied to CLKIN pins)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF        // Internal/External Switchover Mode (Internal/External Switchover Mode is enabled)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config CPUDIV = NOCLKDIV// CPU System Clock Selection Bit (CPU system clock divided by 6)
#pragma config USBLSCLK = 48MHz // USB Low SPeed Clock Selection bit (System clock expects 48 MHz, FS/LS USB CLKENs divide-by is set to 8.)
#pragma config PLLMULT = 3x     // PLL Multipler Selection Bit (3x Output Frequency Selected)
#pragma config PLLEN = DISABLED  // PLL Enable Bit (3x or 4x PLL Enabled)
#pragma config STVREN = OFF      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

//This code configures the device as ibeacon

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator(); 
    
    //turn off analog function for port A, B, C
    ANSELA = 0; 
    ANSELC = 0;
    ANSELB = 0;
 
    // enable BLE HM-11 module
    TRISAbits.TRISA5 = 0;           //IRQ output, pin to drive pMOS
    LATAbits.LATA5 = 0;             // turn on pMOS, turn on BLE module
    
    //RESETB, Reset, active low at least in 5ms, specified for BLE HM-11
    TRISAbits.TRISA4 = 0;
    LATAbits.LATA4 = 1;
    __delay_ms(10); 
 
    //interrupt settings
    INTCONbits.GIE  = 1;            // Enable Global interrupt
    INTCONbits.PEIE = 1;            // Enable Peripheral Interrupts
    PIE1bits.RCIE   = 1;            //Enable  rx interrupts
    PIE1bits.TXIE   = 0;            //disable tx interrupts
    
    
    __delay_ms(250);                //BLE start-up time
    set_uart();                     //UART setup
    __delay_ms(200);
  
     
    uart_write_string("AT");            // test command
     __delay_ms(1000);
    uart_write_string("AT+RENEW");      // restores factory defaults
    __delay_ms(500); 
    uart_write_string("AT+RESET");      //reboot HM-11
    __delay_ms(500);
    uart_write_string("AT+MARJ0x1234"); // Set iBeacon Major number to 0x1234 (hexadecimal) 
    __delay_ms(500);
    uart_write_string("AT+MINO0xFA01"); // Set iBeacon Minor number to 0xFA01 (hexadecimal)
    __delay_ms(500);
    uart_write_string("AT+ADVI3");      // Set advertising interval to 5 (546.25 milliseconds)
    __delay_ms(500);
    uart_write_string("AT+NAMENINO");    // Module name
    __delay_ms(500);
    uart_write_string("AT+IBEA1");       // ebable iBeacon mode
   __delay_ms(500);
  
   //Additionally to save power
   
    uart_write_string("AT+ADTY3");      // HM-11 is non connectable  
     __delay_ms(500);
    uart_write_string("AT+DELO2");   // broadcast-only mode to save power
     __delay_ms(500);
    uart_write_string("AT+PWRM0");     //enable auto sleep
    __delay_ms(500);
    uart_write_string("AT+RESET"); //Reboot  HM-11
    __delay_ms(500);
  
   while(1)
   {
   
   }
   
   
   
}