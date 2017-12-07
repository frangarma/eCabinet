/*
 * eCabinet.c
 *
 * Created: 14/11/2017 11:49:46
 *  Author: garciafr
 */ 

#include "includes.h"

// unsigned char DataGPIOExpander_xBank_y [3][5]=
// {
// 	{0x00, 0x00, 0x00, 0x00, 0x00},//GPIOExpander1_Bank0-4
// 	{0x00, 0x00, 0x00, 0x00, 0x00},//GPIOExpander2_Bank0-4
// 	{0x00, 0x00, 0x00, 0x00, 0x00},//GPIOExpander3_Bank0-4
// 	
// };

//#define Signal_WDT() eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, OutputPortRegisterBank2, WDT_IN)

void eCabinetsendCommand_GPIOExpander(uint8_t address, uint8_t register_definition, uint8_t IO)
{
	i2c_start(address);
	i2c_write(register_definition);
	i2c_write(IO);
	i2c_stop();
}


/***** Link information for function: https://www.tutorialspoint.com/cprogramming/c_return_arrays_from_function.htm *****/

int * eCabinet_getADC(uint8_t address, uint8_t channel)
{
	static int r[2];
	i2c_start(address);
	i2c_write(0x84);// Command: single ended, channel 0, internal reference off and A/D converter ON
	i2c_start(address);// Repeat start condition
	for (int i=0;i<2;i++)
	{r[i]=i2c_readAck();}
	i2c_stop();
	return r;
}

void eCabinet_getADC_1(uint8_t address, uint8_t channel)
{
	
	i2c_start(address<<1);
	i2c_write(0x84);// Command: single ended, channel 0, internal reference off and A/D converter ON
	i2c_start(address>>1);// Repeat start condition
 	array_aux[0]=i2c_readAck();
 	array_aux[1]=i2c_readNak();
	i2c_stop();
	
}

/****** Relation matrix between PSU output and GPIOExpander_N-BANk_n number position*****/
//The values OxFF is in the place that register de actual value of DATA BANK_x GPIO Expander_y
//Try to solve this using struct and pointer
unsigned char Mat_ExpandBank[28][5]=
{
	
		// PSU1_1					PSU1_2						PSU1_3						PSU1_4						NC
		{ GPIOExpander3Address,		GPIOExpander3Address,		GPIOExpander3Address,		GPIOExpander3Address,		0						},
		{ OutputPortRegisterBank2,	OutputPortRegisterBank2,	OutputPortRegisterBank3,	OutputPortRegisterBank3,	0						},
		{ PSU_1_1SWITCH,			PSU_1_2SWITCH,				PSU_1_3SWITCH,				PSU_1_4SWITCH,				0						},	
		{ 0xFF,						0xFF,						0xFF,						0xFF,						0						}, //DataBank_yGPIOExpander_x
		// PSU2_1					PSU2_2						NC							NC							NC
		{ GPIOExpander2Address,		GPIOExpander2Address,		0,							0,							0						},
		{ OutputPortRegisterBank0,	OutputPortRegisterBank0,	0,							0,							0						},
		{ PSU_2_1SWITCH,			PSU_2_2SWITCH,				0,							0,							0						},
		{ 0xFF,						0xFF,						0,							0,							0						}, //DataBank_yGPIOExpander_x
		// PSU3_1					PSU3_2						PSU3_3						PSU3_4						PSU3_5
		{ GPIOExpander3Address,		GPIOExpander3Address,		GPIOExpander3Address,		GPIOExpander3Address,		GPIOExpander3Address	},
		{ OutputPortRegisterBank0,	OutputPortRegisterBank0,	OutputPortRegisterBank0,	OutputPortRegisterBank0,	OutputPortRegisterBank1	},	
		{ PSU_3_1SWITCH,			PSU_3_2SWITCH,				PSU_3_3SWITCH,				PSU_3_4SWITCH,				PSU_3_5SWITCH			},		
		{ 0xFF,						0xFF,						0xFF,						0xFF,						0xFF					}, //DataBank_yGPIOExpander_x
		// NC						PSU4_2						NC							NC							NC			
		{ 0,						GPIOExpander2Address,		0,							0,							0			     		},
		{ 0,						OutputPortRegisterBank0,	0,							0,							0 						},
		{ 0,						PSU_4_2SWITCH,				0,							0,							0						},	
		{ 0,						0xFF,						0,							0,							0						}, //DataBank_yGPIOExpander_x
		// PSU5_1					PSU5_2						PSU3_3						PSU3_4						PSU3_5
		{ GPIOExpander3Address,		GPIOExpander3Address,		0,							0,							0						},
		{ OutputPortRegisterBank3,	OutputPortRegisterBank4,	0,							0,							0					    },
		{ PSU_5_1SWITCH,			PSU_5_2SWITCH,				0,							0,							0						},	
		{ 0xFF,						0xFF,						0,							0,							0						}, //DataBank_yGPIOExpander_x
		// NC						PSU6_2						NC							NC							NC
		{ 0,						GPIOExpander3Address,		0,							0,							0						},
		{ 0,						OutputPortRegisterBank4,	0,							0,							0						},
		{ 0,						PSU_6_2SWITCH,				0,							0,							0						},	
		{ 0,						0xFF,						0,							0,							0						}, //DataBank_yGPIOExpander_x
		// NC						PSU7_2						NC							NC							NC
		{ 0,						GPIOExpander3Address,		0,							0,							0						},
		{ 0,						OutputPortRegisterBank4,	0,							0,							0						},
		{ 0,						PSU_7_2SWITCH,				0,							0,							0						},	
		{ 0,						0xFF,						0,							0,							0						}, //DataBank_yGPIOExpander_x
			
};

