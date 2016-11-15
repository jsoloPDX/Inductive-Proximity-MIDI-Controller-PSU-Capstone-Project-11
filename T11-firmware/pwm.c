/*
	Aside from the ATMEGA328 datasheet, this code was helped along by reading
	the PWM guide and example source code found at: 
	https://sites.google.com/site/qeewiki/books/avr-guide/pwm-on-the-atmega328 
*/ 

// Prescaler value (1,8,64,256,1024) 
//#define PS_1 1
//#define PS_8 2  //Gives 8 kHz   	(PS_B2 = 0, PS_B1 = 1, PS_B0 = 0)
//#define PS_64 4  //Gives 240 Hz 	(PS_B2 = 1, PS_B1 = 0, PS_B0 = 0)
//#define PS_256 6 //			 (PS_B2 = 1, PS_B1 = 1, PS_B0 = 0)
//#define PS_1024 7
//#define PS_Default 6

#define PS_B2 0
#define PS_B1 1
#define PS_B0 0

void PWM_On_PB3(unsigned char DutyCycle)
{
	// Set PB3 port as output (PWM). pg 103
	DDRB |= (1 << DDB3); 

	// Set duty cycle by setting Timer2 Output Control Register A
	OCR2A = DutyCycle; 

	/* Set COM2B[1:0] to 0x2 (0b10), so that OC2A is cleared after a Compare Match, 
	and is set back to BOTTOM (zero). This puts the timer in non-inverting mode. 
	This is found in section 22.7.3 of the data sheet for the ATMEGA328. */
	TCCR2A |= (1 << COM2A1) | (0 << COM2A0); 	
	
	// Set FastPWM (Mode 3 in Table 22-9) by setting WGM[2:0] = 0b011
	TCCR2A |= (0 << WGM22) | (1 << WGM21) | (1 << WGM20); 

	/* Set the prescaler value, which also enables the timer. 
	Table 22-10 in the data sheet explains the values. Setting CA0[2:0] to 
	0b100, will give a prescaler of 256 and should yield a PWM frequency of 
	around 244 Hz. PWMFreq = ClockSpeed/(Prescaler*TOP) = 16000000/(256*256) */
	TCCR2B |= (PS_B2 << CS02) | (PS_B1 << CS01) | (PS_B0 << CS00);

}

void PWM_On_PD5(unsigned char DutyCycle)
{
	// Set PD5 port as an output
	DDRD |= (1 << DDD5); 

	/* Calculate the ON count, and then store this into the OCR0A register. 
	For this 8-bit timer, the maximum count will be 255. Therefore the 
	DutyCyclePercent = (ON_Count/Max_Count)*100. Which means that the 
	ON_Count = (DutyCyclePercent*Max_Count)/100 */
	//unsigned char ON_Count = (unsigned char)((DutyCyclePercent*Max_Count)/100); 
	//OCR0B = ON_Count; 	
	OCR0B = DutyCycle; 	

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
	TCCR0B |= (PS_B2 << CS02) | (PS_B1 << CS01) | (PS_B0 << CS00);
}


void PWM_On_PD6(unsigned char DutyCycle)
{
	// Set PD6 port as an output
	DDRD |= (1 << DDD6); 

	/* Calculate the ON count, and then store this into the OCR0A register. 
	For this 8-bit timer, the maximum count will be 255. Therefore the 
	DutyCyclePercent = (ON_Count/Max_Count)*100. Which means that the 
	ON_Count = (DutyCyclePercent*Max_Count)/100 */
	//unsigned char ON_Count = (unsigned char)((DutyCyclePercent*Max_Count)/100 + 0.5); 
	//OCR0A = ON_Count; 	
	OCR0A = DutyCycle; 	

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
	TCCR0B |= (PS_B2 << CS02) | (PS_B1 << CS01) | (PS_B0 << CS00);
}


void PWM_Change_PB3(unsigned char DutyCycle)
{
	// Check to see whether output is enabled. If it is, set duty cycle.
	// If not, enable PWM with requested DutyCycle and with a default frequency.
	if (DDRB & (1 << DDB3))
	{
		// Set duty cycle by setting Timer2 Output Control Register A
		OCR2A = DutyCycle; 
	}else{
		PWM_On_PB3(DutyCycle);
	}
}

void PWM_Change_PD5(unsigned char DutyCycle)
{
	// Check to see whether output is enabled. If it is, set duty cycle.
	// If not, enable PWM with requested DutyCycle and with a default frequency.
	if (DDRD & (1 << DDD5))
	{
		// Set duty cycle by setting Timer2 Output Control Register A
		OCR0B = DutyCycle; 
	}else{
		PWM_On_PD5(DutyCycle);
	}
}


void PWM_Change_PD6(unsigned char DutyCycle)
{
	// Check to see whether output is enabled. If it is, set duty cycle.
	// If not, enable PWM with requested DutyCycle and with a default frequency.
	if (DDRD & (1 << DDD6))
	{
		// Set duty cycle by setting Timer2 Output Control Register A
		OCR0A = DutyCycle; 
	}else{
		PWM_On_PD6(DutyCycle);
	}
}
