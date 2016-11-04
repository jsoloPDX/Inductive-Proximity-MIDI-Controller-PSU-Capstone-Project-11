/*
	Aside from the ATMEGA328 datasheet, this code was helped along by reading
	the PWM guide and example source code found at: 
	https://sites.google.com/site/qeewiki/books/avr-guide/pwm-on-the-atmega328 
*/ 

void PWM_On_PD5(unsigned char DutyCyclePercent, unsigned long FrequencyHz)
{
	// Set PD5 port as an output
	DDRD |= (1 << DDD5); 

	/* Calculate the ON count, and then store this into the OCR0A register. 
	For this 8-bit timer, the maximum count will be 255. Therefore the 
	DutyCyclePercent = (ON_Count/Max_Count)*100. Which means that the 
	ON_Count = (DutyCyclePercent*Max_Count)/100 */
	unsigned char ON_Count = (unsigned char)((DutyCyclePercent*Max_Count)/100); 
	OCR0B = ON_Count; 	
	
	/* Set COM0A[1:0] to 0x2 (0b10), so that OC0A is cleared after a Compare Match, 
	and is set back to BOTTOM (zero). This puts the timer in non-inverting mode. 
	This is found in section 19.9.1 of the data sheet for the ATMEGA328. */
	TCCR0A |= (0 << COM0B0) | (1 << COM0B1); 

	// Set FastPWM (Mode 3 in Table 19-9) by setting WGM[2:0] = 0b011
	TCCR0A |= (0 << WGM02) | (1 << WGM01) | (1 << WGM00); 

	/* Set the prescaler value, which also enables the timer. 
	Table 19-10 in the data sheet explains the values. Setting CA0[2:0] to 
	0b100, will give a prescaler of 256 and should yield a PWM frequency of 
	around 244 Hz. PWMFreq = ClockSpeed/(Prescaler*TOP) = 16000000/(256*256) */
	TCCR0B |= (1 << CS02) | (0 << CS01) | (0 << CS00);
}


void PWM_On_PD6(unsigned char DutyCyclePercent, unsigned long FrequencyHz)
{
	// Set PD6 port as an output
	DDRD |= (1 << DDD6); 

	/* Calculate the ON count, and then store this into the OCR0A register. 
	For this 8-bit timer, the maximum count will be 255. Therefore the 
	DutyCyclePercent = (ON_Count/Max_Count)*100. Which means that the 
	ON_Count = (DutyCyclePercent*Max_Count)/100 */
	unsigned char ON_Count = (unsigned char)((DutyCyclePercent*Max_Count)/100 + 0.5); 
	OCR0A = ON_Count; 	
	
	/* Set COM0A[1:0] to 0x2 (0b10), so that OC0A is cleared after a Compare Match, 
	and is set back to BOTTOM (zero). This puts the timer in non-inverting mode. 
	This is found in section 19.9.1 of the data sheet for the ATMEGA328. */
	TCCR0A |= (0 << COM0A0) | (1 << COM0A1); 

	// Set FastPWM (Mode 3 in Table 19-9) by setting WGM[2:0] = 0b011
	TCCR0A |= (0 << WGM02) | (1 << WGM01) | (1 << WGM00); 

	/* Set the prescaler value, which also enables the timer. 
	Table 19-10 in the data sheet explains the values. Setting CA0[2:0] to 
	0b100, will give a prescaler of 256 and should yield a PWM frequency of 
	around 244 Hz. PWMFreq = ClockSpeed/(Prescaler*TOP) = 16000000/(256*256) */
	TCCR0B |= (1 << CS02) | (0 << CS01) | (0 << CS00);
}

