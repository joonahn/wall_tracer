/*
 * turn_test.cpp
 *
 * Created: 2016-07-23 오후 12:07:09
 *  Author: REMOTE
 */ 

 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include <avr/delay.h>
 #include <string.h>
 #include <stdio.h>
 #include "wall_tracer.h"

 #define F_CPU 8000000

  volatile unsigned char value;

  ISR(USART_RXC_vect) {
	value = UDR;
	if(value=='A' || value== 'a')
	{
		turn_left();
	}
	else if(value=='D' || value=='d')
	{
		turn_right();
	}
  }

 int __t_main()
 {
	//Init
	 uart_init();
	 pwm_init();
	 sei();
	 DDRB = 0x6;
	 DDRD = 0x7c;

	 //Make PWM signal
	 pwm(2, 10);
	 pwm(1, 10);

	 //STBY
	 PORTD |= (1<<PD2);

	 
	 while(1)
	 {
	 }

 }

