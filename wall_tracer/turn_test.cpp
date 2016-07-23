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
 #include "soogo.h"

 #define F_CPU 8000000

  void turn_right();
  void turn_left();
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

 int main()
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

 void turn_right()
 {
	//Rotate left wheel
	PORTD = 0;
	PORTD |= (0<<PD4) | (1<<PD3);
	PORTD |= (1<<PD2);

	//Delay
	_delay_ms(2000);

	//Stop both wheel
	PORTD = 0;
	PORTD |= (1<<PD2);
 }

 void turn_left()
 {
	//Rotate right wheel
	PORTD = 0;
	PORTD |= (1<<PD6) | (0<<PD5);
	PORTD |= (1<<PD2);

	//Delay
	_delay_ms(2000);

	//Stop both wheel
	PORTD = 0;
	PORTD |= (1<<PD2);
 }

