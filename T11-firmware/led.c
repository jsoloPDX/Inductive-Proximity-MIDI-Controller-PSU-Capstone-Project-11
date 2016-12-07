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


void LED_ON_All(void)
{
	PORTD |= (1 << DDD4);
	PORTD |= (1 << DDD7);
	PORTB |= (1 << DDB0);
	PORTB |= (1 << DDB1);
	PORTB |= (1 << DDB2);
}

void LED_ON_One(void)
{
	PORTD &= ~(1<<DDD4);
	PORTD &= ~(1<<DDD7);
	PORTB |= (1 << DDB0);
	PORTB &= ~(1<<DDB1);
	PORTB &= ~(1<<DDB2); 
}

void LED_ON_Two(void)
{
	PORTD &= ~(1<<DDD4);
	PORTD &= ~(1<<DDD7);
	PORTB |= (1 << DDB0);
	PORTB |= (1 << DDB1);
	PORTB &= ~(1<<DDB2);
}

void LED_ON_Three(void)
{
	PORTD &= ~(1<<DDD4);
	PORTD &= ~(1<<DDD7);
	PORTB |= (1 << DDB0);
	PORTB |= (1 << DDB1);
	PORTB |= (1 << DDB2);
}


void LED_ON_Power(void)
{
	PORTD |= (1 << DDD4);
	PORTD &= ~(1<<DDD7);
	PORTB &= ~(1<<DDB0);
	PORTB &= ~(1<<DDB1);
	PORTB &= ~(1<<DDB2);
}

void LED_ON_Power_One(void)
{
	PORTD |= (1 << DDD4);
	PORTD &= ~(1<<DDD7);
	PORTB |= ~(1<<DDB0);
	PORTB &= ~(1<<DDB1);
	PORTB &= ~(1<<DDB2);
}

void LED_ON_Power_Two(void)
{
	PORTD |= (1 << DDD4);
	PORTD &= ~(1<<DDD7);
	PORTB |= (1 << DDB0);
	PORTB |= (1 << DDB1);
	PORTB &= ~(1<<DDB2);
}

void LED_ON_Power_Three(void)
{
	PORTD |= (1 << DDD4);
	PORTD &= ~(1<<DDD7);
	PORTB |= (1 << DDB0);
	PORTB |= (1 << DDB1);
	PORTB |= (1 << DDB2);
}


