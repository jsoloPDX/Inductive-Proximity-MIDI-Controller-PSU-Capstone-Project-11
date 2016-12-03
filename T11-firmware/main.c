#define F_CPU 16000000UL 
#define BAUD 38400
#define MYUBRR F_CPU/16/BAUD-1

#define DelayOn 50
#define DelayOff 100
#define ADC_THRESHOLD 512

// Comment out the #define DEBUG line to turn off debugging output
#define DEBUG 1
#define LINEFEED 10
#define CARRIAGERETURN 13

#include <avr/io.h> 
#include <util/delay.h>
#include <stdint.h>
#include "pwm.h"
#include "main.h"
#include "usart.h"

void main( void )
{
	/*
	Initialization Stuff should go here. 
	This can include initial calibration
	*/
	
	int mode = 0;
	int savedMode = 0;
	int ADCVal = 0; 
	unsigned char DutyCycle = 256/2; 
	InitializePorts();
	AutoCalibration();	

	/* 
	If DEBUG is defined, enable UART for sending data over TX port
	*/
	#ifdef DEBUG
		// Initialize serial port for sending debug data
		USART_Init(25); // BAUD rate 38400
		USART_TransmitString("DEBUG is enabled.", 17); 
	#endif

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
				#ifdef DEBUG
					USART_TransmitString("Entering Quiet Mode.", 20); 
				#endif
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
				#ifdef DEBUG
					USART_TransmitString("Entering Mode 1.", 16); 
				#endif
				PORTD &= ~(1<<DDD4);
				PORTD &= ~(1<<DDD7);
				PORTB |= (1 << DDB0);
				PORTB &= ~(1<<DDB1);
				PORTB &= ~(1<<DDB2);
				break;

			case 2:
				#ifdef DEBUG
					USART_TransmitString("Entering Mode 2.", 16); 
				#endif
				PORTD &= ~(1<<DDD4);
				PORTD &= ~(1<<DDD7);
				PORTB |= (1 << DDB0);
				PORTB |= (1 << DDB1);
				PORTB &= ~(1<<DDB2);
				break;

			case 3:
				#ifdef DEBUG
					USART_TransmitString("Entering Mode 3.", 16); 
				#endif
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
				#ifdef DEBUG
					USART_TransmitString("Entering Mode Calibration Mode.", 31); 
				#endif
				PORTD |= (1 << DDD4);
				PORTD &= ~(1<<DDD7);
				PORTB &= ~(1<<DDB0);
				PORTB &= ~(1<<DDB1);
				PORTB &= ~(1<<DDB2);

				int calSensor1 = 0;
				int calSensor2 = 0;
				int calSensor3 = 0;

				break;

			case 5:
				/* 
				Calibrate sensors 1, 2, and 3:
				(This will contain the code that sends the PWM sweep out,
				and holds the PWM out for each sensor at the value that
				corresponds to the lowest input voltage.)
				*/
				#ifdef DEBUG
					USART_TransmitString("Calibrating Sensor 1.", 21); 
				#endif
				PORTD |= (1 << DDD4);
				PORTD &= ~(1<<DDD7);
				PORTB |= (1 << DDB0);
				PORTB &= ~(1<<DDB1);
				PORTB &= ~(1<<DDB2);

				// Calibration voltage sweep enable
				PWM_On_PD5(DutyCycle);

				// Initalize values for sensor calibration voltage to 5
				int i = 255;

				// sweep the PWM output
				// it stops as soon as it detects a voltage within 20mV of 0
				for (i = 255; i >= 0; i--)
				{
					if (calSensor1 == 0){
						PWM_Change_PD5(i);
						ADCVal = AnalogRead_PC0();
						if (ADCVal > 0 && ADCVal <= 20){
							calSensor1 = i;
							mode = 6;
							BlinkLED_PB0(5);
							break;
						}
						_delay_ms(100);
					}else if (calSensor1 > 0){
						PWM_Change_PD5(calSensor1);
					}

				}

				break;

			case 6:
				#ifdef DEBUG
					USART_TransmitString("Calibrating Sensor 2.", 21); 
				#endif
				PORTD |= (1 << DDD4);
				PORTD &= ~(1<<DDD7);
				PORTB |= (1 << DDB0);
				PORTB |= (1 << DDB1);
				PORTB &= ~(1<<DDB2);

				// Calibration voltage sweep enable
				PWM_On_PD6(DutyCycle);

				// sweep the PWM output
				// it stops as soon as it detects a voltage within 20mV of 0
				for (i = 255; i >= 0; i--)
				{
					if (calSensor2 == 0){
						PWM_Change_PD6(i);
						ADCVal = AnalogRead_PC1();
						if (ADCVal > 0 && ADCVal <= 20){
							calSensor2 = i;
							mode = 7;
							BlinkLED_PB1(5);
							break;
						}
						_delay_ms(100);
					}else if (calSensor2 > 0){
						PWM_Change_PD6(calSensor2);
					}

				}

				break;

			case 7:
				#ifdef DEBUG
					USART_TransmitString("Calibrating Sensor 3.", 21); 
				#endif
				PORTD |= (1 << DDD4);
				PORTD &= ~(1<<DDD7);
				PORTB |= (1 << DDB0);
				PORTB |= (1 << DDB1);
				PORTB |= (1 << DDB2);

				// Calibration voltage sweep enable
				PWM_On_PB3(DutyCycle);

				// sweep the PWM output
				// it stops as soon as it detects a voltage within 20mV of 0
				for (i = 255; i >= 0; i--)
				{
					if (calSensor3 == 0){
						PWM_Change_PB3(i);
						ADCVal = AnalogRead_PC2();
						if (ADCVal > 0 && ADCVal <= 20){
							calSensor3 = i;
							mode = 0;
							BlinkLED_PB2(5);
							break;
						}
						_delay_ms(100);
					}else if (calSensor3 > 0){
						PWM_Change_PB3(calSensor3);
					}

				}

				break;

			default:
				break;
		}

		if(IsButtonOnePressed()){
			/* 
			Conditionals to toggle between all modes per the software
			state diagram. (Switch 1: Mostly used for play modes)
			*/
			#ifdef DEBUG
				USART_TransmitString("Button 1 Pressed.", 17); 
			#endif
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
			#ifdef DEBUG
				USART_TransmitString("Button 2 Pressed.", 17); 
			#endif
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
	#ifdef DEBUG
		USART_TransmitString("Ports are being initialized.", 28); 
	#endif

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
	#ifdef DEBUG
		USART_TransmitString("Autocalibration.", 16); 
	#endif

	// Perform initialization
	PWM_On_PD5(256/2);
	PWM_On_PD6(256/2);
	PWM_On_PB3(256/2);

	// For setting trim capacitors (manual calibration)
	//PWM_Change_PD5(127);
	//PWM_Change_PD6(127);
	//PWM_Change_PB3(127);

	// Normal operation
	PWM_Change_PD5(0);
	PWM_Change_PD6(0);
	PWM_Change_PB3(0);

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




// Analog Pin 0
int AnalogRead_PC0(void){
	
	int ADCValue = 0;

   	// Set ADC clock prescaler to 128. If this is too low, won't get good resolution
  	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 

	// Set the ADC Reference to AVCC
   	ADMUX &= ~(1 << REFS1);  
   	ADMUX |= (1 << REFS0);  
	// Disable left adjust (use both ADCH and ADCL)
   	ADMUX &= ~(1 << ADLAR);
   	// Set MUX[3:0] to 0000 to enable ADC0
	ADMUX &= ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX1) & ~(1<<MUX0); 
	// Disables PRR bit, so ADC can be enabled
	//PRR &= ~(1<<PRADC); 
	// Enable ADC   
	ADCSRA |= (1 << ADEN);  

	// Start A2D Conversions
	ADCSRA |= (1 << ADSC); 

	// Wait for ADC to complete	
	while (ADCSRA & (1<<ADSC));

	// Store both bytes into unsigned int
	ADCValue = (ADCL | (ADCH << 8)); 
	
	#ifdef DEBUG
		USART_TransmitString("Analog Pin 0 (High,Low): ", 28);
		unsigned char HIGH = (ADCValue>>8); 
		unsigned char LOW = (unsigned char)ADCValue; 		
		USART_Transmit(HIGH);
		USART_Transmit(44); 
		USART_Transmit(LOW); 
		USART_Transmit(CARRIAGERETURN); 
	#endif
	// Return combination as int
	return  (ADCValue); 
}




