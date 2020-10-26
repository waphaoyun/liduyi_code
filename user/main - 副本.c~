/*
                         \\\|///
                       \\  - -  //
                        (  @ @  )
+---------------------oOOo-(_)-oOOo-------------------------+
|	Author   :YingTao Technology						    |
|	Data     :2013-11-09                                    |
|	Version  :Bata2.1                                       |
|   QQ       :1625874998	                                |
|   Function :                                              |
|												            |
|	History  :			                                    |
|                                                           |
|                             Oooo							|
+-----------------------oooO--(   )-------------------------+
                       (   )   ) /
                        \ (   (_/
                         \_)     
*/
/*
实验名称:   AD差分模式采集（开发板默认程序，直接上点就可以调试）
实验前事项：连接j7，j4，j2，j10的所有跳线帽（PCB板上均有注释），连接串口线（波特率：115200）和 LCD1602屏
操作方法：  调节w1电位器（PCB板上均有注释）
实验结果：  LCD1602实时显示当前电压值，同时串口也会同步显示当前电压

*/  
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include <C8051F350.h>                 // SFR declarations
#include <stdio.h>
#include "1602_4bit.h"                 // SFR declarations
#include	"math.h"
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
#define OWR               960// 20          // Desired Output Word Rate in Hz

#define BAUDRATE       9600          // Baud rate of UART in bps

//sbit LED = P0^7;                       // LED='1' means ON
//sbit SW2 = P1^0;                       // SW2='0' means switch pressed
sbit cd4051_a = P0^0;
sbit cd4051_b = P0^1;
sbit cd4051_c = P0^6;
sbit adc_732_en = P1^0;
sbit adc_732_wr = P1^1;
sbit adc_732_cs = P1^2;
sbit adc_732_a4 = P1^3;
sbit adc_732_a3 = P1^4;
sbit adc_732_a2 = P1^5;
sbit adc_732_a1 = P1^6;
sbit adc_732_a0 = P1^7;

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
void Port_Init (void);
void UART0_Init (void);
void ADC0_Init(void);

//-----------------------------------------------------------------------------
// MAIN Routine
//-----------------------------------------------------------------------------


 
 LONGDATA data_24;
   unsigned long mV;
	 
LONGDATA getdata()
{
		LONGDATA rawValue;
		ADC0MD  = 0x82; 
                     // Spin forever
		while(!AD0INT);                     // Wait till conversion complete
		AD0INT = 0;                         // Clear ADC0 conversion complete flag

		 // Copy the output value of the ADC
		 rawValue.Byte[Byte3] = 0x00;
		 rawValue.Byte[Byte2] = (unsigned char)ADC0H;
		 rawValue.Byte[Byte1] = (unsigned char)ADC0M;
		 rawValue.Byte[Byte0] = (unsigned char)ADC0L;

  

		 return rawValue;   
}
 void Send_Char(unsigned char ch)
{
	 SBUF0 = ch;                             //?????
	 while(TI0 == 0);                        //??????
	 TI0 = 0;                                //????
}
	 
void  delay_ms(unsigned char ms)
{
     unsigned int s;
	 do{
	      s = 24000000L;
		  while(--s)	;   //14T per loop
     }while(--ms);
}


