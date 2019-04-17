#include "drv_pwm.h"

void pwm_init()
{
    CCON = 0;
    CL = 0;
    CH = 0;
    CMOD = 0x00;
    CCAPM0 = 0x42;  
    
    CR = 1;     ///<启动PCA计数器
}

void pwm_set(uint16_t fre)
{
    CCAP0H = CCAP0L = fre;
}
