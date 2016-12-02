#define F_CPU 16000000UL 

#include <avr/io.h> 
#include <util/delay.h>
#include <stdint.h>
#include "pwm.h"
#include "main.h"

#define DelayOn 50
#define DelayOff 100
#define ADC_PIN 2
#define ADC_THRESHOLD 512

void main( void )
{
	/*
	Initialization Stuff should go here. 
	This can include initial calibration
	*/
	int mode = 0;
	int savedMode = 0;
	InitializePorts();
	AutoCalibration();	

	/*
	This is the main polling loop. With the exception of function calls, 
	the microcontroller should stay here while powered, and after the 
	initialization. 
	*/
	while(1)
	{

		/* 
		Switch to perform mode functions (based on mode variable)
		*/
		switch(mode){

			case 0:
				/* 
				Quiet mode (no inputs or outputs; polling switches)
				*/
				PORTD |= (1 << DDD4);
				PORTD |= (1 << DDD7);
				PORTB |= (1 << DDB0);
				PORTB |= (1 << DDB1);
				PORTB |= (1 << DDB2);
				break;
			
			case 1:
				/* 
				Play modes 1, 2 and 3:
				(Will contain the code to map input voltages to
				MIDI outputs) 
				*/
				PORTD &= ~(1<<DDD4);
				PORTD &= ~(1<<DDD7);
				PORTB |= (1 << DDB0);
				PORTB &= ~(1<<DDB1);
				PORTB &= ~(1<<DDB2);
				break;

			case 2:
				PORTD &= ~(1<<DDD4);
				PORTD &= ~(1<<DDD7);
				PORTB |= (1 << DDB0);
				PORTB |= (1 << DDB1);
				PORTB &= ~(1<<DDB2);
				break;

			case 3:
				PORTD &= ~(1<<DDD4);
				PORTD &= ~(1<<DDD7);
				PORTB |= (1 << DDB0);
				PORTB |= (1 << DDB1);
				PORTB |= (1 << DDB2);
				break;

			case 4:
				/* 
				Calibrate mode. Re-press begins calibration of first
				sensor. Can return to Quiet mode without calibrating.
				*/
				PORTD |= (1 << DDD4);
				PORTD &= ~(1<<DDD7);
				PORTB &= ~(1<<DDB0);
				PORTB &= ~(1<<DDB1);
				PORTB &= ~(1<<DDB2);
				break;

			case 5:
				/* 
				Calibrate sensors 1, 2, and 3:
				(This will contain the code that sends the PWM sweep out,
				and holds the PWM out for each sensor at the value that
				corresponds to the lowest input voltage.)
				*/
				PORTD |= (1 << DDD4);
				PORTD &= ~(1<<DDD7);
				PORTB |= (1 << DDB0);
				PORTB &= ~(1<<DDB1);
				PORTB &= ~(1<<DDB2);

				// my ineffective attempt at using sensor input value to turn LED5 on/off:
				//if (adc_read(ADC_PIN) > ADC_THRESHOLD){
				//	PORTB &= ~(1<<DDB2);
				//}else{
				//	PORTB |= (1 << DDB2);
				//}	
				break;

			case 6:
				PORTD |= (1 << DDD4);
				PORTD &= ~(1<<DDD7);
				PORTB |= (1 << DDB0);
				PORTB |= (1 << DDB1);
				PORTB &= ~(1<<DDB2);
				break;

			case 7:
				PORTD |= (1 << DDD4);
				PORTD &= ~(1<<DDD7);
				PORTB |= (1 << DDB0);
				PORTB |= (1 << DDB1);
				PORTB |= (1 << DDB2);
				break;

			default:
				break;
		}

		if(IsButtonOnePressed()){

			/* 
			Conditionals to toggle between all modes per the software
			state diagram. (Switch 1: Mostly used for play modes)
			*/
			if(mode == 0 && savedMode == 0){
				mode += 1;
			}	
			else if(mode == 0 && savedMode != 0){
				mode = savedMode;
			}
			else if(mode > 0 && mode < 3 && savedMode == 0){
				mode += 1;
			}
			else if(mode == 3 && mode != savedMode){
				mode = 0;
			}
			else if(mode != 0 && mode == savedMode){
				savedMode = 0;
				mode = 0;
			}
			else if(mode == 4){
				mode = 0;
			}
		}

		if(IsButtonTwoPressed()){

			/* 
			Conditionals to toggle between all modes per the software
			state diagram. (Switch 2: Mostly used for calibration)
			*/
			if(mode == 0){
				mode = 4;
			}
			else if(mode > 3 && mode < 7){
				mode +=1;
			}
			else if(mode == 7){
				mode = 0;
			}
			else if(mode > 0 && mode < 4){
				savedMode = mode;
				mode = 0;
			}
		}

	}
}




