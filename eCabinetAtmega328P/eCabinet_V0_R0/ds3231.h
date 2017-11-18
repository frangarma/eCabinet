/*
 * ds3231.h
 *
 * Created: 21/09/2015 19:46:18
 *  Author: Fran
 */ 


#ifndef DS3231_H_
#define DS3231_H_

#define DS3231_ADDRESS_WRITE	0XD0
#define DS3231_ADDRESS_READ		0XD1
#define DS3231_ADDRESS_SECONDS	0X00
#define DS3231_ADDRESS_MINUTES	0X01
#define DS3231_ADDRESS_HOUR		0X02
#define DS3231_ADDRESS_DAY		0X03	//1-7
#define DS3231_ADDRESS_DATE		0X04	//1-31
#define DS3231_ADDRESS_MONTH	0X05
#define DS3231_ADDRESS_YEAR		0X06	//00-99


void DS3231_SET (uint8_t sec, uint8_t min, uint8_t hour,  uint8_t day,uint8_t date, uint8_t month, uint8_t year);
uint8_t get_hour(void);
uint8_t get_min(void);
uint8_t get_sec(void);
uint8_t get_year(void);
void get_time (void);




#endif /* DS3231_H_ */