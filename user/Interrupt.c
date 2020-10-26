//-----------------------------------------------------------------------------
// Ext_Interrupt_Init
//-----------------------------------------------------------------------------
#include "Interrupt.h"

char readCounts = 0;               //已经读取的字符个数,与MAX_LEN比较
bit  readFlag = 0;                //读标志
char idata trdata[10];      //要接收/发送的字符串
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
   static LONGDATA rawValue;
  
   signed long AD_value;
 
   while(!AD0INT);                     // Wait till conversion complete
   AD0INT = 0;                         // Clear ADC0 conversion complete flag

   // Copy the output value of the ADC
   rawValue.Byte[Byte3] = 0x00;
   rawValue.Byte[Byte2] = (unsigned char)ADC0H;
   rawValue.Byte[Byte1] = (unsigned char)ADC0M;
   rawValue.Byte[Byte0] = (unsigned char)ADC0L;

   //                           Vref (mV)
   //   measurement (mV) =   --------------- * result (bits)
   //                       (2^24)-1 (bits)
   //
   //   measurement (mV) =  result (bits) / ((2^24)-1 (bits) / Vref (mV))
   //
   //
   //   With a Vref (mV) of 2500:
   //
   //   measurement (mV) =  result (bits) / ((2^24)-1 / 2500)
   //
   //   measurement (mV) =  result (bits) / ((2^24)-1 / 2500)
   //
   //   measurement (mV) =  result (bits) / (16777215 / 2500)
   //
   //   measurement (mV) =  result (bits) / (6710)

     AD_value = (rawValue.result / 6710);	   // Because of bounds issues, this
   											   // calculation has been manipulated as
                                       		   // shown above
                                       		   // (i.e. 2500 (VREF) * 2^24 (ADC result)
                                       		   // is greater than 2^32)
	printf("AIN0.2 voltage: %4ld mV\n",AD_value);
	//printf("\n");
   	vault[AD_cout]=AD_value;
	AD_cout++;
	//printf("AD_value voltage: %ld mv\n",AD_value);
	if(AD_cout>=16)
	{
		AD_flag=1;//计数标志位溢出标志	
		AD_cout=0;//计数器复位重新计数

	}	
}

void UART0_Interrupt (void) interrupt 4
{
   char rxch;
   char flag=0;
   if(RI0)                     //中断标志 RI0=1 数据完整接收
   {
	RI0 = 0;                           //软件清零
	rxch = SBUF0;
	                         //读缓冲
	trdata[readCounts] = rxch;          //存入数组,供发送

	if(flag==0&&trdata[0]=='H')
	{
		
		readCounts++;
		flag=1;
	}

	else if(flag==1&&trdata[1]=='D')
	{
		readCounts++;
		flag=2;
	}

	else if(flag==2&&trdata[2]=='M')
	{
		readCounts++;
	} 

	if(readCounts>=13)//数据帧接受完毕 
	{
		if(trdata[12]=='E')
		{
			readCounts = 0;
			readFlag = 1;
		}
		else
		{
			readCounts = 0;
			flag=0;
		}
	}

   }
}
//
////-----------------------------------------------------------------------------
//// /INT0 ISR
////-----------------------------------------------------------------------------
////
//// Whenever a negative edge appears on P0.0, LED1 is toggled.
//// The interrupt pending flag is automatically cleared by vectoring to the ISR
////
////-----------------------------------------------------------------------------
//void INT0_ISR (void) interrupt 0
//{
//   //add your code here
//   //LED1 = !LED1;
//
//}
////-----------------------------------------------------------------------------
//// /INT1 ISR
////-----------------------------------------------------------------------------
////
//// Whenever a negative edge appears on P0.1, LED2 is toggled.
//// The interrupt pending flag is automatically cleared by vectoring to the ISR
////
////-----------------------------------------------------------------------------
//void INT1_ISR (void) interrupt 2
//{
//   //add your code here
//   //LED2 = !LED2;
//}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------


