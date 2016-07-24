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

 int __AS_main()
 {
	// Sensor variables,
	// IRF: front, IRB: left-front, IRH: HEAD
	int IRF = 0, IRB = 0, IRH = 0;

	// Threshold Variables
	int th1 = 500, th2 = 400, med = 350, th3 = 300, th4=200;
	int delta = 0;
	int heading = 0;

	// Debug string
	char str[200];

	//Initialize functions
	uart_init();

	while(1)
	{
		//Get the sensor values
		//IRF = adc_read(4);
		//IRB = adc_read(2);
		//IRH = adc_read(0);

		IRB = adc_read(1);
		IRF = adc_read(3);
		IRH = adc_read(5);
		//ALIGN
		heading = IRF-IRB;

		// Print Debug string
		sprintf(str, "IRF : %d\n IRB : %d\nIRH : %d\n\n", IRF, IRB, IRH);
		uart_puts(str);

		//Make a big turn
		if(IRF<th4)
		{
			// turn_left();
			pwm(1,10);
			pwm(2,7.5);
			uart_puts("out of th4\n\t(10, 7.5)\n");
			continue;
		}

		if(IRF<th3)
		{
			delta = th3-IRF;
			sprintf(str, "in th3-th4 area\n\t(%f, %f)\n", 10-delta/20.0, 10.0);
			uart_puts(str);
			continue;
		}
		else if(IRF<th2)
		{
			if(heading>0)
			{
				sprintf(str, "positive heading\n\t(%f, %f)\n", 10.0, 10-heading/20.0);
				uart_puts(str);
			}
			if(heading<0)
			{
				sprintf(str, "negative heading\n\t(%f, %f)\n", 10-heading/20.0, 10.0);
				uart_puts(str);
			}
			continue;
		}
		else if(IRF<th1)
		{
			delta = IRF-th2;
			sprintf(str, "in th1-th2 area\n\t(%f, %f)\n", 10.0, 10-delta/20.0);
			uart_puts(str);
			continue;
		}
		else
		{
			pwm(1,10);
			pwm(2,7.5);
			uart_puts("out of th1\n");
			continue;
		}

		// Print Debug string
		sprintf(str, "IRF : %d\n IRB : %d\nIRH : %d\n\n", IRF, IRB, IRH);
		uart_puts(str);

		_delay_ms(1000);
	}
 }