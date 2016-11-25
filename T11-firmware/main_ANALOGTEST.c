#define F_CPU 16000000UL 
#define BAUD 38400
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h> 
#include <util/delay.h>

#include "usart.h"
#include "analog.h"

void Blink1(void);
void Blink2(void);
void Blink3(void);


int main (void)
{
   	USART_Init(MYUBRR); 
   	DDRB |= (1 << DDB5); // Set LED1 as output

	int ACDVal = 0; 
   while(1)  // Loop Forever
   {

	ACDVal = AnalogRead_PC0(); 	
	
	// Transmit over external USART for debug
	// Transmits the 2-most significant bits first, 
	// then the 8-least significant bits next over TX pin.
	USART_Transmit((unsigned char)(ACDVal>>8)); 
	USART_Transmit((unsigned char)(ACDVal)); 

	// Could also light up an LED depending on level. 
	// Note that 5V = 1024. 2.5V = 512. 0V = 0. Etc. 
	// Formula is: ADC = 1024*(Vin/Vref)
    }

}


void Blink1(void){
	PORTB |= (1 << DDB5);
	_delay_ms(50);

	// Set PB2 port as off
	PORTB &= ~(1<<DDB5);
	_delay_ms(100);
}

void Blink2(void){
	PORTB |= (1 << DDB5);
	_delay_ms(1000);

	// Set PB2 port as off
	PORTB &= ~(1<<DDB5);
	_delay_ms(100);
}

void Blink3(void){
	PORTB |= (1 << DDB5);
	_delay_ms(5000);

	// Set PB2 port as off
	PORTB &= ~(1<<DDB5);
	_delay_ms(1000);
}
