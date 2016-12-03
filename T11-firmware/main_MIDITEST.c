#define F_CPU 16000000UL 
#define BAUD 31250
#define MYUBRR F_CPU/16/BAUD-1

#define DelayOn 50
#define DelayOff 100
#define ADC_THRESHOLD 512

#define LINEFEED 10
#define CARRIAGERETURN 13

#include <avr/io.h> 
#include <util/delay.h>
#include "usart.h"

void main( void )
{
	/*
	This code was confirmed to work using the HW layout 
	demonstrated in the schematic. 
	*/
	MIDI_Init();
	unsigned char NoteON = 0x90;
	unsigned char DataNote = 0x50;
	unsigned char DataVelocity = 0x7F; 
	unsigned char NoteOFF = 0x80; 

	while(1)
	{
		MIDI_Transmit(NoteON,DataNote,DataVelocity);
		_delay_ms(1000);
		MIDI_Transmit(NoteOFF,DataNote,DataVelocity);
		_delay_ms(1000);
	}
}


