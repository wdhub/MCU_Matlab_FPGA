/************************************************************************************

程序名称： 1602显示屏驱动程序    
功能说明:  包括1602初始化,清屏,写字符串等           

************************************************************************************/
 #include "delay.h"
 #include "stc15f2k60s2.h"
 #include <intrins.h>			// 加入此头文件后,可使用_nop_库函数


 sbit RS=P2^0;
 sbit RW=P2^1;
 sbit EN=P2^2;
 


 #define RS_CLR RS=0
 #define RS_SET RS=1

 #define RW_CLR RW=0
 #define RW_SET RW=1

 #define EN_CLR EN=0
 #define EN_SET EN=1

 #define dataport P0


bit lcd_check_busy(void)	//LCD判忙检查
{
	dataport= 0xFF;
	RS_CLR;
	RW_SET;
	EN_CLR;
	_nop_();
	EN_SET;
	return (bit) (dataport & 0x80); 
}

void lcd_write_com(unsigned char com)	//LCD 写指令函数
{
	while(lcd_check_busy());
	RS_CLR;
	RW_CLR;
	EN_SET;
	dataport= com;
	_nop_();
	EN_CLR;
}

void lcd_write_data(unsigned char Data)
{
	while(lcd_check_busy());
	RS_SET;
	RW_CLR;
	EN_SET;
	dataport= Data;
	_nop_();
	EN_CLR;
}

void lcd_clear(void)	//清屏函数
{
	lcd_write_com(0x01);
	DelayMS(5);
}

void lcd_write_string(unsigned char x,unsigned char y,unsigned char *s)	//字符串显示函数
{
	if (y==0)
	{
		lcd_write_com(0x80 + x);
	}
		else 
		{
			lcd_write_com(0xC0 + x);
		}
	 while(*s)
	{
		lcd_write_data(*s);
		s++;
	}
}

/*	 	               //字符显示函数 */
void lcd_write_char(unsigned char x,unsigned char y, unsigned char Data)
{
	if(y==0)
		{
			lcd_write_com(0x80 + x);
		}
		else
		{
			lcd_write_com(0xC0 + x);
		}
	lcd_write_data(Data);
}

void lcd_init(void)		//LCD初始化
{
	lcd_write_com(0x38);
	DelayMS(5);
	lcd_write_com(0x38);
	DelayMS(5);
	lcd_write_com(0x38);
	DelayMS(5);
	lcd_write_com(0x38);
	lcd_write_com(0x08);
	lcd_write_com(0x01);
	lcd_write_com(0x06);
	DelayMS(5);
	lcd_write_com(0x0c);
}