#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

#define ADC_POWER 0x80 
#define ADC_FLAG 0x10 
#define ADC_START 0x08 
#define ADC_SPEEDLL 0x00 //540 clocks
#define ADC_SPEEDL 0x20 //360 clocks
#define ADC_SPEEDH 0x40 //180 clocks
#define ADC_SPEEDHH 0x60

#include <stc12c5a60s2.h>
#include <stdio.h>
#include "CTypes.h"

void adc_init( void );
uint8_t get_AdcResult(uint8_t ch);
float get_voltage(uint8_t ch);
void _cut_result_num(void);

#endif ///<__DRV_ADC_H__
