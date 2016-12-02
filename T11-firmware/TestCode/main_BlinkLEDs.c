#define F_CPU 16000000UL 
#define BAUD 38400
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h> 
#include <util/delay.h>

void Blink1(void);
void Blink2(void);
void Blink3(void);


int main (void)
{

   	DDRD |= (1 << DDD4); // Set LED1 as output
	DDRD |= (1 << DDD7); // Set LED1 as output
	DDRB |= (1 << DDB0); // Set LED1 as output
	DDRB |= (1 << DDB1); // Set LED1 as output
	DDRB |= (1 << DDB2); // Set LED1 as output

   while(1)  // Loop Forever
   {
	Blink1(); 
	Blink2(); 
	Blink3(); 
	Blink4(); 
	Blink5(); 
    }

}


void Blink1(void){
	PORTD |= (1 << DDD4);
	_delay_ms(500);

	// Set PD5 port as off
	PORTD &= ~(1<<DDD4);
	_delay_ms(10);
}

void Blink2(void){
	PORTD |= (1 << DDD7);
	_delay_ms(500);

	// Set PB2 port as off
	PORTD &= ~(1<<DDD7);
	_delay_ms(10);
}

void Blink3(void){
	PORTB |= (1 << DDB0);
	_delay_ms(500);

	// Set PB2 port as off
	PORTB &= ~(1<<DDB0);
	_delay_ms(10);
}

void Blink4(void){
	PORTB |= (1 << DDB1);
	_delay_ms(500);

	// Set PB2 port as off
	PORTB &= ~(1<<DDB1);
	_delay_ms(10);
}

void Blink5(void){
	PORTB |= (1 << DDB2);
	_delay_ms(500);

	// Set PB2 port as off
	PORTB &= ~(1<<DDB2);
	_delay_ms(10);
}