// Analog Pin 1
int AnalogRead_PC1(void){
	
	int ADCValue = 0;

	// Set ADC clock prescaler to 128. If this is too low, won't get good resolution
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 

	// Set the ADC Reference to AVCC
   	ADMUX &= ~(1 << REFS1);  
   	ADMUX |= (1 << REFS0);  
	// Disable left adjust (use both ADCH and ADCL)
   	ADMUX &= ~(1 << ADLAR);
   	// Set MUX[3:0] to 0001 to enable ADC1
	ADMUX &= ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX1); 
	ADMUX |=  (1<<MUX0); 
	// Disables PRR bit, so ADC can be enabled
	//PRR &= ~(1<<PRADC); 
	// Enable ADC   
	ADCSRA |= (1 << ADEN);  

	// Start A2D Conversions
	ADCSRA |= (1 << ADSC); 

	// Wait for ADC to complete	
	while (ADCSRA & (1<<ADSC));

	// Store both bytes into unsigned int
	ADCValue = (ADCL | (ADCH << 8)); 

	#ifdef DEBUG
		USART_TransmitString("Analog Pin 1 (High,Low): ", 28);
		unsigned char HIGH = (ADCValue>>8); 
		unsigned char LOW = (unsigned char)ADCValue; 		
		USART_Transmit(HIGH);
		USART_Transmit(44); 
		USART_Transmit(LOW); 
		USART_Transmit(CARRIAGERETURN); 
	#endif

	// Return combination as int
	return  (ADCValue); 
}




// Analog Pin 2
int AnalogRead_PC2(void){
	
	int ADCValue = 0;

	// Set ADC clock prescaler to 128. If this is too low, won't get good resolution
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 

	// Set the ADC Reference to AVCC
   	ADMUX &= ~(1 << REFS1);  
   	ADMUX |= (1 << REFS0);  
	// Disable left adjust (use both ADCH and ADCL)
   	ADMUX &= ~(1 << ADLAR);
   	// Set MUX[3:0] to 0010 to enable ADC2
	ADMUX &= ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX0); 
	ADMUX |=  (1<<MUX1); 
	// Disables PRR bit, so ADC can be enabled
	//PRR &= ~(1<<PRADC); 
	// Enable ADC   
	ADCSRA |= (1 << ADEN);  

	// Start A2D Conversions
	ADCSRA |= (1 << ADSC); 

	// Wait for ADC to complete	
	while (ADCSRA & (1<<ADSC));

	// Store both bytes into unsigned int
	ADCValue = (ADCL | (ADCH << 8)); 

	#ifdef DEBUG
		USART_TransmitString("Analog Pin 2 (High,Low): ", 28);
		unsigned char HIGH = (ADCValue>>8); 
		unsigned char LOW = (unsigned char)ADCValue; 		
		USART_Transmit(HIGH);
		USART_Transmit(44); 
		USART_Transmit(LOW); 
		USART_Transmit(CARRIAGERETURN); 
	#endif

	// Return combination as int
	return  (ADCValue); 
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