void main (void)
{
	unsigned char iwap,iwapys,i,j,tongdao;	
	unsigned long result;
	LONGDATA vo1,vo2,vo[8]=0;
	unsigned long min;
   PCA0MD &= ~0x40;                    // WDTE = 0 (clear watchdog timer
                                       // enable)

   Oscillator_Init();                  // Initialize system clock
   Port_Init();                        // Initialize Crossbar and GPIO
   UART0_Init();                       // Initialize UART0 for printf's
   ADC0_Init();                        // Initialize ADC0
   LCD_init();
   AD0INT = 0;
   ADC0MD = 0x83;                      // Start continuous conversions
   EA = 1;                             // Enable global interrupts
   LCD_clr();
	 cd4051_a=1;
		 cd4051_b=1;
		 cd4051_c=1;
		 adc_732_en = 0;
adc_732_wr = 0;
adc_732_cs = 0;
adc_732_a4 = 1;
adc_732_a3 = 1;
adc_732_a2 = 1;
adc_732_a1 = 1;
adc_732_a0= 1;
iwap=1;
   while (1) {  
							{
					
						adc_732_a4=iwap/16;
						adc_732_a3=(iwap-adc_732_a4*16)/8;
						adc_732_a2=(iwap-adc_732_a4*16-adc_732_a3*8)/4;
						adc_732_a1=(iwap-adc_732_a4*16-adc_732_a3*8-adc_732_a2*4)/2;
						adc_732_a0=(iwap-adc_732_a4*16-adc_732_a3*8-adc_732_a2*4-adc_732_a1*2);
						i=4;
						
										while(1)
										{
												
											place:	
//														for(i=0;i<8;i++)
												{
														
														cd4051_c=i/4;
														cd4051_b=(i-cd4051_c*4)/2;
														cd4051_a=(i-cd4051_c*4-cd4051_b*2);
														delay_ms(2);
														vo1=getdata();
//														delay_long(1);
														vo2=getdata();
												//	TX1_write2buff(0xaa);
//														while(((vo1.result-vo2.result)>100)||((vo1.result-vo2.result)<-100))
														while(abs(vo1.result-vo2.result)>167772)
														{
																vo1=getdata();
////																delay_long(1);
																vo2=getdata();

														}
														if(11000000<vo1.result)
														{
																switch(i)
																{
																	case 0:
																		i=4;
//																	Send_Char(0xbb);
//														Send_Char(i);
																	goto place;
																	break;
																	case 1:
																		i=0;
//																	Send_Char(0xbb);
//														Send_Char(i);
																	goto place;
																	break;
																	case 2:
																		i=1;
//																	Send_Char(0xbb);
//														Send_Char(i);
																	goto place;
																	break;
																	case 3:
																		i=6;
//																	Send_Char(0xbb);
//														Send_Char(i);
																	goto place;
																	break;
																	case 4:
																		i=3;
//																	Send_Char(0xbb);
//														Send_Char(i);
																	goto place;
																	break;
																	case 5:
																		i=2;
//																	Send_Char(0xbb);
//														Send_Char(i);
																	goto place;
																	break;
																	case 6:
																		i=7;
//																	Send_Char(0xbb);
//														Send_Char(i);
																	goto place;
																	break;
																	case 7:
																		i=5;
//																	Send_Char(0xbb);
//														Send_Char(i);
																	goto place;
																	break;
																	default:
																		i=4;
//																	Send_Char(0xbb);
//														Send_Char(i);
																	goto place;
																}
														}
														else
														{
															for(j=0;j<4;j++)
															{
																	vo[j]=getdata();
															}
															vo1.result=(vo[0].result+vo[1].result+vo[2].result+vo[3].result)/4;
															if(iwap>=0&&iwap<=15)
																iwapys=31-iwap;
															else
																iwapys=iwap-16;
//																	high=vo1>>8;
//																	low=vo1&0x00ff;
																	Send_Char(0xff);
																	Send_Char(0xff);
																	Send_Char(0xcc);
																	Send_Char(0xdd);
																	Send_Char(iwapys);
																	Send_Char(i);
																	Send_Char(vo1.Byte[Byte3]);
																	Send_Char(vo1.Byte[Byte2]);
																	Send_Char(vo1.Byte[Byte1]);
																	Send_Char(vo1.Byte[Byte0]);
																	Send_Char(0xff);
																	Send_Char(0xee);
																	Send_Char(0xee);
																	switch(iwap){
																
																case 1-1:
																iwap=17-1;
																break;
																case 2-1:
																iwap=1-1;
																break;
																case 3-1:
																iwap=2-1;
																break;
																case 4-1:
																iwap=3-1;
																break;
																case 5-1:
																iwap=4-1;
																break;
																case 6-1:
																iwap=5-1;
																break;
																case 7-1:
																iwap=6-1;
																break;
																case 8-1:
																iwap=7-1;
																break;
																case 9-1:
																iwap=8-1;
																break;
																case 10-1:
																iwap=9-1;
																break;
																case 11-1:
																iwap=10-1;
																break;
																case 12-1:
																iwap=11-1;
																break;
																case 13-1:
																iwap=12-1;
																break;
																case 14-1:
																iwap=13-1;
																break;
																case 15-1:
																iwap=14-1;
																break;
																case 16-1:
																iwap=15-1;
																break;
																case 17-1:
																iwap=18-1;
																break;
																case 18-1:
																iwap=19-1;
																break;
																case 19-1:
																iwap=20-1;
																break;
																case 20-1:
																iwap=21-1;
																break;
																case 21-1:
																iwap=22-1;
																break;
																case 22-1:
																iwap=23-1;
																break;
																case 23-1:
																iwap=24-1;
																break;
																case 24-1:
																iwap=25-1;
																break;
																case 25-1:
																iwap=26-1;
																break;
																case 26-1:
																iwap=27-1;
																break;
																case 27-1:
																iwap=28-1;
																break;
																case 28-1:
																iwap=29-1;
																break;
																case 29-1:
																iwap=30-1;
																break;
																case 30-1:
																iwap=31-1;
																break;
																case 31-1:
																iwap=32-1;
																break;
																case 32-1:
																iwap=16-1;
																break;
																default :
																	iwap=17-1;}
																	goto here;
														}
												}
										}
										here:
										;		
												
				}
   }
}

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
//
//   AIN0.2 - ADC0 input
//
//-----------------------------------------------------------------------------
void Port_Init (void)
{
  //P0SKIP = 0x00; 
//P0SKIP = 0;  
	XBR0 = 0x01;                        // UART0 Selected
   XBR1 = 0x40;                        // Enable crossbar and weak pull-ups
   P0MDOUT |= 0xD0;  //0xDF;//                  // TX, LEDs = Push-pull
	P1MDOUT |= 0xFF;                    // TX, LEDs = Push-pull
 //  P2MDOUT |= 0xFF;                    // TX, LEDs = Push-pull
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
   SCON0 = 0x10;                       // SCON0: 8-bit variable bit rate
                                       //        level of STOP bit is ignored
                                       //        RX enabled
                                       //        ninth bits are zeros
                                       //        clear RI0 and TI0 bits
   if (SYSCLK/BAUDRATE/2/256 < 1) {
      TH1 = -(SYSCLK/BAUDRATE/2);
      CKCON |=  0x08;                  // T1M = 1; SCA1:0 = xx
   } else if (SYSCLK/BAUDRATE/2/256 < 4) {
      TH1 = -(SYSCLK/BAUDRATE/2/4);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 01
      CKCON |=  0x01;
   } else if (SYSCLK/BAUDRATE/2/256 < 12) {
      TH1 = -(SYSCLK/BAUDRATE/2/12);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 00
   } else if (SYSCLK/BAUDRATE/2/256 < 48) {
      TH1 = -(SYSCLK/BAUDRATE/2/48);
      CKCON &= ~0x0B;                  // T1M = 0; SCA1:0 = 10
      CKCON |=  0x02;
   } else {
      while (1);                       // Error.  Unsupported baud rate
   }

   TL1 = TH1;                          // Init Timer1
   TMOD &= ~0xf0;                      // TMOD: timer 1 in 8-bit autoreload
   TMOD |=  0x20;
   TR1 = 1;                            // START Timer1
   TI0 = 1;                            // Indicate TX0 ready
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
   ADC0CF = 0x04;                      // Interrupts upon SINC3 filter output
                                       // and uses internal VREF

   ADC0CLK = (SYSCLK/MDCLK)-1;         // Generate MDCLK for modulator.
                                       // Ideally MDCLK = 2.4576MHz

   // Program decimation rate for desired OWR
   ADC0DEC = ((unsigned long) MDCLK / (unsigned long) OWR /
              (unsigned long) 128) - 1;

   ADC0BUF = 0x00;                     // Turn off Input Buffers
   ADC0MUX = 0x76;                     // v= AIN0.7 -  AIN0.6

   ADC0MD = 0x81;                      // Start internal calibration
   while(AD0CALC != 1);                // Wait until calibration is complete

   EIE1   |= 0x00; //0x08;                     // Enable ADC0 Interrupts
   ADC0MD  = 0x80;                     // Enable the ADC0 (IDLE Mode)
}

