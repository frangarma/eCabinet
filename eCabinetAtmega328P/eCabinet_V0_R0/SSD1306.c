/*
 * SSD1306.c
 *
 * Created: 26/09/2015 18:21:36
 *  Author: Fran
 */ 

#include "includes.h"

extern unsigned char Ascii_1[97][5];//TimesNewRomans_97_5.c

extern uint8_t buffer [1024];//buffer.c


//lcd init de este link
//https://github.com/tibounise/SSD1306-AVR/blob/master/SSD1306.cpp

void lcd_init(void)// Init sequence for 128x64 OLED module
{
	// Turn display off
	sendCommand(SSD1306_DISPLAYOFF);//0XAE
	
	
	
	sendCommand(SSD1306_SETMULTIPLEX);//0XA8
	sendCommand(0X3F);
	
	sendCommand(SSD1306_SETDISPLAYOFFSET);//0XD3
	sendCommand(0x00);					// no offset
	
	//sendCommand_1((SSD1306_SETSTARTLINE | 0x00));//0X40, range from 0x40 to 7F
	sendCommand(SSD1306_SETSTARTLINE);	//0X40
	//sendCommand(0x00);					//LINE 0
	
	//sendCommand(SSD1306_SEGREMAP);	//0XA0, two options: 0XA0 | 0XA1
	sendCommand(0XA1);	//0XA1 ESTA ES UNA SEGUNDA OPCION PARA SEGREMAP
	
	sendCommand(SSD1306_COMSCANDEC);//0XC8, two options: 0XC0 | 0XC8, ALLOWING LAYOUT FLEXIBILITY IN THE OLED MODULE
	//sendCommand(0XC0);
	
	sendCommand(SSD1306_SETCOMPINS);	//0XDA
	sendCommand(0x12);					//
	
	sendCommand(SSD1306_SETCONTRAST);//0X81
	sendCommand(0xCF);
	
	sendCommand(SSD1306_DISPLAYALLON_RESUME);	//0XA4
	
	sendCommand(SSD1306_NORMALDISPLAY);	//0XA6 IF INVERTER CHARGE 0XA7
	//sendCommand(0XA7);
	
	sendCommand(SSD1306_SETDISPLAYCLOCKDIV);//0XD5
	sendCommand(0x80);						// the suggested ratio 0x80

	sendCommand(SSD1306_CHARGEPUMP);	//0X8D	Charge pump Setting
	sendCommand(0x14);					// Enable charge pump
	
	sendCommand(SSD1306_MEMORYMODE);	//0X20
	sendCommand(0x00);					//Horizontal address mode
	
	
	
	sendCommand(SSD1306_SETPRECHARGE);//0XD9
	sendCommand(0xF1);
	

	sendCommand(SSD1306_SETVCOMDETECT);
	sendCommand(0x40);
	
	sendCommand(SSD1306_DISPLAYON);	//0XAF
	
}


void drawPixel(int16_t x, int16_t y)
{//, int16_t color){ //void drawPixel(int16_t x, int16_t y, int16_t color){
	buffer[x+(y/8)*128] |= (1 << (y & 7));
}

void clearBuffer(uint8_t *buff)
{
	memset(buff, 0, 1024);//// void *memset(void *str, int c, size_t n) copies the character c o the first n characters of the string pointed to, by the argument str
}

void clearBuffer_1(uint8_t *buff)
{
	
	//memset(buff, 0, 1024);
	for (uint16_t i= 0;i<1024;i++)
	{
		buffer[i]=0x00;
	}
}


void drawBuffer(uint8_t *buffer)
{
	sendCommand_Plus2B(SSD1306_COLUMNADDR, 0, 127);//0X21, range from 0-127
	sendCommand_Plus2B(SSD1306_PAGEADDR, 0, 7);//0X22, range from 0-7
	
	for (uint16_t i=0; i<1024; i++)
	{
		sendData(buffer[i]);
	}
	
}


void lcd_draw_char(unsigned char column, unsigned char page, unsigned char letter, uint8_t *buff)
{
	uint8_t ascii_offset = 32;
	for(uint8_t i=0; i<5; i++)
	{
		buff[i+((page*128)+column)] = Ascii_1[letter-ascii_offset][i];
	}
}

void lcd_draw_string(uint8_t column, uint8_t page, char *string, uint8_t *buff)
{
	uint8_t i = 0;
	while(string[i] != 0)
	{
		lcd_draw_char(column+(5*i), page, (string[i]), buff);
		i++;
	}
}

void lcd_draw_line_string(uint8_t column, uint8_t page, char *string, uint8_t *buff)
{
	uint8_t i = 0;
	while(string[i] != 0)
	{
		lcd_draw_char(column+(5*i), page, (string[i]), buff);
		i++;
	}
	sendCommand_Plus2B(SSD1306_COLUMNADDR, column, 127);//0X21, range from 0-127
	sendCommand_Plus2B(SSD1306_PAGEADDR, page, 7);//0X22, range from 0-7
	for (uint16_t i=0; i<64; i++)
	{
		sendData(buffer[i]);
	}
}




void OLED_pixel(uint8_t x,uint8_t y)
{
	uint8_t nt;
	uint8_t pagina;
	uint8_t bit;
	pagina = y /8;
	bit= y-(pagina*8);
	nt= buffer[pagina*128+x];
	nt |= 1 << bit;
	buffer[pagina*128+x] = nt;
	sendData(buffer[pagina*128+x]);
}

void sendCommand(uint8_t command)
{
	i2c_start(SSD1306_DEFAULT_ADDRESS);
	i2c_write(command_byte);
	i2c_write(command);
	i2c_stop();
}

void sendCommand_Plus2B(uint8_t command, uint8_t byte_1, uint8_t byte_2)
{
	i2c_start(SSD1306_DEFAULT_ADDRESS);
	i2c_write(command_byte);
	i2c_write(command);
	i2c_write(byte_1);
	i2c_write(byte_2);
	i2c_stop();
}
void sendData(uint8_t data)
{
	i2c_start(SSD1306_DEFAULT_ADDRESS);
	i2c_write(data_byte);
	i2c_write(data);
	i2c_stop();
	NOP();
}
