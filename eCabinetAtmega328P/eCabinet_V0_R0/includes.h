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


extern uint8_t buffer [1024];//define into SSD1306
extern unsigned char h,m,s;//define into user.c
extern unsigned char new_minute;
extern unsigned char new_state_application_0;
extern char mensaje[20];
extern unsigned char actual_time [6];//s,m,h,d,D,y
extern unsigned char initial_program_time[6];//s,m,h,d,D,y
extern unsigned char end_program_time[6];//s,m,h,d,D,y
extern unsigned char program;// 1 if there any program existent
extern unsigned char k;// Used to get the state of active_program() extern
extern unsigned char init;//extern


#endif /* INCLUDES_H_ */