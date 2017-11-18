/*
 * Int0_interruption.c
 *
 * Created: 19/03/2015 21:32:14
 *  Author: Usuario
 */ 
#include "includes.h"

void INT0_enable (void)
{
	EICRA |=(1<<ISC01);
	EICRA |=(0<<ISC00);//The falling edge of INT0 generates an interrupt request.
	EIMSK |=(1<<INT0);	
	//sei();//Line in main function
}

void INT0_disable (void)
{
	EICRA=0;
	EIMSK |=(0<<INT0);	
}