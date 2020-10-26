#include "Key_events.h"
void mykey()
{
//	unsigned char addr;
	idata int key_count=0;
	int i=0;
	idata long tatl_key=0;//超过128要定义成idata
//	char address[9];
	int key_flag=0;//按键处理标志位
	//管脚已经初始化过了！	
	while(key==0)
	{
		
		delay(10);//消除抖动延时
		key_count++;
		if(key_flag==0)
		{
			key_flag=1; 
		}		
	}
	if(key_flag==1)
	{
		if(key_count<1100)//短按操作（校0）
		{
			//add your code here	
			LCD_clr();
			LCD_write_string(0,LINE1,"I LOVE NOKIA!");

			Cardinal=tatl_main;//较零

//			printf("Cardinal voltage: %ld \n",Cardinal);
		}
		if(key_count>=1100)//长按操作（定标）
		{
//			LCD_clr();
//			LCD_write_string(0,LINE1,"I LOVE NOKIA!");
//			delay(1000);//延时显示
//			delay(1000);
//			delay(1000);
//			delay(1000);
//			delay(1000);
//			delay(1000);
//			delay(1000);
//			delay(1000);
			//add your code here
		}
		key_flag=0;
	}		
}