unsigned char MauxOutputRBank [5] = {OutputPortRegisterBank0, OutputPortRegisterBank1, OutputPortRegisterBank2, OutputPortRegisterBank3, OutputPortRegisterBank4};


//http://www.zator.com/Cpp/E4_3_8.htm
void PSU_Switch (uint8_t PSU_X, uint8_t Out_Y_PSU_X, uint8_t Switch, uint8_t array_aux[][5] )
{
	uint8_t aux=0;
	
	
	if (Switch)
	{
		array_aux[PSU_X-1][Out_Y_PSU_X-1]= ( Mat_ExpandBank [(PSU_X-1)*4+3][(Out_Y_PSU_X-1)] &= Mat_ExpandBank [(PSU_X-1)*4+2][(Out_Y_PSU_X-1)] ) ;
	}
 	else
	{ 
		array_aux[PSU_X-1][Out_Y_PSU_X-1]= ( Mat_ExpandBank [(PSU_X-1)*4+3][(Out_Y_PSU_X-1)] |= ~(Mat_ExpandBank [(PSU_X-1)*4+2][(Out_Y_PSU_X-1)])) ; 
	}	
	array_aux[1][0]&=array_aux[1][1];
	//void eCabinetsendCommand_GPIOExpander(uint8_t address, uint8_t register_definition, uint8_t IO)
	eCabinetsendCommand_GPIOExpander(Mat_ExpandBank [(PSU_X-1)*4][(Out_Y_PSU_X-1)], Mat_ExpandBank [(PSU_X-1)*4+1][(Out_Y_PSU_X-1)], array_aux[PSU_X-1][Out_Y_PSU_X-1]);
}

/***** This function aims is to configure all the IO of the three GPIO Expander and Banks from 0 to 4 according to hardware desing *****/
IOBank_Expander_Configuration()
{
eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, IORegisterBank0Address, IOConf_Bank0_Exp1);//Configure IO pins of Bank0 GPIOExpander_1
eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, IORegisterBank1Address, IOConf_Bank1_Exp1);//Configure IO pins of Bank1 GPIOExpander_1
eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, IORegisterBank2Address, IOConf_Bank2_Exp1);//Configure IO pins of Bank2 GPIOExpander_1

eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, IORegisterBank0Address, IOConf_Bank0_Exp2);//Configure IO pins of Bank0 GPIOExpander_2
eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, IORegisterBank1Address, IOConf_Bank1_Exp2);//Configure IO pins of Bank1 GPIOExpander_2
eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, IORegisterBank2Address, IOConf_Bank2_Exp2);//Configure IO pins of Bank0 GPIOExpander_2

eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, IORegisterBank0Address, IOConf_Bank0_Exp3);//Configure IO pins of Bank0 GPIOExpander_3
eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, IORegisterBank1Address, IOConf_Bank1_Exp3);//Configure IO pins of Bank1 GPIOExpander_3
eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, IORegisterBank2Address, IOConf_Bank2_Exp3);//Configure IO pins of Bank0 GPIOExpander_3
eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, IORegisterBank3Address, IOConf_Bank3_Exp3);//Configure IO pins of Bank0 GPIOExpander_3
eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, IORegisterBank4Address, IOConf_Bank4_Exp3);//Configure IO pins of Bank0 GPIOExpander_3
}

