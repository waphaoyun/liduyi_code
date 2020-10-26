#ifndef __MIAN_H
#define __MIAN_H
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <stdio.h>
#include "F35x_ADC0_ExternalInput.h"
#include "1602_4bit.h"                
#include "UART.h"
#include "string.h"
#include "Key_events.h"
//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------
sbit LED_TEST1 = P0^7;
sbit LED_TEST2 = P0^6;
char LCD_valut[16]="valut:xxxx.xxmv ";	//8 9 10 11 12
char Data_frame[13]="HDM001C00R00E";	//8 9 10 11 12

idata long tatl_main=0;			   //Ö÷º¯ÊýADÀÛ¼ÓÆ÷

extern idata long vault[16];

extern int AD_flag;

idata long Cardinal=0; 


//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------


#endif
