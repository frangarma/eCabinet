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

#define PSU_1_1SWITCHON			0X10
#define PSU_1_2SWITCHON			0X40
#define PSU_1_3SWITCHON			0X01
#define PSU_1_4SWITCHON			0X04
#define PSU_1_5SWITCHON			0X10
#define PSU_1_5SOFT_SWITCH		0X20



#define PSU_2_1SWITCHON			~ 0x10 // Señales activas a 0
#define PSU_2_2SWITCHON			~ 0x40 // Señales activas a 0

#define PSU_3_1SWITCHON			0X02
#define PSU_3_2SWITCHON			0X08
#define PSU_3_3SWITCHON			0X20
#define PSU_3_4SWITCHON			0X80
#define PSU_3_5SWITCHON			0X02

#define PSU_4_2SWITCHON			0X04

#define PSU_5_1SWITCHON			0X80
#define PSU_5_2SWITCHON			0X02

#define PSU_6_2SWITCHON			0X10

#define PSU_7_2SWITCHON			0X80


#define WDT_IN_CONF				0b00010000	//
#define WDT_IN					0X01

#define LED0					~ 0x40			
#define LED1					~ 0x80


void eCabinetsendCommand_GPIOExpander(uint8_t address, uint8_t register_definition, uint8_t IO);
int * eCabinet_getADC(uint8_t address, uint8_t channel);



#endif /* ECABINET_H_ */