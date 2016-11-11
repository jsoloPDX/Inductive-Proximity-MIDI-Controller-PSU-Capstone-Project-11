#define F_CPU 16000000UL 

#include <avr/io.h> 
#include <util/delay.h>
#include "pwm.h"

void main( void )
{
	// Value between 0-255
	// 0=0v, 255=5v
	unsigned char DutyCycle = 256/2; 

	// Prescaler value (1,8,64,256,1024) 
	// Formula for frequency: f = 16000000/(N*510)
	// Where N = Frequency value
	// *** WARNING *** Frequency selection not yet implemented.
	unsigned long Frequency = 256; 

	PWM_On_PD5(DutyCycle, Frequency);
	PWM_On_PD6(DutyCycle, Frequency);	
	PWM_On_PB3(DutyCycle, Frequency); 

	unsigned char i=0; 
	while(1)
	{
		for (i = 0; i <= 255; i++)
		{
			PWM_Change_PD5(i);
			PWM_Change_PD6(i);
			PWM_Change_PB3(i);
			_delay_ms(100);
		}
	}
}


