/*
 * USART.h
 *
 * Created: 26/09/2015 18:28:50
 *  Author: Fran
 */ 


#ifndef USART_H_
#define USART_H_

void USART_Init( unsigned int baud );
void USART_Transmit_byte( const char byte );
void USART_Transmit_data(const char * s);



#endif /* USART_H_ */