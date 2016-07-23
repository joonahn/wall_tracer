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
#include "soogo.h"

 int main()
 {
	// Sensor variables,
	// IRF: front, IRB: left-front, IRR: left-rear
	int IRF = 0, IRB = 0, IRR = 0;

	// Debug string
	char str[200];

	//Init functions
	uart_init();

	while(1)
	{
		//Get the sensor values
		//IRF = adc_read(4);
		//IRB = adc_read(2);
		//IRR = adc_read(0);

		IRF = adc_read(5);
		IRB = adc_read(3);
		IRR = adc_read(1);

		// Print Debug string
		sprintf(str, "IRF : %d\n IRB : %d\nIRR : %d\n\n", IRF, IRB, IRR);
		uart_puts(str);

		_delay_ms(1000);
	}
 }