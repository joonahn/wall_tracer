#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <string.h>
#include <stdio.h>
#include "soogo.h"


int __main()
{
	// TODO: check motor is working while the robot is executing delay()--> Yes
	// TODO: implement turn_right, turn_left function --> motor will change
	// TODO: Get sensor value
	uart_init();
	pwm_init();
	DDRB = 0x6;
	DDRD = 0x7c;

	//RIGHT WHEEL
	PORTD = 0;
	PORTD |= (1<<PD6) | (0<<PD5);
	pwm(2, 10);

	//LEFT WHEEL
	PORTD |= (0<<PD4) | (1<<PD3);
	pwm(1, 10);

	//STBY
	PORTD |= (1<<PD2);

	
	while(1)
	{
		_delay_ms(1000);
		uart_transmit('A');
	}

}

void turn_right()
{
	pwm(1, 20);
	_delay_ms(200);
}

void turn_left()
{
	pwm(2,20);
	_delay_ms(200);
}

