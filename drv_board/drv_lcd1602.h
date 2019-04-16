#ifndef __DRV_LCD1602_H__
#define __DRV_LCD1602_H__

#define LCD1602_DB P0
#define LCD1602_RS P20
#define LCD1602_RW P21
#define LCD1602_E  P12

void LcdWaitReady( void );
void LcdWriteCmd(unsigned char cmd);
void LcdWriteDat(unsigned char dat);
void LcdSetCursor(unsigned char x,unsigned char y);
void LcdShowStr(unsigned char x,unsigned char y,unsigned char *str);
static void InitLcd1602( void );

#endif
