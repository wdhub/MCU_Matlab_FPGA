#ifndef __1602_H_
#define __1602_H_

void lcd_clear(void);
void lcd_write_string(unsigned char x,unsigned char y,unsigned char *s);
void lcd_init(void);


#endif