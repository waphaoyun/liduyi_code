#ifndef __1602_4bit_H
#define __1602_4bit_H

#include <C8051F350.h>                 // SFR declarations
//lcd part
#define          LINE1                             0
#define          LINE2                             1
#define          LINE1_HEAD                        0x80
#define          LINE2_HEAD                        0xC0
#define          CLEARSCREEN                       LCD_en_com(0x01)
/*************************************/
//change this part at different board
sbit DB7=P1^3;
sbit DB6=P1^2;
sbit DB5=P1^1;
sbit DB4=P1^0;
sbit LCD1602_RS=P1^4;   //data command select  1 data  0 command  pin 4 
//sbit LCD1602_RW=P0^3;   //read write select   1 read   0 write     pin 5
sbit LCD1602_EN=P1^5;   //LCD enable signal             pin 6
/********************************************************************/
void LCD_Prot_Init() ;
void delay(unsigned int n);     

void LCD_en_com(unsigned char command);
void LCD_en_dat(unsigned char command);

void LCD_set_xy(unsigned char x,unsigned char y);

void LCD_write_string(unsigned char x,unsigned char y,unsigned char *s);

void LCD_init(void);
void LCD_clr(void);

#endif

