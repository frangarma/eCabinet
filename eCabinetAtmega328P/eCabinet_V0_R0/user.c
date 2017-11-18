/*
 * user.c
 *
 * Created: 23/08/2015 0:07:28
 *  Author: Fran
 */ 

#include "includes.h"

char mensaje[20];

	
void NOP (void) {}
	


void test_1 (void)
{
	sendCommand(0XA7);//Invert display
	drawBuffer(buffer);//For 1024 With command send_Data(data)
	_delay_ms(1000);
	clearBuffer(buffer);
	sendCommand(SSD1306_NORMALDISPLAY);//Invert display
	
}


void test_2 (void)
{
	USART_Transmit_data("Hello my friend \n");	
}

void test_3 (unsigned char n, unsigned char j)
{
	//clearBuffer(buffer);
	lcd_draw_string(n,j, "Running: ", buffer);//Charge buffer with string
	drawBuffer(buffer);//For 1024 With command send_Data(data)
	//_delay_ms(2000);
	
}

void test_4 (void)
{
	
}

/*
void lcd_refresh(void)
{
	adc_value=(read_adc(0)*0.49);
	sprintf(mensaje, "Ch0:%.2i C",adc_value);
	lcd_draw_string(15,2, mensaje, buffer);//Charge buffer with string
	
	get_time();
	sprintf(mensaje, "%.2i:%.2i:%.2i", actual_time[2], actual_time[1],actual_time[0]);
	lcd_draw_string(15,1, mensaje, buffer);//Charge buffer with string
	
	temp_ntc=get_temp_NTC();
	sprintf(mensaje, "Ch1:%.2i C",temp_ntc);
	lcd_draw_string(15,3, mensaje, buffer);//Charge buffer with string
	
	
	if (program)
	{
	sprintf(mensaje,"Prg %.2i:%.2i to %.2i:%.2i", initial_program_time[2], initial_program_time[1],end_program_time[2],end_program_time[1]);
	lcd_draw_string(15,0,mensaje, buffer);//Charge buffer with string
	}
	
	if ((program)&& (k))
	{
		sprintf(mensaje,"Act %.2i:%.2i to %.2i:%.2i", initial_program_time[2], initial_program_time[1],end_program_time[2],end_program_time[1]);
		lcd_draw_string(15,0,mensaje, buffer);//Charge buffer with string		
	}
	
	drawBuffer(buffer);//For 1024 With command send_Data(data)	
}

*/


