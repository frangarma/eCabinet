/*
 * ds3231.c
 *
 * Created: 21/09/2015 19:45:53
 *  Author: Fran
 */ 

/******* WORKS VERY WELL ***********
This link about set & get Time
https://www.ccsinfo.com/forum/viewtopic.php?t=50256
*/

#include "includes.h" 

unsigned char h,m,s;// extern
unsigned char new_minute;//extern
unsigned char actual_time [6];//extern


void DS3231_SET (uint8_t sec, uint8_t min, uint8_t hour,  uint8_t day,uint8_t date, uint8_t month, uint8_t year)
{
	i2c_start(DS3231_ADDRESS_WRITE);
	i2c_write(0x00);// set next input to start at the seconds register
	i2c_write(decimal_to_bcd(sec));
	i2c_write(decimal_to_bcd(min));
	i2c_write(decimal_to_bcd(hour));
	i2c_write(day);//set day of week
	i2c_write(date);//set day of month
	i2c_write(month);
	i2c_write(year);	
	i2c_stop();	
}

uint8_t get_hour(void)
{
	i2c_start(DS3231_ADDRESS_WRITE);
	i2c_write(DS3231_ADDRESS_HOUR);// set next input to start at the seconds register
	i2c_start(DS3231_ADDRESS_READ);
	return bcd_to_decimal(i2c_readAck());	
}

uint8_t get_min(void)
{
	i2c_start(DS3231_ADDRESS_WRITE);
	i2c_write(DS3231_ADDRESS_MINUTES);// set next input to start at the seconds register
	i2c_start(DS3231_ADDRESS_READ);
	return bcd_to_decimal(i2c_readAck());
}

uint8_t get_sec(void)
{
	i2c_start(DS3231_ADDRESS_WRITE);
	i2c_write(DS3231_ADDRESS_SECONDS);// set next input to start at the seconds register	
	i2c_start(DS3231_ADDRESS_READ);	
	return  bcd_to_decimal(	i2c_readAck());
}

uint8_t get_year(void)
{

}

void get_time (void)
{
	actual_time[0]=get_sec();
	actual_time[1]=get_min();
	actual_time[2]=get_hour();	
	if (actual_time[0]==0) {new_minute=1;}
	else {new_minute=0;}
	
}

