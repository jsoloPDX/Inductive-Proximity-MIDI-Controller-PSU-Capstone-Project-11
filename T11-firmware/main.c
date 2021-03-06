#define F_CPU 16000000UL 
#define BAUD 31250
#define MYUBRR F_CPU/16/BAUD-1


/* Comment out the "#define DEBUG 1" line to turn off debugging output
!!!!!-WARNING-!!!!! Turn OFF debugging (comment out line) before enabling 
MIDI, since MIDI needs to use the USART at a different BAUD rate. */
//#define DEBUG 1

#include "main.h"
#include <avr/io.h> 
#include <util/delay.h>
#include <stdint.h>
#include "pwm.h"
#include "usart.h"
#include "analog.h"
#include "led.h"
#include "buttons.h" 
#include "calibration.h"
#include "mode1.h"

void main( void )
{
	/*
	Initialization Stuff should go here. 
	This can include initial calibration
	*/
	InitializePorts();
	
	// InitialPWMValue and other global variables found in main.h
	// Enables PWM Sensors, and sets the initial value. 	
	InitializeSensors(InitialPWMValue); 

	// If DEBUG is NOT defined, then allow MIDI
	#ifndef DEBUG
		MIDI_Init();
	#endif

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
		#ifdef DEBUG
			USART_Transmit(PWMValue1); 
		#endif
		HandleButtonOnePress();
		HandleButtonTwoPress(); 

		switch(CurrentMode)
		{
			case IDLE: 
				//Do Nothing
				break;
			case MODE_1:
				curMidi = updatePitchChangeMode(1, ADC_THRESHOLD, 2, lowMidi, curMidi);
				break;
			case MODE_2: 
				// Do MODE2 stuff
				break;
			case MODE_3: 
				// Do MODE3 stuff
				break;
			case CALIBRATION:
				PWMValue1 = AutoCalibrate_1(CALIBRATION_START_VOLTAGE, ADC_THRESHOLD);
				PWMValue2 = AutoCalibrate_2(CALIBRATION_START_VOLTAGE, ADC_THRESHOLD);
				PWMValue3 = AutoCalibrate_3(CALIBRATION_START_VOLTAGE, ADC_THRESHOLD);
				CurrentMode = IDLE;
				break; 
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




void InitializeSensors(unsigned char Voltage){
	#ifdef DEBUG
		USART_TransmitString("Autocalibration.", 16); 
	#endif

	// Perform initialization
	PWM_On_PD5(Voltage); //Sensor 1
	PWM_On_PD6(Voltage); //Sensor 2
	PWM_On_PB3(Voltage); //Sensor 3

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






