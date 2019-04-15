#include <stc12c5a60s2.h>

static void LcdWaitReady( void )
{
    unsigned char sta;

    LCD1602_DB = 0xFF;
    LCD1602_RS = 0;
    LCD1602_RW = 1;
    /*暂时省缺，延时五毫秒*/
    do
    {
        LCD1602_E = 1;
        sta = LCD1602_DB;
        LCD1602_E = 0;
    }while(sta & 0x80);
}

/*写一字节命令*/
void LcdWriteCmd(unsigned char cmd)
{
    LcdWaitReady();
    LCD1602_RS = 0;
    LCD1602_RW = 0;
    LCD1602_DB = cmd;
    /*暂时省缺，延时五毫秒*/
    LCD1602_E = 1;
    LCD1602_E = 0;
}

/*写一字节数据*/
void LcdWriteDat(unsigned char dat)
{
    LcdWaitReady();
    LCD1602_RS = 1;
    LCD1602_RW = 0;
    LCD1602_DB = dat;
    /*暂时省缺，延时五毫秒*/
    LCD1602_E = 1;
    LCD1602_E = 0;
}
/*设置光标起始地址*/
void LcdSetCursor(unsigned char x,unsigned char y)
{
    unsigned char addr;

    if( y == 0 )
    {
        addr = 0x00 + x;
    }
    else
    {
        addr = 0x40 + x;
    }

    LcdWriteCmd( addr | 0x80 ); ///<设置RAM地址
}

/*在液晶屏上显示字符*/
void LcdShowStr(unsigned char x,unsigned char y,unsigned char *str)
{
    LcdSetCursor(x,y);
    while( *str != '\0' )
    {
        LcdWriteDat( *str++ );
    }
}
static void InitLcd1602( void )
{

    LcdWriteCmd(0x38);
    /*暂时省缺，延时五毫秒*/
    LcdWriteCmd(0x0c);	  //显示器开，光标关闭
    LcdWriteCmd(0x06);	  //文字不动，地址主动加一
    LcdWriteCmd(0x01);	  //清屏

}

