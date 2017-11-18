/*
 * configuration.c
 *
 * Created: 22/08/2015 20:08:18
 *  Author: Fran
 */ 


#include "includes.h"


void initial_configuration (void)
{
	pin_manager();
	USART_Init(BAUD_PRESCALE);	
	i2c_init();	
	adc_init();
	INT0_enable();
}

void pin_manager(void)
{	
	// Configure UART's pins
	DDRD |=(1<<PIND1);//Digital output TX USART
	DDRD |=(0<<PIND2);//Digital input INT0
	//DDRB |=(1<<PINB0);//Digital output IO8 turn on GLCD
	DDRB |=(1<<PINB1);//Digital output IO9 turn on Yelow LEd
	//CONFIGURATION SDA & SCL PIN of I2C protocol in PORT C
	//Note that is not necessary configure de DDRC´s pin corresponding 
	
	PORTC=0b00110000;// Pin 4 & 5 PULL UP TO I2C PROTOCOL
}





