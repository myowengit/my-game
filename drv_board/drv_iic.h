#ifndef __DRV_IIC_H__
#define __DRV_IIC_H__

#include <stc12c5a60s2.h>
#include "CTypes.h"
#include "delay.h"

#define I2C_SCL P36
#define I2C_SDA P37

void iic_start(void);
void iic_stop(void);
bit iic_write(const uint8_t wr_data);
uint8_t iic_read(const bit ack);

#denif	///<__DRV_IIC_H__
