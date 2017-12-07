
/*
 * main.c
 *
 * Created: 22/08/2015 18:24:54
 *  Author: Fran
 * Code repository: https://github.com/frangarma/eCabinet
 * Repository create on: 8/11/2017
 */ 



#include "includes.h"

unsigned char new_event_timer=0;
unsigned char count_timer =0;
uint8_t error=0;

char mensaje[20];
char message_received [20];
uint8_t array_aux[2];
int *p;
uint16_t aux=0;

uint8_t DataGPIOExpander_xBank_y [3][5]=
{
	{0x00, 0x00, 0x00, 0x00, 0x00},//GPIOExpander1_Bank0-4
	{0x00, 0x00, 0x00, 0x00, 0x00},//GPIOExpander2_Bank0-4
	{0x00, 0x00, 0x00, 0x00, 0x00} //GPIOExpander3_Bank0-4

};

//TODO, parece que la matriz no guarda valores como si fuese una variable global, al modificarlos con los encendidos de las PSU2_1 PSU_2_2 como las operaciones son & no retiene el valor anterior (0 anterior) y por tanto
// no mantiene varios valores activos


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
	
	initial_configuration();//Pin manager; USART_init; I2C_init
	lcd_init();// Set of configuration commands
	test_1();// Display picture during 0.5 seconds
	test_2();// Send through USART "Hello my friend"
	
	sei();//Set enable interrupt	
	TIMER1_enable();
	_delay_ms(1);
	/******* GPIO Expanders configuration******/
	IOBank_Expander_Configuration();
	
	//TODO	
	/***** Code to test all the elements in the circuit *****/
	//This code aims to test all the interns elements in the circuit and have to report the communications' results, specifying the fail element if was the case.
	/*
	/*
	/*
	/*
	/*
	
	
	//TODO
	/***** Code that let us to manage the test throug a menu with different option and the managment is by means of 1 button *****/	
	/* Communication tests
	/* Reset all
	/* Switch on PSU
	/* Parameter reads
	
	
	/****** RESET outputs or defaults values *****/
	IO_Bank_Expander_reset_outputs();
	_delay_ms(500);
		//TODO Put here the same series for the rest of combination and merge all inside a function
	
	/*****Configure output registers to turn on all PSU*****/	
	SwitchOnAllPSU();
	
	
	
	
	
	
	/***** Create here the configuration to put on MUX1 the signal to read from ADC*****/
	eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank0, DataBank0GPIOExpander_2 &=PSU2_VOLTAGE);//This command charge the corresponding value to select PSU2_VOLTAGE signal into channel 0 of ADC IC. 
	eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank0, DataBank0GPIOExpander_2 &= PSU2_CURRENT);//This command charge the corresponding value to select PSU2_CURRENT signal into channel 0 of ADC IC. 
	
// 	PSU_Switch(2,1,1,DataGPIOExpander_xBank_y);
// 	_delay_ms(500);
// 	PSU_Switch(2,2,1,DataGPIOExpander_xBank_y);
	
	
	
	
	//PSU_Switch(2,2,1);
	/******* Headlines *****/
	
	lcd_draw_string(10,1, "Running: ", buffer);//Charge buffer with string
	sprintf(mensaje, "B0_Exp2:%x", DataBank0GPIOExpander_2);
	lcd_draw_string(10,2, mensaje, buffer);//Charge buffer with string	
	lcd_draw_string(10,3, "Voltage:", buffer);//Charge buffer with string	
	lcd_draw_string(10,4, "Current:", buffer);//Charge buffer with string
	lcd_draw_string(10,5, "Current:", buffer);//Charge buffer with string
	lcd_draw_string(10,6, "Current:", buffer);//Charge buffer with string
	lcd_draw_string(10,7, "Error:", buffer);//Charge buffer with string	
	drawBuffer(buffer);
	
    while(1)
	{		
		
		if (new_event_timer)//Currently wait 100 seconds until begin to resets each 2 seconds,but is a new data is write in output register it doesn' wait the 100 seconds only 2
		{
			new_event_timer=0;
			sprintf(mensaje, "%d",count_timer);
			lcd_draw_string(50,1, mensaje, buffer);//Charge buffer with string
			
			WDT_signal();			
			led_activity();
 			
			
				
			//eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank0, (DataBank0GPIOExpander_2 &= PSU2_VOLTAGE));//This command charge the corresponding value to select PSU2_VOLTAGE signal into channel 0 of ADC IC. 
			eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank0, 0xA9);//This command charge the corresponding value to select PSU2_VOLTAGE signal into channel 0 of ADC IC. 
			error=i2c_readReg(ADCAddress, 0x84, array_aux, 2);//
			aux=array_aux[0]<<8;
			aux|= array_aux[1];
			aux/=38.5024;// Voltage 38.5024
			sprintf(mensaje, "%d", aux);
			lcd_draw_string(50,3, mensaje, buffer);//Charge buffer with string			 
			aux=0;
			
			//eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank0, (DataBank0GPIOExpander_2 &= PSU2_CURRENT));//This command charge the corresponding value to select PSU2_CURRENT signal into channel 0 of ADC IC. 
			eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank0, 0xA8);//This command charge the corresponding value to select PSU2_CURRENT signal into channel 0 of ADC IC. 
			error=i2c_readReg(ADCAddress, 0x84, array_aux, 2);
			aux=array_aux[0]<<8;
			aux|= array_aux[1];
			//aux/54;// Current=(Valor leído -2048)/54.0672
			sprintf(mensaje, "%d", aux);
			lcd_draw_string(50,4, mensaje, buffer);//Charge buffer with string
			aux=0;
			
			//eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank0, (DataBank0GPIOExpander_2 &= PSU2_CURRENT));//This command charge the corresponding value to select PSU2_CURRENT signal into channel 0 of ADC IC.
			eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank0, 0xAB);//This command charge the corresponding value to select PSU2_1_CURRENT signal into channel 0 of ADC IC.
			error=i2c_readReg(ADCAddress, 0x84, array_aux, 2);
			aux=array_aux[0]<<8;
			aux|= array_aux[1];
			//aux/=(82);// Current=(Valor leído/820)*10
			sprintf(mensaje, "%d", aux);
			lcd_draw_string(50,5, mensaje, buffer);//Charge buffer with string
			aux=0;
			
			//eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank0, (DataBank0GPIOExpander_2 &= PSU2_CURRENT));//This command charge the corresponding value to select PSU2_CURRENT signal into channel 0 of ADC IC.
			eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank0, 0xAC);//This command charge the corresponding value to select PSU2_2_CURRENT signal into channel 0 of ADC IC.
			error=i2c_readReg(ADCAddress, 0x84, array_aux, 2);
			aux=array_aux[0]<<8;
			aux|= array_aux[1];
			//aux/=(82);// Current=(Valor leído/820)*10
			sprintf(mensaje, "%d", aux);
			lcd_draw_string(50,6, mensaje, buffer);//Charge buffer with string
			aux=0;
			
		
			if (error)
			{
				 sprintf(mensaje, "%d",error);
				 lcd_draw_string(50,7, mensaje, buffer);//Charge buffer with string
			 }
			else
			{ 
				sprintf(mensaje, "%d",error);
				lcd_draw_string(50,7, mensaje, buffer);
			}
			
			drawBuffer(buffer);		
			
			if (count_timer==255)
			{ count_timer=0;}
				
			
		}// end if (new_event_timer)
		
		
		NOP();
			
    } // end while
	return 0;
}// end main

