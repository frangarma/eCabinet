
/*
 * main.c
 *
 * Created: 22/08/2015 18:24:54
 *  Author: Fran
 */ 



#include "includes.h"

unsigned char new_event_timer=0;
unsigned char count_timer =0;

char mensaje[20];
char message_received [20];

unsigned char DataBank0GPIOExpander_1 = 0x00;
unsigned char DataBank1GPIOExpander_1 = 0x00;
unsigned char DataBank2GPIOExpander_1 = 0x00;
unsigned char DataBank3GPIOExpander_1 = 0x00;
unsigned char DataBank4GPIOExpander_1 = 0x00;

unsigned char DataBank0GPIOExpander_2 = 0x00;
unsigned char DataBank1GPIOExpander_2 = 0x00;
unsigned char DataBank2GPIOExpander_2 = 0x00;
unsigned char DataBank3GPIOExpander_2 = 0x00;
unsigned char DataBank4GPIOExpander_2 = 0x00;

unsigned char DataBank0GPIOExpander_3 = 0x00;
unsigned char DataBank1GPIOExpander_3 = 0x00;
unsigned char DataBank2GPIOExpander_3 = 0x00;
unsigned char DataBank3GPIOExpander_3 = 0x00;
unsigned char DataBank4GPIOExpander_3 = 0x00;



//itoa(adc_value, buffer, 10);        //Convert the read value to an ascii string

ISR(INT0_vect)
{
	EIFR |= (1<< INTF0);//Flag interrupt reset
	//Here the code	
}
 
/*	
ISR(USART_RX_vect)
{
	//usart_byte_received=UDR0;
	//if (application_0_state!=ATTENTION_INCOMING_CALL_USART_0) {previus_state=application_0_state; };
	//application_0_state=ATTENTION_INCOMING_CALL_USART_0;	
	
	message_received[n]=UDR0;
	n++;	
	
}*/

/***** TIMER1 COMPA *******/
ISR(TIMER1_COMPA_vect)
{
	new_event_timer=1;
	count_timer++;			
}




int main(void)
{
	enum bool {false, true};
	enum bool myFlag=false;
	int *p;
	initial_configuration();//Pin manager; USART_init; I2C_init
	lcd_init();// Set of configuration commands
	test_1();// Display picture during 2 seconds
	test_2();// Send through USART "Hello my friend"
	test_3(10,1);//Send to lcd "Running: "
	sprintf(mensaje, "%i", count_timer);	
	lcd_draw_string(50,1, mensaje, buffer);//Charge buffer with string
	drawBuffer(buffer);
	
	sei();//Set enable interrupt	
	TIMER1_enable();
	_delay_ms(1);
	/******* GPIO Expanders configuration******/
	eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, IORegisterBank0Address, IOConf_Bank0_Exp1);//Configure IO pins of Bank0 GPIOExpander_1
	eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, IORegisterBank1Address, IOConf_Bank1_Exp1);//Configure IO pins of Bank1 GPIOExpander_1
	eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, IORegisterBank2Address, IOConf_Bank2_Exp1);//Configure IO pins of Bank2 GPIOExpander_1
	
	eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, IORegisterBank0Address, IOConf_Bank0_Exp2);//Configure IO pins of Bank0 GPIOExpander_2
	eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, IORegisterBank1Address, IOConf_Bank1_Exp2);//Configure IO pins of Bank1 GPIOExpander_2
	eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, IORegisterBank2Address, IOConf_Bank2_Exp2);//Configure IO pins of Bank0 GPIOExpander_2
	
	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, IORegisterBank0Address, IOConf_Bank0_Exp3);//Configure IO pins of Bank0 GPIOExpander_3
	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, IORegisterBank1Address, IOConf_Bank1_Exp3);//Configure IO pins of Bank1 GPIOExpander_3
	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, IORegisterBank2Address, IOConf_Bank2_Exp3);//Configure IO pins of Bank0 GPIOExpander_3

	sprintf(mensaje, "B0_Exp2:%x", DataBank0GPIOExpander_2);
	lcd_draw_string(10,2, mensaje, buffer);//Charge buffer with string
	drawBuffer(buffer);
	_delay_ms(500);
	
	/****** RESET outputs or defaults values *****/
	eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank0, DataBank0GPIOExpander_2 |= 0xFF );//Switch off both PSU2 outputs.
	eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, OutputPortRegisterBank0, DataBank0GPIOExpander_1 |= 0xFF );//Switch off both Leds 1&2.
	
	
	_delay_ms(200);
	
	/*****Configure output registers *****/
	eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank0, DataBank0GPIOExpander_2 &= (PSU_2_2SWITCHON & PSU_2_1SWITCHON));//Switch on both PSU
 	_delay_ms(200);
 	eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank0, DataBank0GPIOExpander_2 |= (~ PSU_2_2SWITCHON | ~ PSU_2_1SWITCHON) );//Switch off this PSU
	_delay_ms(200);
	eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank0, DataBank0GPIOExpander_2 &= (PSU_2_2SWITCHON & PSU_2_1SWITCHON));//Switch on both PSU
	
	/***** Create here the configuration to put on MUX1 the signal to read from ADC*****/
	// Put the code here
	
	
	
    while(1)
	{		
		
		if (new_event_timer)//Currently wait 100 seconds until begin to resets each 2 seconds,but is a new data is write in output register it doesn' wait the 100 seconds only 2
		{
			/*Generate a short pulse in WDT_In signal to avoid a WDT time_out*/
			eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, OutputPortRegisterBank2, WDT_IN_CONF| WDT_IN);
			eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, OutputPortRegisterBank2, WDT_IN_CONF);
			
			/****** Activity led0 & Led 1 *****/
 			eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, OutputPortRegisterBank0, DataBank0GPIOExpander_1 &= LED0);//Configure IO pins of Bank2 GPIOExpander_1
			_delay_ms(100);
			eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, OutputPortRegisterBank0, DataBank0GPIOExpander_1 |= ~LED0);//Configure IO pins of Bank2 GPIOExpander_1
			
			new_event_timer=0;
			
			p=eCabinet_getADC(ADCAddress,0);// Currently Channel is not a parameter
			sprintf(mensaje, "%d", *p);
			lcd_draw_string(50,1, mensaje, buffer);//Charge buffer with string
			drawBuffer(buffer);			
			if (count_timer==255)
			{ count_timer=0;}
				
			
		}// end if (new_event_timer)
		
		NOP();
			
    } // end while
	return 0;
}// end main