void WDT_signal(void)
{
eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, OutputPortRegisterBank2, WDT_IN_CONF| WDT_IN);
eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, OutputPortRegisterBank2, WDT_IN_CONF);	
}

void led_activity(void)
{
	eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, OutputPortRegisterBank0, DataBank0GPIOExpander_1 &= LED0);//Configure IO pins of Bank2 GPIOExpander_1
	_delay_ms(100);
	eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, OutputPortRegisterBank0, DataBank0GPIOExpander_1 |= ~LED0);//Configure IO pins of Bank2 GPIOExpander_1
}

/***** This function aims to reset every ouputs Baknk of every GPIO Expander in order to switch off all the hardware   *****/
void IO_Bank_Expander_reset_outputs(void)
{
	

	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, OutputPortRegisterBank2, DataBank2GPIOExpander_3 |= 0xFF );//Switch off both PSU1 outputs PSU1_1 & PSU1_2
	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, OutputPortRegisterBank3, DataBank3GPIOExpander_3 |= 0xFF );//Switch off both PSU1 outputs PSU1_3 & PSU1_4 & PSU_1_5 & PSU1_5_SOFT & PSU_5_1
	eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank0, DataBank0GPIOExpander_2 |= 0xFF );//Switch off both PSU2 outputs PSU2_1 & PSU2_2
	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, OutputPortRegisterBank0, DataBank0GPIOExpander_3 |= 0xFF );//Switch off both PSU3 outputs PSU3_1 & PSU3_2 & PSU3_3 & PSU3_4
	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, OutputPortRegisterBank1, DataBank1GPIOExpander_3 |= 0xFF );//Switch off both PSU3 outputs PSU3_5
	eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank1, DataBank1GPIOExpander_2 |= 0xFF );//Switch off both PSU4 outputs PSU4_2
	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, OutputPortRegisterBank4, DataBank4GPIOExpander_3 |= 0xFF );//Switch off both PSU5&PSU6&PSU7 outpus PSU5_2 & PSU_6_2 & PSU_7_2

	eCabinetsendCommand_GPIOExpander(GPIOExpander1Address, OutputPortRegisterBank0, DataBank0GPIOExpander_1 |= 0xFF );//Switch off both Leds 1&2.

}

/***** This function aims to switch on all the PSU  *****/
void SwitchOnAllPSU(void)
{
	

	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, OutputPortRegisterBank2, DataBank2GPIOExpander_3 &= (PSU_1_1SWITCH & PSU_1_2SWITCH));//Switch on both output PSU1_1 & PSU1_2
	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, OutputPortRegisterBank3, DataBank3GPIOExpander_3 &= (PSU_1_3SWITCH & PSU_1_4SWITCH));//Switch on both output PSU1_3 & PSU1_4
	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, OutputPortRegisterBank3, DataBank3GPIOExpander_3 &= (PSU_1_5SWITCH));//Switch on both output PSU1_5
	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, OutputPortRegisterBank3, DataBank3GPIOExpander_3 &= (PSU_1_5SOFT_SWITCH));//Switch on both output PSU1_5_SOFT

	eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank0, DataBank0GPIOExpander_2 &= (PSU_2_2SWITCH & PSU_2_1SWITCH));//Switch on both output PSU2_1 & PSU2_2

	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, OutputPortRegisterBank0, DataBank0GPIOExpander_3 &= (PSU_3_1SWITCH & PSU_3_2SWITCH & PSU_3_3SWITCH & PSU_3_4SWITCH));//Switch on both output PSU3_1 & PSU3_3 & PSU3_2 & PSU3_4
	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, OutputPortRegisterBank1, DataBank1GPIOExpander_3 &= (PSU_3_5SWITCH));//Switch on both output PSU3_5

	eCabinetsendCommand_GPIOExpander(GPIOExpander2Address, OutputPortRegisterBank1, DataBank1GPIOExpander_2 &= (PSU_4_2SWITCH));//Switch on both output PSU4_2

	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, OutputPortRegisterBank3, DataBank3GPIOExpander_3 &= (PSU_5_1SWITCH));//Switch on both output PSU5_1
	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, OutputPortRegisterBank4, DataBank4GPIOExpander_3 &= (PSU_5_2SWITCH));//Switch on both output PSU5_2

	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, OutputPortRegisterBank4, DataBank4GPIOExpander_3 &= (PSU_6_2SWITCH));//Switch on both output PSU6_2
	eCabinetsendCommand_GPIOExpander(GPIOExpander3Address, OutputPortRegisterBank4, DataBank4GPIOExpander_3 &= (PSU_7_2SWITCH));//Switch on both output PSU7_2
	
}