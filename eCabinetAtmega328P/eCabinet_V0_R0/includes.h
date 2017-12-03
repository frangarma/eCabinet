/*
 * includes.h
 *
 * Created: 22/08/2015 19:52:24
 *  Author: Fran
 */ 


#ifndef INCLUDES_H_

#define INCLUDES_H_

#define F_CPU 16000000
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define OUTPUT_1				PINB0
#define OUTPUT_1_ON			PORTB |=(1<<PINB0)//I08
#define OUTPUT_1_OFF		PORTB &= ~(1<<PINB0)
#define OUTPUT_2_ON			PORTB |=(1<<PINB1)//I09
#define OUTPUT_2_OFF		PORTB &= ~(1<<PINB1)//I09
#define OUTPUT_3_ON			PORTB |=(1<<PINB6)//I10
#define OUTPUT_3_OFF		PORTB &= ~(1<<PINB6)//I10
#define AVERAGE_IDLE_TIME	30
#define LONG_IDLE_TIME		60

#define analogPin1	1



#define COMMAND_PRUEBA		"ER_COMANDO PRUEBA "




#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <inttypes.h>
#include <compat/twi.h>
#include <math.h>



#include "configurations.h"
#include "user.h"
#include "i2cmaster.h"
#include "SSD1306.h"
#include "USART.h"
#include "spi.h"
#include "Timer_1.h"
#include "Int0_interruption.h"
#include "adc.h"
#include "ntc.h"
#include "eCabinet.h"
#include "main.h"


extern unsigned char buffer [1024];//define into SSD1306
extern char mensaje[20];
extern uint8_t array_aux[2];//define into main.c

extern unsigned char DataBank0GPIOExpander_1;
extern unsigned char DataBank1GPIOExpander_1;
extern unsigned char DataBank2GPIOExpander_1;
extern unsigned char DataBank3GPIOExpander_1;
extern unsigned char DataBank4GPIOExpander_1;

extern unsigned char DataBank0GPIOExpander_2;
extern unsigned char DataBank1GPIOExpander_2;
extern unsigned char DataBank2GPIOExpander_2;
extern unsigned char DataBank3GPIOExpander_2;
extern unsigned char DataBank4GPIOExpander_2;

extern unsigned char DataBank0GPIOExpander_3;
extern unsigned char DataBank1GPIOExpander_3;
extern unsigned char DataBank2GPIOExpander_3;
extern unsigned char DataBank3GPIOExpander_3;
extern unsigned char DataBank4GPIOExpander_3;

//extern unsigned char DataGPIOExpander_xBank_y [3][5];//defined into eCabinet.c


#endif /* INCLUDES_H_ */