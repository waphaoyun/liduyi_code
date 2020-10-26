#ifndef __F35x_ADC0_ExternalInput_H
#define __F35x_ADC0_ExternalInput_H
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <C8051F350.h>                 // SFR declarations
#include <stdio.h>

//-----------------------------------------------------------------------------
// 16-bit SFR Definitions for 'F35x
//-----------------------------------------------------------------------------

sfr16 TMR2RL = 0xCA;                   // Timer2 reload value
sfr16 TMR2 = 0xCC;                     // Timer2 counter
sfr16 ADC0DEC = 0x9A;                  // ADC0 Decimation Ratio Register

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

#define SYSCLK       24500000          // SYSCLK frequency in Hz

#define MDCLK         2457600          // Modulator clock in Hz (ideal is
                                       // (2.4576 MHz)
#define OWR                20          // Desired Output Word Rate in Hz



//sbit LED = P0^7;                       // LED='1' means ON
sbit SW2 = P1^0;                       // SW2='0' means switch pressed

typedef union LONGDATA{                // Access LONGDATA as an
   unsigned long result;               // unsigned long variable or
   unsigned char Byte[4];              // 4 unsigned byte variables
}LONGDATA;

// With the Keil compiler and union byte addressing:
// [0] = bits 31-24, [1] =  bits 23-16, [2] = bits 15-8, [3] = bits 7-0
#define Byte3 0
#define Byte2 1
#define Byte1 2
#define Byte0 3

//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------

void Oscillator_Init (void);
void ADC0_Init(void);
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------


#endif
