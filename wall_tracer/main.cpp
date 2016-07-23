/*
 * for문을 사용한 코드
 *
 * PB1 - PWMA
 * PB2 - PWMB
 * PC0 - IR3
 * PC2 - IR2
 * PC3 - R2
 * PC4 - IR1
 * PC5 - R3
 * PC6 - R1
 */

#define F_CPU 8000000
#define ubrr 51
#define badu 9600

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <string.h>
#include <stdio.h>
#include "wall_tracer.h"

// speed parameters
float speed_straight = 0;
float speed_inner = 0;
float speed_outter = 0;

// adc sensitivity parameter
float adc_sensitivity = 0;

/*
	speed_inner: 회전방향 쪽 바퀴 , speed_outter: 회전 반대 방향 쪽
	바퀴(ex.우회전시 왼쪽바퀴)
*/

int main()
{
	// Sensor variables,
	// IRF: front, IRB: left-back, IRH: HEAD
	int IRF = 0, IRB = 0, IRH = 0; 

	// Threshold Variables
	int th1 = 500, th2 = 450, th3 = 300;

	// Debug string
	char str[200];

	DDRB = 6;
	DDRC = 0;
	DDRD = 0x7c;

	//Initialize UART
	uart_init();

	// VR Value Read
	//parameter_init();
	pwm_init();
	pwm(1, 10);
	pwm(2, 10);

	while (1) {

		//Make the robot move
		PORTD = 0;
		PORTD |= (1<<PD6) | (0<<PD5);
		PORTD |= (0<<PD4) | (1<<PD3);
		PORTD |= (1<<PD2);
		

		//Read Sensor Value
		IRB = adc_read(5);
		IRF = adc_read(3);
		IRH = adc_read(1);

		// Print Debug string
		sprintf(str, "IRF : %d\n IRB : %d\nIRH : %d\n\n", IRF, IRB, IRH);
		uart_puts(str);

		_delay_ms(100);

		//Hello World

		if(IRH>th2)
		{
			turn_right();
			continue;
		}
		else if(IRF>th1)
		{
			//(LEFT, RIGHT) = (1, 0.75)
			pwm(1, 10);
			pwm(2, 7.5);
			continue;
		}
		else if(IRF<th3)
		{
			turn_left();
			continue;
		}
		else if(IRF<th2)
		{
			//(LEFT, RIGHT) = (0.75, 1)
			pwm(1, 7.5);
			pwm(2, 10);
			continue;
		}
		

		pwm(1, 10);
		pwm(2, 10);

	}
}