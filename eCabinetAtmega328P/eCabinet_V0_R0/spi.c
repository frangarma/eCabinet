/*
 * spi.c
 *
 * Created: 26/09/2015 21:05:01
 *  Author: Fran
 */ 
#include "includes.h"

// Initialize SPI Master Device (with SPI interrupt)
void spi_init_master (void)
{
	// Set MOSI, SCK as Output
	DDRB=(1<<5)|(1<<3);
	
	// Enable SPI, Set as Master
	// Prescaler: Fosc/16, Enable Interrupts
	//The MOSI, SCK pins are as per ATMega8
	SPCR=(1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPIE);
	
	// Enable Global Interrupts
	sei();
}

// Initialize SPI Slave Device
void spi_init_slave (void)
{
	DDRB = (1<<6);     //MISO as OUTPUT
	SPCR = (1<<SPE);   //Enable SPI
}

//Function to send and receive data for both master and slave
unsigned char spi_tranceiver (unsigned char data)
{
	// Load data into the buffer
	SPDR = data;
	
	//Wait until transmission complete
	while(!(SPSR & (1<<SPIF) ));
	
	// Return received data
	return(SPDR);
}