void InitializePorts(void){
	// Port initialization code here. The function eventually will 
	// accept inputs/outputs as needed. 
	
	// Enable ADC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 
	ADMUX = (1 << REFS0);
	ADCSRA |= (1 << ADEN);
	//ADCSRA |= (1 << ADSC);

	// Initialize PinD2 as input
	DDRD &= ~(1<<DDD2);
	// Initialize PinD3 as input
	DDRD &= ~(1<<DDD3);

	// Set PD4 port as output. Initialize as off.
	DDRD |= (1 << DDD4);
	PORTD &= ~(1<<DDD4);
	// Set PD7 port as output. Initialize as off.
	DDRD |= (1 << DDD7);
	PORTD &= ~(1<<DDD7);
	// Set PB0 port as output. Initialize as off.
	DDRB |= (1 << DDB0);
	PORTB &= ~(1<<DDB0);
	// Set PB1 port as output. Initialize as off.
	DDRB |= (1 << DDB1);
	PORTB &= ~(1<<DDB1);
	// Set PB2 port as output. Initialize as off.
	DDRB |= (1 << DDB2);
	PORTB &= ~(1<<DDB2);

}




void AutoCalibration(void){
	// Perform auto calibration

}




int IsButtonOnePressed(void){
	if(~PIND & 0b00000100){
		// Button pressed. Wait 40 ms, and if still pressed(x3), return.
		_delay_ms(40);		
		if(~PIND & 0b00000100){
			_delay_ms(40);		
			if(~PIND & 0b00000100){
				_delay_ms(40);		
				if(~PIND & 0b00000100){
					// Small delay to handle depress.
					_delay_ms(100);
					return(1);
				}
			}
		}
	}
	// Return 0 if false, 1 if true
	return(0);	
}




int IsButtonTwoPressed(void){
	if(~PIND & 0b00001000){
		// Button pressed. Wait 20 ms, and if still pressed(x3), return.
		_delay_ms(40);		
		if(~PIND & 0b00001000){
			_delay_ms(40);		
			if(~PIND & 0b00001000){
				_delay_ms(40);		
				if(~PIND & 0b00001000){
					// Small delay to handle depress.
					_delay_ms(100);
					return(1);
				}
			}
		}
	}
	// Return 0 if false, 1 if true
	return(0);	
}



// hasn't been working. not yet updated to eric's working code:
uint16_t adc_read(uint8_t adcx) {
	/* adcx is the analog pin we want to use.  ADMUX's first few bits are
	 * the binary representations of the numbers of the pins so we can
	 * just 'OR' the pin's number with ADMUX to select that pin.
	 * We first zero the four bits by setting ADMUX equal to its higher
	 * four bits. */
	ADMUX	&=	0xf0;
	ADMUX	|=	adcx;

	/* This starts the conversion. */
	ADCSRA |= (1<<ADSC);

	/* This is an idle loop that just wait around until the conversion
	 * is finished.  It constantly checks ADCSRA's ADSC bit, which we just
	 * set above, to see if it is still set.  This bit is automatically
	 * reset (zeroed) when the conversion is ready so if we do this in
	 * a loop the loop will just go until the conversion is ready. */
	while ( (ADCSRA & (1<<ADSC)) );  

	/* Finally, we return the converted value to the calling function. */
	return ADC;
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




void BlinkLED_PD7(unsigned char NumOfBlinks){

	unsigned char i = 0;
	for (i = 0; i < NumOfBlinks; i++){ 	
		// Set PD7 port as on
		PORTD |= (1 << DDD7);
		_delay_ms(DelayOn);
		
		// Set PD7 port as off
		PORTD &= ~(1<<DDD7);
		_delay_ms(DelayOff);

	}
}




void BlinkLED_PB0(unsigned char NumOfBlinks){

	unsigned char i = 0;
	for (i = 0; i < NumOfBlinks; i++){ 	
		// Set PB0 port as on
		PORTB |= (1 << DDB0);
		_delay_ms(DelayOn);
		
		// Set PB0 port as off
		PORTB &= ~(1<<DDB0);
		_delay_ms(DelayOff);
	}
}




void BlinkLED_PB1(unsigned char NumOfBlinks){

	unsigned char i = 0;
	for (i = 0; i < NumOfBlinks; i++){ 	
		// Set PB1 port as on
		PORTB |= (1 << DDB1);
		_delay_ms(DelayOn);
		
		// Set PB1 port as off
		PORTB &= ~(1<<DDB1);
		_delay_ms(DelayOff);
	}
}




void BlinkLED_PB2(unsigned char NumOfBlinks){

	unsigned char i = 0;
	for (i = 0; i < NumOfBlinks; i++){ 	
		// Set PB2 port as on
		PORTB |= (1 << DDB2);
		_delay_ms(DelayOn);
		
		// Set PB2 port as off
		PORTB &= ~(1<<DDB2);
		_delay_ms(DelayOff);
	}
}








/* 
Made you look
*/
