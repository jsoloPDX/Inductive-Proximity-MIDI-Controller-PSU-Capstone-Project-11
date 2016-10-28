#define F_CPU 16000000UL 
#define BAUD 31250
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h> 
#include <util/delay.h>
#include "usart.h"

void main( void )
{
	USART_Init(MYUBRR);
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


