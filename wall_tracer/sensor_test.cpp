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

 int __s_main()
 {
	// Sensor variables,
	// IRF: front, IRB: left-front, IRH: HEAD
	int IRF = 0, IRB = 0, IRH = 0;

	// Debug string
	char str[200];

	//Init functions
	uart_init();

	while(1)
	{
		//Get the sensor values
		//IRF = adc_read(4);
		//IRB = adc_read(2);
		//IRH = adc_read(0);

		IRB = adc_read(5);
		IRF = adc_read(3);
		IRH = adc_read(1);

		// Print Debug string
		sprintf(str, "IRF : %d\n IRB : %d\nIRH : %d\n\n", IRF, IRB, IRH);
		uart_puts(str);

		_delay_ms(1000);
	}
 }