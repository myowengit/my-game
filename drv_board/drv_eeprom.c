#include "drv_eeprom.h"

uint8_t eeprom_write(uint8_t *buf, uint8_t addr, uint8_t len)
{
    uint8_t i = 0;

    while(len > 0)
    {
        while(1)
        {
            /* connect eeprom if overtime break */
            iic_start();
            if(0 == iic_write(0xA2)) 
                break;    		///<success
            iic_stop();
            if (i++ > 100) 
                return 0x11;   	///<fault
        }
        /* write address */
        if(iic_write(addr)) 
            return 0x21;     	///<fault

        while (len > 0)
        {
            /* write data */
            if(iic_write(*buf++)) 
                return 0x22;  	///<fault
            len--;
            addr++;
            if ((addr&0x07) == 0) 
                break;       	///<next page
        }
        iic_stop();              ///<stop current page
    }

    return 0x00;                ///<all write is success
}
uint8_t eeprom_read(uint8_t *buf, uint8_t addr, uint8_t len)
{                 
    uint8_t i = 0;

    while(1)
    {
        /* connect eeprom if overtime break */
        iic_start();
        if (0 == iic_write(0xA2)) 
            break;         		///<success
        iic_stop();
        if (i++ > 100) 
            return 0x11;        ///<fault
    }
    if(iic_write(addr)) 
        return 0x21;            ///<fault

    /* Restart bus to read */
    iic_start();
    if(iic_write(0xA3)) 
        return 0x22;            ///<fault

    while(--len) 
        *buf++ = iic_read(0);    
    *buf = iic_read(1);          ///<no ack read

    iic_stop();

    return 0x00;                ///<read is success
}
