/*
 * Timer_1.c
 *
 * Created: 09/10/2015 18:33:11
 *  Author: Fran
 */ 
#include "includes.h"

void TIMER1_enable(void)
{
	TCCR1A = 0;     // set entire TCCR1A register to 0
	TCCR1B = 0;     // same for TCCR1B
	
	// set compare match register to desired timer count
	OCR1A = 15624;// --> 1 SECOND
	//OCR1AH = 0x3D;                      //Load higher byte of 15624 into output compare register
	//OCR1AL = 0x08;                      //Load lower byte of 15624 into output compare register
	
	
	// Turn on CTC modeSet CS10 and CS12 bits for 1024 prescaler
	TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);
	
	//Clear ICF1, clear pending interrupts
	TIFR1 = 1<<ICF1;
	
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);
	
	
	TCNT1H=0;
	TCNT1L=0;	
}

void TIMER1_disable(void)
{TCCR1B=0x00;	}