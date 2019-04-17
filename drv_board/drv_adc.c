#include "drv_adc.h"

uint8_t _adc_num_stoc[6] = {0};


void adc_init( void )
{
    P1ASF |= 0x01;      ///<配置P10为ADC引脚
    ADC_RES = 0;        ///<清除高八位缓冲数据
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    Delay5ms();
}

uint8_t get_AdcResult(uint8_t ch)
{
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ch;
    Delay5ms();
    while(!(ADC_CONTR & ADC_FLAG));
    ADC_CONTR &= ~ADC_FLAG;
    
    return ADC_RES;
}

float get_voltage(uint8_t ch)
{
    uint8_t vol;
    float value;
    vol = get_AdcResult(ch);
    value = 5 * ((float)vol / 256);
    return value;
}

void _cut_result_num(void)
{
    float result = 0;
    
    result = get_voltage(0);
    
    sprintf(_adc_num_stoc,"%.2f",result);
    if( _adc_num_stoc[2] == '0' )
    {
        sprintf(_adc_num_stoc,"%.3f",result);
        if( _adc_num_stoc[3] == '0' )
           sprintf(_adc_num_stoc,"%.2f",result);
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
