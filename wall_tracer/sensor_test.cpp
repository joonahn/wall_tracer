/*
 * sensor_test.cpp
 *
 * Created: 2016-07-23 오전 11:40:06
 *  Author: REMOTE
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <string.h>
#include <stdio.h>
#include "wall_tracer.h"

 int main()
 {
	// Sensor variables,
	// IRF: front, IRB: left-front, IRH: HEAD
	int IRF = 0, IRB = 0, IRH = 0;
	int vr0, vr1, vr2;

	// Debug string
	char str[200];

	//Initialize functions
	uart_init();

	while(1)
	{
		//Get the sensor values
		IRB = adc_read(1);
		IRF = adc_read(3);
		IRH = adc_read(5);

		vr0 = adc_read(0);
		vr1 = adc_read(2);
		vr2 = adc_read(4);

		// Print Debug string
		sprintf(str, "IRF : %d\n IRB : %d\nIRH : %d\n", IRF, IRB, IRH);
		uart_puts(str);


		// Print Debug string
		sprintf(str, "ADC0 : %d ADC1 : %d ADC2 : %d\n", vr0, vr1, vr2);
		uart_puts(str);

		_delay_ms(1000);
	}
 }