//-----------------------------------------------------------------------------
// Interrupt Service Routines
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// ADC0_ISR
//-----------------------------------------------------------------------------
//
// This ISR prints the result to the UART. The ISR is called after each ADC
// conversion.
//
//-----------------------------------------------------------------------------
void ADC0_ISR (void) interrupt 10
{
//   static LONGDATA rawValue;
//   unsigned long mV;
//  /// char LCD_valut[10]="xxxx.xxmv";


//   while(!AD0INT);                     // Wait till conversion complete
//   AD0INT = 0;                         // Clear ADC0 conversion complete flag

//   // Copy the output value of the ADC
//   rawValue.Byte[Byte3] = 0x00;
//   rawValue.Byte[Byte2] = (unsigned char)ADC0H;
//   rawValue.Byte[Byte1] = (unsigned char)ADC0M;
//   rawValue.Byte[Byte0] = (unsigned char)ADC0L;

//  

//   mV = rawValue.result*100/ 6710;        // Because of bounds issues, this
//                                       // calculation has been manipulated as
//                                       // shown above
//                                       // (i.e. 2500 (VREF) * 2^24 (ADC result)
//                                       // is greater than 2^32)

//   printf("AIN0.7-AIN0.6: %6ld mV\n",mV);
//   //itoa(mV,strmV);
////   LCD_valut[0] =  ( mV / 100000 ) % 10 + 0x30;  
////   LCD_valut[1] =  ( mV / 10000 ) % 10 + 0x30;
////   LCD_valut[2] =  ( mV / 1000 ) % 10 + 0x30;
////   LCD_valut[3] =  ( mV / 100 ) % 10 + 0x30;
////   LCD_valut[5] =  ( mV / 10 ) % 10 + 0x30;
////   LCD_valut[6] =  ( mV / 1) % 10 + 0x30;
////   LCD_write_string(0,LINE1,"AIN0.7 - AIN0.6:");
////   LCD_write_string(0,LINE2,LCD_valut);
//   
}


//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------




