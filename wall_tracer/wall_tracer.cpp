/*
 * main2.cpp
 *
 * Created: 2016-07-10 오후 6:17:00
 *  Author: HyunSung Kim
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
extern float speed_straight;
extern float speed_inner;
extern float speed_outter;

// adc 채널을 선택하고 해당 채널에서 analog값을 읽어서 반환해주는 함수
int adc_read(int channel)
{
	int analog;

	/* select channel */
	switch (channel) {
	case 0:
		ADMUX = 1 << REFS0 | 0 << MUX2 | 0 << MUX1 | 0 << MUX0;
		break;
	case 1:
		ADMUX = 1 << REFS0 | 0 << MUX2 | 0 << MUX1 | 1 << MUX0;
		break;
	case 2:
		ADMUX = 1 << REFS0 | 0 << MUX2 | 1 << MUX1 | 0 << MUX0;
		break;
	case 3:
		ADMUX = 1 << REFS0 | 0 << MUX2 | 1 << MUX1 | 1 << MUX0;
		break;
	case 4:
		ADMUX = 1 << REFS0 | 1 << MUX2 | 0 << MUX1 | 0 << MUX0;
		break;
	case 5:
		ADMUX = 1 << REFS0 | 1 << MUX2 | 0 << MUX1 | 1 << MUX0;
		break;
	case 6:
		ADMUX = 1 << REFS0 | 1 << MUX2 | 1 << MUX1 | 0 << MUX0;
		break;
	case 7:
		ADMUX = 1 << REFS0 | 1 << MUX2 | 1 << MUX1 | 1 << MUX0;
		break;
	}

	ADCSRA = 1 << ADEN | 1 << ADPS0 | 1 << ADPS1 | 1 << ADPS2;

	/*	read analog value */
	ADCSRA = 1 << ADSC | ADCSRA;
	while (ADCSRA & (1 << ADSC))
		;
	analog = ADCW;

	delay();

	return analog;
}

//학생이 설정한 가변 저항 값을 읽고 그 값에 따라서 parameter를 설정해주는 함수
void parameter_init()
{
	int PM1 = 0, PM2 = 0, PM3 = 0;

	PM1 = adc_read(6);
	PM2 = adc_read(3);
	PM3 = adc_read(5);

	switch (PM1 % 100) // speed parameter
	{
	case 0:
	case 1:
	case 2:
		speed_straight = 10;
		speed_inner = 3;
		speed_outter = 7;
		break;
	case 3:
	case 4:
		speed_straight = 10;
		speed_inner = 3;
		speed_outter = 7;
		break;
	case 5:
	case 6:
		speed_straight = 10;
		speed_inner = 3;
		speed_outter = 7;
		break;
	case 7:
	case 8:
		speed_straight = 10;
		speed_inner = 3;
		speed_outter = 7;
		break;
	case 9:
	case 10:
		speed_straight = 10;
		speed_inner = 3;
		speed_outter = 7;
		break;
	}
	switch (PM2 % 100) // sensor sensitivity parameter
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	break;
	}
	switch (PM3 % 100) // Not decisive
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	break;
	}
}

// PB1과 PB2 핀을 PWM 신호 output으로 설정해주는 함수. 건드릴거 없음
void pwm_init()
{
	/* Set PB1 and PB2 as PWM Mode */

	ICR1 = 19999; // 128일땐 39999
	//FAST-PWM, TOP:ICR1, OCR1x update at BOTTOM, TOV1 Flag set on TOP
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
}

// channel과 width를 받아서 PWM 신호 폭을 설정해주는 함수. 걍 쓰면 됨
void pwm(int channel, float width)
{
	/* change PWM width(0 ~ 20). channel 1 is PB1(OC1A) pin, channel 2 is
   * PB2(OC1B) pin */

	if (channel == 1) OCR1A = (ICR1 / 20) * width;
	else if (channel == 2) OCR1B = (ICR1 / 20) * width;
}

void delay()
{
	for (int i = 0; i < 300; i++)
		;
}

void uart_init()
{
	UBRRH = (unsigned char)(ubrr >> 8);
	UBRRL = (unsigned char)ubrr;
	UCSRB = (1 << RXEN) | (1 << TXEN) | (1<<RXCIE);
	UCSRC = (1 << URSEL) | (0 << USBS) | (3 << UCSZ0);
}

void uart_transmit(unsigned char data)
{
	while (!(UCSRA & 0b00100000))
		;
	UDR = data;
}

unsigned char uart_receive(void)
{
	while (!(UCSRA) & (1<<RXC));
	return UDR;
}

void uart_puts(const char * str)
{
	int len = strlen(str);
	int i;
	for(i=0;i<len;i++)
	{
		uart_transmit(str[i]);
	}
}

int abs(int num)
{
	if(num<0)
		return -num;
	return num;
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

