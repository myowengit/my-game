#ifndef __DRV_EEPROM_H__
#define __DRV_EEPROM_H__

#include <stc12c5a60s2.h>
#include "CTypes.h"
#include "drv_iic.h"

uint8_t eeprom_write(uint8_t *buf, uint8_t addr, uint8_t len);
uint8_t eeprom_read(uint8_t *buf, uint8_t addr, uint8_t len);

#endif	///<__DRV_EEPROM_H__
