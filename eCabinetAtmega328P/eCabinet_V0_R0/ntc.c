/*
 * ntc.c
 *
 * Created: 15/11/2015 13:35:59
 *  Author: Fran
 */ 
#include "includes.h"


float Vin = 5;     // [V]       Tensión alimentación del divisor
float Rfija = 10000;  // [ohm]     Resistencia fija del divisor
float R25 = 10000;    // [ohm]     Valor de NTC a 25ºC
float Beta = 3977; // [K]      Parámetro Beta de NTC
float T0 = 298.15;   // [K]       Temperatura de referencia en Kelvin a 25 ºC

float Vout = 0;    // [V]       Variable para almacenar Vout
float Rntc = 0;    // [ohm]     Variable para NTC en ohmnios

float TempK = 0;   // [K]       Temperatura salida en Kelvin
float TempC = 0;   // [ºC]      Temperatura salida en Celsius

float get_temp_NTC(void)
{
	Vout=(Vin/1024)*(read_adc(analogPin1));//IO9
	Rntc=(Vout*Rfija)/(Vin-Vout);// Para divisor de tensión con Rntc a masa.
	TempK =(Beta/(log(Rntc/R25)+(Beta/T0)));
	TempC=(TempK-273.15);// Temperature in Celsius
	return TempC;// Temperature in Celsius
}
