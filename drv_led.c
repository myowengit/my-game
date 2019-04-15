#include "dev_led.h"
#include <stdio.h>
#define P0_BUFF 0xFF
code unsigned char num_table[] = {
    0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XF8, 0X80, 0X90,0XFF
};

uint8_t num_buff[6] = { 0 };
uint8_t floatNum_buff[6] = { 0 };

void digitron_showFloatNum(float floatnum)
{
    uint8_t n = 6;
    uint8_t i = 6;

    sprintf((char*)floatNum_buff,"%6f",floatnum);
    while (n)
    {
        num_buff[n - 1] = num_table[floatNum_buff[i] - '0'];
        if (floatNum_buff[i] == '.')
        {
            num_buff[n - 1] = num_table[floatNum_buff[i - 1] - '0'] & 0x7f;///<Add decimal points
            i--;
        }
        n--;
        i--;
    }
    num_buff[6] = P0_BUFF;
}

void Ledscan()
{
    uint8_t i = 0;

    for(i = 0;i <= 6;i++)
    {
        P2 = 0xF8 + i;
        P0 = num_buff[i];
    }
}
