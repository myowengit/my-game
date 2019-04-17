#ifndef __DRV_PWM_H__
#define __DRV_PWM_H__

#include <stc12c5a60s2.h>
#include "CTypes.h"

void pwm_init();
void pwm_set(uint16_t fre);

#endif ///<__DRV_PWM_H__
