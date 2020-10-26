//-----------------------------------------------------------------------------
// F35x_ADC0_ExternalInput.c
//-----------------------------------------------------------------------------
// Copyright 2006 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
// --------------------
//
// This example code for the C8051F350 takes measurements from input A1N0.2
// using ADC0 then prints the results to a terminal window via the UART.
//
// The system is clocked by the internal 24.5MHz oscillator. The completion of
// this conversion in turn triggers an interrupt service routine (ISR). The ISR
// calculates the ADC0 result into the equivalent mV and then prints the value
// to the terminal via printf before starting another conversion.
//
// The analog multiplexer selects A1N2 as the positive ADC0 input.  This
// port is configured as an analog input in the port initialization routine.
// The negative ADC0 input is connected via mux to ground, which provides
// for a single-ended ADC input.
//
// A 100kohm potentiometer may be connected as a voltage divider between
// VREF and AGND on the terminal strip as shown below:
//
// ---------
//          |
//         o| VREF ----|
//         o| GND   ---|<-|
//         o| AIN2     |  |
//         o|    |        |
//         o|     --------
//         o|
//          |
//----------
// C8051F350-TB
//
// Terminal output is done via printf, which directs the characters to
// UART0.
//
// F350 Delta-Sigma ADC
// --------------------
// Please see Silicon Labs Applicaton Note AN217 for more information
// on the C8051F35x Delta-Sigma ADC.  AN217 can be found on the Applications
// webpage by going to the Silicon Labs Microcontrollers homepage
// (www.silabs.com -> select Microcontrollers under "Products at the top) and
// clicking the gray link on the left.
//
// Direct link:
//   http://www.silabs.com/products/microcontroller/applications.asp
//
// F350 Resources:
// ---------------
// Timer1: clocks UART
//
// How To Test:
// ------------
// 1) Download code to a 'F350 device on a C8051F350-TB development board
// 2) Connect serial cable from the transceiver to a PC
// 3) On the PC, open HyperTerminal (or any other terminal program) and connect
//    to the COM port at <BAUDRATE> and 8-N-1
// 4) Connect a variable voltage source (between 0 and Vref)
//    to AIN2, or a potentiometer voltage divider as shown above.
// 5) HyperTerminal will print the voltage measured by the device.
//
// FID:            35X000029
// Target:         C8051F350
// Tool chain:     Keil C51 7.50 / Keil EVAL C51
// Command Line:   None
//
// Release 1.0
//    -Initial Revision (SM / TP)
//    - 8 NOV 2006

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "F35x_ADC0_ExternalInput.h"
//-----------------------------------------------------------------------------
// Oscillator_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This routine initializes the system clock to use the internal 24.5MHz
// oscillator as its clock source.  Also enables missing clock detector reset.
//
//-----------------------------------------------------------------------------
void Oscillator_Init (void)
{
   OSCICN = 0x83;                      // Configure internal oscillator for
                                       // its lowest frequency
   RSTSRC = 0x04;                      // Enable missing clock detector
}


//-----------------------------------------------------------------------------
// ADC0_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Initialize the ADC to use the temperature sensor. (non-differential)
//
//-----------------------------------------------------------------------------
void ADC0_Init (void)
{
   REF0CN |= 0x03;                     // Enable internal Vref
   ADC0CN = 0x00;                      // Gain = 1, Unipolar mode
   ADC0CF = 0x00;                      // Interrupts upon SINC3 filter output
                                       // and uses internal VREF

   ADC0CLK = (SYSCLK/MDCLK)-1;         // Generate MDCLK for modulator.
                                       // Ideally MDCLK = 2.4576MHz

   // Program decimation rate for desired OWR
   ADC0DEC = ((unsigned long) MDCLK / (unsigned long) OWR /
              (unsigned long) 128) - 1;

   ADC0BUF = 0x00;                     // Turn off Input Buffers
   ADC0MUX = 0x08;                     // Select AIN0.2	

   ADC0MD = 0x81;                      // Start internal calibration
   while(AD0CALC != 1);                // Wait until calibration is complete

   EIE1   |= 0x08;                     // Enable ADC0 Interrupts
   ADC0MD  = 0x80;                     // Enable the ADC0 (IDLE Mode)
}


//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
