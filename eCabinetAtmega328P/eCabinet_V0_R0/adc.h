/*
 * adc.h
 *
 * Created: 07/11/2015 18:45:57
 *  Author: Fran
 */ 


#ifndef ADC_H_
#define ADC_H_

void adc_init(void);
uint16_t read_adc(uint8_t channel);

#endif /* ADC_H_ */