#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <string.h>
#include <stdio.h>
#include "soogo.h"


int main()
{
	// TODO: check motor is working while the robot is executing delay()
	while(1)
	{
		pwm_init();
		pwm(2, 20);
		delay();
	}

}

void turn_right()
{
	pwm(1, 20);
	__delay_ms(200);
}

void turn_left()
{
	pwm(2,20);
	__delay_ms(200);
}

