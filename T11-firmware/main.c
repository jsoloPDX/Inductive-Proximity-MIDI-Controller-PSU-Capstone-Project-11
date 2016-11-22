#define F_CPU 16000000UL 

#include <avr/io.h> 
#include <util/delay.h>
#include "pwm.h"
#include "main.h"

#define DelayOn 500
#define DelayOff 1000

void main( void )
{
	/*
	Initialization Stuff should go here. 
	This can include initial calibration
	*/ 
	InitializePorts();
	AutoCalibration();	



	/*
	This is the main polling loop. With the exception of function calls, 
	the microcontroller should stay here while powered, and after the 
	initialization. 
	*/
	while(1)
	{

		if(IsButtonOnePressed()){
			BlinkLED_PD4(3);
		}

		if(IsButtonTwoPressed()){
			//Handle Buttone Two
		}

	}
}





void InitializePorts(void){
	// Port initialization code here. The function eventually will 
	// accept inputs/outputs as needed. 
	
	// Initialize PinD3 as input
	DDRD &= ~(1<<DDD3);

	// Set PD4 port as output. Initialize as off.
	DDRD |= (1 << DDD4);
	PORTD &= ~(1<<DDD4);
}





void AutoCalibration(void){
	// Perform auto calibration
}




int IsButtonOnePressed(void){
	if(PIND & 0b00100000){
		// Button pressed. Wait 20 ms, and if still pressed, return.
		_delay_ms(20);		
		if(PIND & 0b00100000){
			// Small delay to handle depress.
			_delay_ms(100);
			return(1);
		}
	}
	// Return 0 if false, 1 if true
	return(0);	
}




int IsButtonTwoPressed(void){
	if(PIND & 0b01000000){
		// Button pressed. Wait 20 ms, and if still pressed, return.
		_delay_ms(20);		
		if(PIND & 0b00100000){
			// Small delay to handle depress.
			_delay_ms(100);
			return(1);
		}
	}
	// Return 0 if false, 1 if true
	return(0);	
}




void BlinkLED_PD4(unsigned char NumOfBlinks){

	unsigned char i = 0;
	for (i = 0; i < NumOfBlinks; i++){ 	
		// Set PD4 port as on
		PORTD |= (1 << DDD4);
		_delay_ms(DelayOn);
		
		// Set PD4 port as off
		PORTD &= ~(1<<DDD4);
		_delay_ms(DelayOff);
	}
}



