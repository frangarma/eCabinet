/*
 * user.h
 *
 * Created: 22/08/2015 20:02:43
 *  Author: Fran
 */ 


#ifndef USER_H_
#define USER_H_

unsigned char bcd_to_decimal(unsigned char d);
unsigned char decimal_to_bcd(unsigned char d);
void NOP (void);
void test_1 (void);
void test_2 (void);
void test_3 (unsigned char n, unsigned char j);
void test_4 (void);
void lcd_refresh(void);


#endif /* USER_H_ */