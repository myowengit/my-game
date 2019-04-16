#ifndef __UART_H__
#define __UART_H__

#include <stc12c5a60s2.h>
#include "CTypes.h"

extern  uint8_t RxdBuff[15];
extern uint8_t code _waiting_buff[];
extern uint8_t code _remd_right_buff[];
extern uint8_t code _remd_error_buff[];
extern uint8_t code _remd_input_buff[];

void UartInit(void);
void Txdthing(uint8_t *p);

#endif  ///<__UART_H
