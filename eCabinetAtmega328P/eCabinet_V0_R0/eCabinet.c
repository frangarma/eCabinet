/*
 * eCabinet.c
 *
 * Created: 14/11/2017 11:49:46
 *  Author: garciafr
 */ 

#include "includes.h"

//#define Signal_WDT() eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, OutputPortRegisterBank2, WDT_IN)

void eCabinetsendCommand_GPIOExpander(uint8_t address, uint8_t register_definition, uint8_t IO)
{
	i2c_start(address);
	i2c_write(register_definition);
	i2c_write(IO);
	i2c_stop();
}


/***** Link information for function: https://www.tutorialspoint.com/cprogramming/c_return_arrays_from_function.htm *****/

int * eCabinet_getADC(uint8_t address, uint8_t channel)
{
	static int r[2];
	i2c_start(address<<1);
	i2c_write(0x84);// Command: single ended, channel 0, internal reference off and A/D converter ON
	i2c_start(address);// Repeat start condition
	for (int i=0;i<2;i++)
	{r[i]=i2c_readAck();}
	i2c_stop();
	return r;
}

