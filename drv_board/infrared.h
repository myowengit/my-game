#ifndef __INFRARED_H__
#define __INFRARED_H__

#include <stc12c5a60s2.h>
#include "Ctypes.h"
#include "timer.h"

#define IR_PIN P32

void InitInfrared( void );
void InitTimer0( void );
void infrared_num_make();

#endif  ///<__INFRARED_H__
