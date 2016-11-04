#define F_CPU 16000000UL 

#include <avr/io.h> 
#include <util/delay.h>
#include "pwm.h"

void main( void )
{
	unsigned char DutyCycle = 50; 
	unsigned long Frequency = 1000; 

	
	unsigned char i=0; 
	while(1)
	{
		for (i = 0; i <= 100; i++)
		{
			PWM_On_PD5(i, Frequency);
			PWM_On_PD6(i, Frequency);
			_delay_ms(200);
		}
	}
}


