#include "drv_iic.h"

void iic_start(void)
{
    /* Init iic bus position */
    I2C_SDA = 1; 
    I2C_SCL = 1; 
    delay_us(1);      

    /* Pull down SDA and SCL to communication */
    I2C_SDA = 0;
    delay_us(1);      	
    I2C_SCL = 0; 
    delay_us(1);                   
}
void iic_stop(void)
{
    /* Init iic bus position */
    I2C_SCL = 0;
    I2C_SDA = 0;
    delay_us(1);      

    /* Pull up SDA and SCL to stop communication */
    I2C_SCL = 1;
    delay_us(1);                  
    I2C_SCL = 1; 
    delay_us(1);               
}
bit iic_write(const uint8_t wr_data)
{
    uint8_t i;
    bit ack;

    for(i=0; i<8; i++)
    {
        /* write data from high bool to low bool */
        I2C_SDA = wr_data & (0x80>>i);	
        /* change SCL with delay to communication */
        delay_us(3);
        I2C_SCL = 1;              
        delay_us(3); 
        I2C_SCL = 0;               
    }

    /* free SDA to read ack */
    I2C_SDA = 1; 
    delay_us(1);
    I2C_SCL = 1; 
    ack = I2C_SDA; 
    delay_us(1); 
    I2C_SCL = 0;  

    return (ack);
}
uint8_t iic_read(const bit ack)
{
    uint8_t i;
    uint8_t re_data = 0x00;

    I2C_SDA = 1;	///< free SDA bus

    /* order clock to read data */
    for(i=0; i<8; i++)
    {
        I2C_SCL = 1; 
        delay_us(3);
        re_data |= (I2C_SDA ? (0x80>>i): 0x00);
        I2C_SCL = 0; 
        delay_us(3);
    }

    I2C_SDA = ack;                            
    delay_us(1);
    I2C_SCL = 1;                 
    delay_us(1); 
    I2C_SCL = 0;                   

    return (re_data);
}
