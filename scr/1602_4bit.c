#include "1602_4bit.h"                 // SFR declarations
////lcd part
//#define          LINE1                             0
//#define          LINE2                             1
//#define          LINE1_HEAD                        0x80
//#define          LINE2_HEAD                        0xC0
//#define          CLEARSCREEN                       LCD_en_com(0x01)
///*************************************/
////change this part at different board
//sbit DB7=P1^3;
//sbit DB6=P1^2;
//sbit DB5=P1^1;
//sbit DB4=P1^0;
//sbit LCD1602_RS=P0^4;   //data command select  1 data  0 command  pin 4 
//sbit LCD1602_RW=P0^3;   //read write select   1 read   0 write     pin 5
//sbit LCD1602_EN=P0^5;   //LCD enable signal             pin 6
///********************************************************************/
void LCD_Prot_Init()      
{
   P0MDOUT = 0xC0;                     	//P1.7背光 P1.6按键

   P1MDOUT = 0xBF;                     //P1口全部为输出

   P1MDIN |= 0x40;					   //P1.6设置成输入

   XBR1    = 0x40;                     // Enable crossbar and enable 
}

void delay(unsigned int n)      
{
    unsigned int i=0,j=0;
    for (i=n;i>0;i--)
     for (j=0;j<120;j++);  
}
void LCD_en_com(unsigned char command)
{
        DB7=(command>>7)%2;
        DB6=(command>>6)%2;
        DB5=(command>>5)%2;
        DB4=(command>>4)%2;
        LCD1602_RS = 0;           //RS 0 
        //LCD1602_RW = 0;                //RW 0 
        LCD1602_EN = 1;        //EN --\|/__        Write command
        delay(2);
        LCD1602_EN = 0;

        DB7=(command>>3)%2;
        DB6=(command>>2)%2;
        DB5=(command>>1)%2;
        DB4=(command>>0)%2;
        LCD1602_RS = 0;           //RS 0 
        //LCD1602_RW = 0;                //RW 0 
        LCD1602_EN = 1;        //EN --\|/__        Write command
        delay(2);
        LCD1602_EN = 0;
}
void LCD_en_dat(unsigned char command)
{
        DB7=(command>>7)%2;
        DB6=(command>>6)%2;
        DB5=(command>>5)%2;
        DB4=(command>>4)%2;
        LCD1602_RS = 1;        //RS 1 
        //LCD1602_RW = 0;                //RW 0 
        LCD1602_EN = 1;        //EN --\|/__        Write data
        delay(2);
        LCD1602_EN = 0;

        DB7=(command>>3)%2;
        DB6=(command>>2)%2;
        DB5=(command>>1)%2;
        DB4=(command>>0)%2;
        LCD1602_RS = 1;        //RS 1 
        //LCD1602_RW = 0;                //RW 0 
        LCD1602_EN = 1;        //EN --\|/__        Write data
        delay(2);
        LCD1602_EN = 0;
}
void LCD_set_xy(unsigned char x,unsigned char y)
{
        unsigned char address;
        if(y == LINE1)        
                address = LINE1_HEAD + x;
        else                         
                address = LINE2_HEAD + x;
        delay(10);
        LCD_en_com(address); 
}
void LCD_write_string(unsigned char x,unsigned char y,unsigned char *s)
{
        LCD_set_xy(x,y); 
        while(*s)  
        {
                LCD_en_dat(*s);   
                s++;
        }
}
void LCD_init(void)
{
	LCD_Prot_Init();//初始化LCD管脚
	delay(50); 
	LCD_en_com(0x33);//原来1602初始化成4位数据线之前必需先初始化成8位(此时命令发送方式是8位格式,但数据线只需接4位)
	delay(10);
	LCD_en_com(0x32);//然后再改到4位线宽,这样初始化才稳定
	delay(10); 
	LCD_en_com(0x28);//四线模式设置
	delay(10);
	LCD_en_com(0x0c);//显示开--对应开关显示控制指令
	delay(10);
	CLEARSCREEN;
	delay(30);
}
void LCD_clr(void)      
{
	LCD_en_com(0x01);
   	delay(1700);
}
/********************************************************************/
//
//void main(void)
//{
//LCD_init();
//   LCD_write_string(0,LINE1,"0123456789abcdef");
//   LCD_write_string(3,LINE2,"Advanced");
//  while(1);                  
//} 