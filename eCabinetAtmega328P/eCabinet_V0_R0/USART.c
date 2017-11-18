/*
 * USART.c
 *
 * Created: 26/09/2015 18:26:12
 *  Author: Fran
 */ 

#include "includes.h"

//The purpose of this function is to initialize the USART.
void USART_Init( unsigned int baud )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(baud>>8);
	UBRR0L = (unsigned char)baud;
	/* Enable receiver and transmitter, enables interrupt on the RXC1 Flag */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	/* Set frame format: 8data, 1 stop bit */
	UCSR0C = (0<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01);	
}

void USART_Transmit_byte( const char byte )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = byte;
}

void USART_Transmit_data(const char * s)
{
	while(*s!=0){
		USART_Transmit_byte(*s);
	*s++;}
}