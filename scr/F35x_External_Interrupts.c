//-----------------------------------------------------------------------------
// F35x_External_Interrupts.c
//-----------------------------------------------------------------------------
// Copyright 2007 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This software shows the necessary configuration to use External Interrupt 0
// (/INT0) or External Interrupt 1 (/INT1) as an interrupt source.  The code
// executes the initialization routines and then spins in an infinite while()
// loop.  If the button on P1.0 (on the target board) is pressed, then the
// edge-triggered /INT0 input on P0.0 will cause an interrupt and toggle the
// LED.
//
// Pinout:
//
// P0.0 - /INT0
// P0.1 - /INT1
//
// P1.0 - SW1 (Switch 1)
// P0.6 - LED1
// P0.7 - LED2
//
// How To Test:
//
// 1) Compile and download code to a 'F35x target board.
// 2) On the target board, connect P1.0_SW J3 to P0.0 for /INT0 and P0.1 for
//    /INT1.
// 3) Press the switches.  Every time a switch is pressed, the P0.6 or P0.7
//    LED should toggle.
//
// Target:         C8051F35x
// Tool chain:     Keil C51 7.50 / Keil EVAL C51
// Command Line:   None
//
//
// Release 1.0
//    -Initial Revision (SM)
//    -19 JUN 2007
//

//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------

#include "F35x_External_Interrupts.h"

//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Ext_Port_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function configures the crossbar and GPIO ports.
//
// Pinout:
//
// P0.0 - digital   open-drain  /INT0
// P0.1 - digital   open-drain  /INT1
// P0.6 - digital   push-pull   LED1
// P0.7 - digital   push-pull   LED2
//
// P1.0 - digital   open-drain  SW1 (Switch 1)
//
//-----------------------------------------------------------------------------
void Ext_Port_Init (void)
{
   //P0MDIN |= 0xC0;                     // P0.6 and P0.7 are digital
   P0MDOUT = 0xC0;                     // P0.6 and P0.7 are push-pull
   //P0MDIN |= 0xC0;                     // P0.6 and P0.7 are digital
   P1MDOUT = 0xFF;                     // P0.6 and P0.7 are push-pull
   XBR1    = 0x40;                     // Enable crossbar and enable
}

//
// Return Value : None
// Parameters   : None
//
// This function configures and enables /INT0 and /INT1 (External Interrupts)
// as negative edge-triggered.
//
//-----------------------------------------------------------------------------
void Ext_Interrupt_Init (void)
{
   Ext_Port_Init ();					//初始化外部中断管脚
   TCON = 0x05;                        // /INT 0 and /INT 1 are edge triggered
   IT01CF = 0x10;                      // /INT0 active low; /INT0 on P0.0;
                                       // /INT1 active low; /INT1 on P0.1
   EX0 = 1;                            // Enable /INT0 interrupts
   EX1 = 1;                            // Enable /INT1 interrupts
}

//-----------------------------------------------------------------------------
// Interrupt Service Routines
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
