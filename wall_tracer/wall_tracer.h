#ifndef __SooGoHaeRa_SuckJoonA_H_
#define __SooGoHaeRa_SuckJoonA_H_

int adc_read(int channel);
void parameter_init();
void pwm_init();
void pwm(int channel, float width);
void delay();
void uart_init();
void uart_transmit(unsigned char data);
unsigned char uart_receive(void);
void uart_puts(const char * str);
int abs(int num);
void turn_right();
void turn_left();
void point_turn_right();
void point_turn_left();
void go_straight(int millisec);

#endif
