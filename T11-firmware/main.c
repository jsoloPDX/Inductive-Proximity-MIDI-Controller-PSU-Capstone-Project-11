#define F_CPU 16000000UL 
#define BAUD 31250
#define MYUBRR F_CPU/16/BAUD-1

#define DelayOn 50
#define DelayOff 100
#define ADC_THRESHOLD 40 // 20-50 works best, upper value used in zero calibration
#define numSam 8         // number of samples for averaging buffer

/* These are sensor values */
#define f0 50
#define f1 60
#define f2 70
#define f3 80
#define f4 96
#define f5 128
#define f6 256
#define f7 384
#define m0 512
#define m1 640
#define c0 768
#define c1 896
#define c2 960

/* Comment out the "#define DEBUG 1" line to turn off debugging output
!!!!!-WARNING-!!!!! Turn OFF debugging (comment out line) before enabling 
MIDI, since MIDI needs to use the USART at a different BAUD rate. */
//#define DEBUG 1
#define LINEFEED 10
#define CARRIAGERETURN 13

#include <avr/io.h> 
#include <util/delay.h>
#include <stdint.h>
#include "pwm.h"
#include "main.h"
#include "usart.h"
#include "analog.h" 

void main( void )
{
	/*
	Initialization Stuff should go here. 
	This can include initial calibration
	*/
	
	int mode = 0; // Set to 0 by default. If other than zero, then was set temporarily for debug purposes.
	int savedMode = 0;
	int ADCVal = 0;
	unsigned char DutyCycle = 256/2; 
	int ADC_Buffer1[numSam];
	InitializeBuffer(ADC_Buffer1);
	InitializePorts();
	AutoCalibration();	
	
	// If DEBUG is NOT defined, then allow MIDI
	#ifndef DEBUG
		MIDI_Init();
	#endif
	unsigned char NoteON = 0x90;
	unsigned char DataNote = 0x50;
	unsigned char DataVelocity = 0x7F; 
	unsigned char NoteOFF = 0x80;

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
				//PORTD &= ~(1<<DDD4);
				//PORTD &= ~(1<<DDD7);
				//PORTB |= (1 << DDB0);
				//PORTB &= ~(1<<DDB1);
				//PORTB &= ~(1<<DDB2); 

				// 
				ADCVal = AnalogRead_MeanPC0(10);

				// Just some diagnostics using LEDs to track distance from sensor 2
				if (ADCVal >= f0 && ADCVal < f1){
					PORTD |= (1 << DDD7);
					PORTB &= ~(1<<DDB0);
					PORTB &= ~(1<<DDB1);
					PORTB &= ~(1<<DDB2); 
					#ifndef DEBUG					
						MIDI_Transmit(NoteON,DataNote,DataVelocity);
					#endif
				}else if (ADCVal >= f1 && ADCVal < f2){
					PORTD &= ~(1<<DDD7);
					PORTB |= (1 << DDB0);
					PORTB &= ~(1<<DDB1);
					PORTB &= ~(1<<DDB2);
					#ifndef DEBUG					
						MIDI_Transmit(NoteON,DataNote,DataVelocity);
					#endif
				}else if (ADCVal >= f2 && ADCVal < f3){
					PORTD &= ~(1<<DDD7);
					PORTB &= ~(1<<DDB0);
					PORTB |= (1 << DDB1);
					PORTB &= ~(1<<DDB2); 
					#ifndef DEBUG					
						MIDI_Transmit(NoteON,DataNote,DataVelocity);
					#endif
				}else if (ADCVal >= f3 && ADCVal < f4){
					PORTD &= ~(1<<DDD7);
					PORTB &= ~(1<<DDB0);
					PORTB &= ~(1<<DDB1);
					PORTB |= (1 << DDB2);
					#ifndef DEBUG					
						MIDI_Transmit(NoteON,DataNote,DataVelocity);
					#endif
				}else if (ADCVal < f0){
					PORTD &= ~(1<<DDD4);
					PORTD &= ~(1<<DDD7);
					PORTB &= ~(1<<DDB0);
					PORTB &= ~(1<<DDB1);
					PORTB &= ~(1<<DDB2); 
				}

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

				// Initalize values for sensor calibration voltage to 5
				int i = 255;

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

				// Initalize sensor calibration voltage values
				int calSensor1 = 0;
				int calSensor2 = 0;
				int calSensor3 = 0;
				PWM_Change_PD5(calSensor1);
				PWM_Change_PD6(calSensor2);
				PWM_Change_PB3(calSensor3);

				// Calibration voltage sweep enable
				PWM_On_PD5(DutyCycle);

				// sweep the PWM output
				// it stops as soon as it detects a voltage within 20mV of 0
				for (i = 255; i >= 0; i--)
				{
					if (calSensor1 == 0){
						PWM_Change_PD5(i);
						ADCVal = AnalogRead_PC0();
						if (ADCVal > 0 && ADCVal <= ADC_THRESHOLD){
							calSensor1 = i;
							mode = 6;
							BlinkLED_PB0(3);
							break;
						}
						_delay_ms(50);
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
						if (ADCVal > 0 && ADCVal <= ADC_THRESHOLD){
							calSensor2 = i;
							mode = 7;
							BlinkLED_PB1(3);
							break;
						}
						_delay_ms(50);
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
						if (ADCVal > 0 && ADCVal <= ADC_THRESHOLD){
							calSensor3 = i;
							mode = 0;
							BlinkLED_PB2(3);
							break;
						}
						_delay_ms(50);
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




void InitializeBuffer(int* ADC_Buffer1){
	#ifdef DEBUG
		USART_TransmitString("The buffer is being initialized.", 32); 
	#endif

	// Initalize all values of ADC_Buffer1 to 0
	unsigned int i = 0;
	for (i=0; i<=(numSam - 1); i++){
    	ADC_Buffer1[i] = 0;
	}
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




// Function to buffer and average the analog_read values
int Average_PC0(int* ADC_Buffer1){

	unsigned char i = 0;
	int ADC_Total = 0;
	int val = AnalogRead_PC0();

	// Shifts all data in the array one space left
	for (i=0; i<(numSam - 1); i++){
    	ADC_Buffer1[i] = ADC_Buffer1[i+1] ;
	}
	// Fills in the last space in the buffer with the new analog_read value
	ADC_Buffer1[numSam - 1] = val;

	// Averages the numbers in the buffer
	for (i=0; i<=(numSam - 1); i++){
    	ADC_Total += ADC_Buffer1[i];
	}
	ADC_Total = ADC_Total/numSam;

	return ADC_Total;
}













































/* 
Made you look
*/
