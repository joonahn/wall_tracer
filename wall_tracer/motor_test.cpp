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