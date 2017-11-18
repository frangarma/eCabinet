#ifndef _I2CMASTER_H
#define _I2CMASTER_H   1




void i2c_init(void);
unsigned char i2c_start(unsigned char addr);
void i2c_start_wait(unsigned char addr);
unsigned char i2c_rep_start(unsigned char addr);
unsigned char i2c_write(uint8_t data);
unsigned char i2c_readAck(void);
unsigned char i2c_readNak(void);
void i2c_stop(void);




#endif
