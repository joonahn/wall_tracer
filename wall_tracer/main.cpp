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

// adc sensitivity parameter
int dist_bias = 0;
float speed_bias = 0;
int turn_bias = 0;

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
	// Too Loose!
	// int th1 = 500, th2 = 400, med = 350, th3 = 300, th4=200, th5 = 100;
	// new threshold
	int th1 = 450, th2 = 400, th3 = 390, th4=340, th5 = 290;
	int delta = 0;

	//Heading = sensor value difference
	int heading = 0;
	int target_heading = 0;

	// Debug string
	char str[200];

	// PORT Init
	DDRB = 6;
	DDRC = 0;
	DDRD = 0x1F;


	// VR Value Read
	parameter_init();

	// PWM Init
	pwm_init();
	pwm(1, 20);
	pwm(2, 20);

	//Motor Signal Initialization
	PORTD = 0;
	PORTD |= (1<<PD3) | (0<<PD4);
	PORTD |= (1<<PD1) | (0<<PD0);
	PORTD |= (1<<PD2);


	while (1) {
		// Read VR value
		parameter_init();
		th1 = 450 + dist_bias;
		th2 = 400 + dist_bias;
		th3 = 390 + dist_bias;
		th4 = 340 + dist_bias;
		th5 = 290 + dist_bias;

		//Read Sensor Value
		IRB = adc_read(1);
		IRF = adc_read(3);
		IRH = adc_read(5);

		//ALIGN
		heading = IRF-IRB;

		//Set target heading

		if(IRH>300)
		{
			point_turn_right();
			target_heading = 0;
		}

		if(IRF<200)
		{
			pwm(1,20*speed_bias);
			pwm(2,20*speed_bias);

			//_delay_ms(880/speed_bias)
			int sec = (88 / speed_bias);
			for(int i = 0;i<sec;i++)
				_delay_ms(10);

			point_turn_left();

			pwm(1,20*speed_bias);
			pwm(2,20*speed_bias);

			//_delay_ms(1300/speed_bias)
			sec = (130 / speed_bias);
			for(int i = 0;i<sec;i++)
				_delay_ms(10);
			target_heading = 0;
		}
		else if(IRF<th5)
		{
			target_heading = 80;
		}

		else if(IRF<th4)
		{
			// out of th4
			target_heading = 80;
		}
		
		else if(IRF<th3)
		{
			// in th3-th4 area
			target_heading = 50;
		}

		else if(IRF<th2)
		{
			// in th2-th3 area
			target_heading = 0;
		}

		else if(IRF<th1)
		{
			// in th1-th2 area
			target_heading = -50;
			delta = IRF-th2;
		}

		else
		{
			// out of th1
			target_heading = -80;
		}

		//Make current heading to target heading
		if(heading - target_heading > 0)
		{
			// positive heading
			pwm(1,20*speed_bias);
			pwm(2,(20-(heading - target_heading)/20.0)*speed_bias);
		}
		if(heading - target_heading < 0)
		{
			// negative heading
			pwm(1,(20+(heading - target_heading)/20.0)*speed_bias);
			pwm(2,20*speed_bias);
		}
	}
}