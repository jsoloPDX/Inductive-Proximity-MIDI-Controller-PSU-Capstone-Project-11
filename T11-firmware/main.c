#define F_CPU 16000000UL 

#include <avr/io.h> 
#include <util/delay.h>
#include "pwm.h"
#include "main.h"

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
			//Handle Buttone One
		}

		if(IsButtonTwoPressed()){
			//Handle Buttone Two
		}

	}
}



void InitializePorts(void){
	// Port initialization code here. The function eventually will 
	// accept inputs/outputs as needed. 
}


void AutoCalibration(void){
	// Perform auto calibration
}


int IsButtonOnePressed(void){
	// Return 0 if false, 1 if true
	return(0);	
}


int IsButtonTwoPressed(void){
	// Return 0 if false, 1 if true
	return(0);
}

