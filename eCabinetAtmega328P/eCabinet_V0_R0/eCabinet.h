/*
 * eCabinet.h
 *
 * Created: 14/11/2017 11:50:03
 *  Author: garciafr
 */ 


#ifndef ECABINET_H_
#define ECABINET_H_

/***** Register address****/
#define GPIOExpander1Address	0x22<<1
#define GPIOExpander2Address	0x23<<1 // In I2C, all writes are even, and reads are odd
#define GPIOExpander3Address	0x26<<1
#define ADCAddress				0x4A

#define OutputPortRegisterBank0 0x08
#define OutputPortRegisterBank1 0x09
#define OutputPortRegisterBank2 0x0A
#define OutputPortRegisterBank3 0x0B
#define OutputPortRegisterBank4 0x0C

#define IORegisterBank0Address		0x18
#define IORegisterBank1Address		0x19
#define IORegisterBank2Address		0x1A
#define IORegisterBank3Address		0x1B
#define IORegisterBank4Address		0x1C

/******IO configuration banks GPIO Expander *****/

#define IOConf_Bank0_Exp1		0x00
#define IOConf_Bank1_Exp1		0xF3
#define IOConf_Bank2_Exp1		0x06
#define IOConf_Bank3_Exp1
#define IOConf_Bank4_Exp1

#define IOConf_Bank0_Exp2		0xA8
#define IOConf_Bank1_Exp2		0x03
#define IOConf_Bank2_Exp2		0x00
#define IOConf_Bank3_Exp2
#define IOConf_Bank4_Exp2

#define IOConf_Bank0_Exp3		0x55
#define IOConf_Bank1_Exp3		0x01
#define IOConf_Bank2_Exp3		0xA8
#define IOConf_Bank3_Exp3		0x4A
#define IOConf_Bank4_Exp3		0x6D

#define PSU_1_1SWITCH			~0X10
#define PSU_1_2SWITCH			~0X40
#define PSU_1_3SWITCH			~0X01
#define PSU_1_4SWITCH			~0X04
#define PSU_1_5SWITCH			~0X10
#define PSU_1_5SOFT_SWITCH		~0X20



#define PSU_2_1SWITCH			~0x10 // Señales activas a 0
#define PSU_2_2SWITCH			~0x40 // Señales activas a 0

#define PSU_3_1SWITCH			~0X02
#define PSU_3_2SWITCH			~0X08
#define PSU_3_3SWITCH			~0X20
#define PSU_3_4SWITCH			~0X80
#define PSU_3_5SWITCH			~0X02

#define PSU_4_2SWITCH			~0X04

#define PSU_5_1SWITCH			~0X80
#define PSU_5_2SWITCH			~0X02

#define PSU_6_2SWITCH			~0X10

#define PSU_7_2SWITCH			~0X80


#define WDT_IN_CONF				0b00010000	//
#define WDT_IN					0X01

#define LED0					~ 0x40			
#define LED1					~ 0x80

/****** MASKS TO ENCODE PSU SIGNAL  *****/

#define MASK_GPIO_EXPAND_2_BANK0 0xF8

/***** MUX SELECT CORRESPONDING SIGNAL *****/

#define PSU2_CURRENT			(0X00 | MASK_GPIO_EXPAND_2_BANK0)
#define PSU2_VOLTAGE			(0X01 | MASK_GPIO_EXPAND_2_BANK0)
#define PSU2_GND_SENSE_VOLTAGE	0X02
#define PSU2_1_IFB				0x03
#define PSU2_2_IFB				0x04


void eCabinetsendCommand_GPIOExpander(uint8_t address, uint8_t register_definition, uint8_t IO);
void IO_Bank_Expander_reset_outputs(void);
void SwitchOnAllPSU(void);
int * eCabinet_getADC(uint8_t address, uint8_t channel);
void eCabinet_getADC_1(uint8_t address, uint8_t channel);
void PSU_Switch (uint8_t PSU_X, uint8_t Out_Y_PSU_X, uint8_t Switch, uint8_t array_aux[][5] );
void WDT_signal(void);
void led_activity(void);


#endif /* ECABINET_H_ */