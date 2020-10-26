//-----------------------------------------------------------------------------
// UART.c
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------
#include "UART.h"

extern unsigned char TX_Ready ;
//-----------------------------------------------------------------------------
// Port_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function initializes the GPIO and the Crossbar
//
// Pinout:
//
//   P0.4 - UART TX (digital, push-pull)
//   P0.5 - UART RX (digital, open-drain)
//-----------------------------------------------------------------------------
void UART_Port_Init (void)
{
   XBR0 = 0x01;                        // UART0 Selected

   XBR1 = 0x40;                        // Enable crossbar and weak pull-ups

   P0MDOUT |= 0xD0;                    // TX, LEDs = Push-pull
}

//-----------------------------------------------------------------------------
// UART0_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configure the UART0 using Timer1, for <BAUDRATE> and 8-N-1.
//
//-----------------------------------------------------------------------------
void UART0_Init (void)
{
   UART_Port_Init ();
   SCON0 = 0x10;                       // SCON0: 8-bit variable bit rate
                                       //        level of STOP bit is ignored
                                       //        RX enabled
                                       //        ninth bits are zeros
                                       //        clear RI0 and TI0 bits
   if (SYSCLK/BAUDRATE/2/256 < 1) {
      TH1 = -(SYSCLK/BAUDRATE/2);
      CKCON &= ~0x0B;                  // T1M = 1; SCA1:0 = xx
      CKCON |=  0x08;
   } else if (SYSCLK/BAUDRATE/2/256 < 4) {
      TH1 = -(SYSCLK/BAUDRATE/2/4);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 01                  
      CKCON |=  0x01;
   } else if (SYSCLK/BAUDRATE/2/256 < 12) {
      TH1 = -(SYSCLK/BAUDRATE/2/12);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 00
   } else {
      TH1 = -(SYSCLK/BAUDRATE/2/48);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 10
      CKCON |=  0x02;
   }

   TL1 = TH1;                          // Init Timer1
   TMOD &= ~0xf0;                      // TMOD: timer 1 in 8-bit autoreload
   TMOD |=  0x20;                       
   TR1 = 1;                            // START Timer1
   TI0 = 1;                            // Indicate TX0 ready
   ES0 = 1;                            // Enable UART0 interrupts
   TI0 = 1;                            //声明TX0就绪,可以发送
   TR0 = 1;
}

void Send_Char(unsigned char ch)
{
	 SBUF0 = ch;                             //送入缓冲区
	 while(TI0 == 0);                        //等待发送完毕
	 TI0 = 0;                                //软件清零
}

//发送字符串,调用Send_Char() len字符串长度
void Send_String(unsigned char * str,unsigned int len)
{
    unsigned int k = 0;
    do 
    {
        Send_Char(*(str + k));
        k++;
    } while(k < len);
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------