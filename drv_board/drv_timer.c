#include "timer.h"

void Timer0Init(void)		//1毫秒@33.1776MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x66;		//设置定时初值
	TH0 = 0x7E;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
    
    ET0 = 1;
}

void InterruptTimer0() interrupt 1
{
    static unsigned int i = 0;
    
    TL0 = 0x66;		//设置定时初值
	TH0 = 0x7E;		//设置定时初值
    i++;
    if( i == 1000 )
    {
        i = 0;
        TimeChange(); 
    }
}

