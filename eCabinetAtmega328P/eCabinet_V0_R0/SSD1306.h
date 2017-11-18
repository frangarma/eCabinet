/*
 * SSD1306.h
 *
 * Created: 26/09/2015 18:13:04
 *  Author: Fran
 */ 


#ifndef SSD1306_H_
#define SSD1306_H_

#define SLAVE_OLED_WRITE	0b01111000	// Slave address + write
#define SLAVE_OLED_WRITE_ERRONEO	0b11111000	// Slave address + write

#define data_byte		0X40
#define command_byte	0X00

#define SSD1306_DEFAULT_ADDRESS 0x78
#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR 0x22
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_SWITCHCAPVCC 0x2
#define SSD1306_NOP 0xE3

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64
#define SSD1306_BUFFERSIZE (SSD1306_WIDTH*SSD1306_HEIGHT)/8

#define I2C_READ    1
#define I2C_WRITE   0

#define i2c_read(ack)  (ack) ? i2c_readAck() : i2c_readNak(); 


void lcd_init(void);
void drawPixel(int16_t x, int16_t y);
void clearBuffer(uint8_t *buff);
void clearBuffer_1(uint8_t *buff);
void drawBuffer(uint8_t *buffer);
void lcd_draw_char(unsigned char column, unsigned char page, unsigned char letter, uint8_t *buff);
void lcd_draw_string(uint8_t column, uint8_t page, char *string, uint8_t *buff);
void lcd_draw_line_string(uint8_t column, uint8_t page, char *string, uint8_t *buff);
void OLED_pixel(uint8_t x,uint8_t y);
void sendCommand(uint8_t command);
void sendCommand_Plus2B(uint8_t command, uint8_t byte_1, uint8_t byte_2);
void sendData(uint8_t data);


#endif /* SSD1306_H_ */