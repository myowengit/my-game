#include "uart.h"

bit txdflag = 1;
uint8_t RxdBuff[15] = {0};
uint8_t code _waiting_buff[] = "Waiting...";
uint8_t code _remd_input_buff[] = "Please input passward";
uint8_t code _remd_right_buff[]  = "Wlecome to you!";
uint8_t code _remd_error_buff[]  = "The password is error! Please input again!";

void UartInit(void)		//9600bps@33.1776MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T
	BRT = 0x94;		//设定独立波特率发生器重装值
	AUXR |= 0x01;		//串口1选择独立波特率发生器为波特率发生器
	AUXR |= 0x10;		//启动独立波特率发生器
	
	ES = 1;             ///<使能串口中断
}

void Txdthing(uint8_t *p)
{
	while(txdflag == 1)
	{
		SBUF = *p;
		while(!TI);
		p++;

		if(*p == '\0') 
		{
			//txdflag = 0;
			break;
		}
			
	}
}

void InterruptUART() interrupt 4
{
    uint8_t temp = 0;    ///<临时储存变量
    static uint8_t rev_data_count = 0;
    
	if(RI)
	{
        EA = 0;
		RI = 0;
        
        temp = SBUF;
        if(temp != '\n')    ///<以'\n'作为结束标记
        {
            RxdBuff[rev_data_count] = temp;
            rev_data_count++;
        }
        else
        {
            rev_data_count = 0;
            txdflag = 1;
        }
        EA = 1;
	}
	if(TI)
	{
		TI = 0;
	}
}
