#include "Key_events.h"
void mykey()
{
//	unsigned char addr;
	idata int key_count=0;
	int i=0;
	idata long tatl_key=0;//����128Ҫ�����idata
//	char address[9];
	int key_flag=0;//���������־λ
	//�ܽ��Ѿ���ʼ�����ˣ�	
	while(key==0)
	{
		
		delay(10);//����������ʱ
		key_count++;
		if(key_flag==0)
		{
			key_flag=1; 
		}		
	}
	if(key_flag==1)
	{
		if(key_count<1100)//�̰�������У0��
		{
			//add your code here	
			LCD_clr();
			LCD_write_string(0,LINE1,"I LOVE NOKIA!");

			Cardinal=tatl_main;//����

//			printf("Cardinal voltage: %ld \n",Cardinal);
		}
		if(key_count>=1100)//�������������꣩
		{
//			LCD_clr();
//			LCD_write_string(0,LINE1,"I LOVE NOKIA!");
//			delay(1000);//��ʱ��ʾ
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