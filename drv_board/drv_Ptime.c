#include <stc12c5a60s2.h>
unsigned char digit[] = {"A   00-01-00"};    ///<时间显示数组
void TimeChange()
{
    digit[11] -= 1;
    if( digit[11] == '/' )
    {
        digit[11] = '9';
        digit[10] -= 1;
        if(digit[10] == '/')
        {
            digit[10] = '5';
            digit[11] = '9';
            digit[8] -= 1;
            if(digit[8] == '/')
            {
                digit[8] = '9';
                digit[7] -= 1;
                if(digit[7] == '/')
                {
                    digit[7] = '5';
                    digit[8] = '9';
                    digit[5] -= 1;
                    if(digit[5] == '/')
                    {
                        digit[5] = '9';
                        digit[4] -= 1;
                        if(digit[4] == '/')
                        {
                            digit[11] = '3';
                            digit[10] = '2';
                            digit[8]  = '9';
                            digit[7]  = '5';
                            digit[5]  = '3';
                            digit[4]  = '2';
                        }

                    }
                }
            }
        }
    }
}
