#include "infrared.h"

uint8_t ircode[5];                          ///<红外解码存储缓存

/*初始化红外,(初始化外部中断0)*/
void InitInfrared( void )
{
    IR_PIN = 1;        ///<make sure INT0 high
    IT0 = 1;
    EX0 = 1;
}
/*定时器0初始化*/
void InitTimer0( void )
{
    AUXR &= 0x7F;		//定时器时钟12T模式
    TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
    TH0 = 0;
    TL0 = 0;
    
    ET0 = 0;        //禁止T0中断
    TF0 = 0;		//清除TF0标志
	TR0 = 0;		//停止T0计数 
}
/*
*函数名称:uint16_t get_high_time( void )
*函数功能:获取高电平时间
*函数参数:无
*/
uint16_t get_high_time( void )
{
    uint16_t temp = 0;

    TH0 = 0;        ///<清零T0计数
    TL0 = 0;
    TR0 = 1;        ///<启动T0计数

    while (IR_PIN)
    {
        if (TH0 > 0xC2)
        {                                     ///<高电平持续时间超过18ms                                 
            break;                           ///<强制退出循环,防止信号异常,程序假死
        }
    }
    TR0 = 0;
    
    temp = TH0 * 256 + TL0;
    return (temp);
}
/*
*函数名称:uint16_t get_low_time(void)
*函数功能:获取低电平时间
*函数参数:无
*/
uint16_t get_low_time(void)
{
    uint16_t temp = 0;

    TH0 = 0;        ///<清零TH1计数初值
    TL0 = 0;
    TR0 = 1;

    while (!IR_PIN)
    {
        if (TH0 > 0xC2)                   ///<低电平持续时间超过18ms
        {                                           ///<强制退出循环,防止信号异常
            break;
        }
    }
    TR0 = 0;
    
    temp = TH0 * 256 + TL0;
    return (temp);
}
/*
*函数名称:static void get_infrared_data( void )
*函数使用:使用与外部中断0
*函数功能:获取红外信号并且解码
*函数参数:无
*/
static void get_infrared_data( void )
{
    uint8_t count1 = 0, count2 = 0;
    uint8_t temp = 0;
    uint16_t time = 0;

    time = get_low_time();              ///<接收并判定9ms低电平

    if ( (time < 0x5BCC) || (time > 0x6690) )
    {                                          ///<超时跳出
        IE0 = 0;                                  ///<退出前清除INT0中断标志位
        return;
    }

    time = get_high_time();             ///<接收判定4.5ms高电平

    if ((time > 0x3600) || (time < 0x2B33))
    {                                               ///<超时跳出
        IE0 = 0;                                    ///<退出前清除INT0中断标志位    
        return;
    }

    for (count1 = 0; count1 < 4; count1++)          ///<循环接收四个字节
    {
        for (count2 = 0; count2 < 8; count2++)      ///<循环接收每个字节的8bit
        {
            time = get_low_time();                  ///<接收560us低电平

            if ((time > 0x86C) || (time < 0x3AC))
            {
                IE0 = 0;                            ///<超时退出
                return;
            }

            time = get_high_time();                 ///<接收每次高电平时间,判定bit值

            if ((time < 0x86C) && (time > 0x3AC))
            {
                temp >>= 1;         ///<低位在前,数据右移,高位为0
            }
            else if ((time < 0x1485) && (time > 0xFC4))
            {
                temp >>= 1;
                temp |= 0x80;       ///<高位置一
            }
            else
            {
                IE0 = 0;
                return;
            }
        }

        ircode[count1] = temp;
    }
    
    IE0 = 0;        ///<清除标志位
}

/*外部中断0服务函数*/
void infrared_interrupt() interrupt 0
{
     get_infrared_data();
}

