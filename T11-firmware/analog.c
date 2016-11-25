// Analog Pin 0
int AnalogRead_PC0(void){
	
	int ADCValue = 0;

        // Set ADC clock prescaler to 128. If this is too low, won't get good resolution
    	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 

	// Set the ADC Reference to AVCC
   	ADMUX &= ~(1 << REFS1);  
   	ADMUX |= (1 << REFS0);  

	// Disable left adjust (use both ADCH and ADCL)
   	ADMUX &= ~(1 << ADLAR);

   	// Set MUX[3:0] to 0000 to enable ADC0
	ADMUX &= ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX1) & ~(1<<MUX0); 

	// Disables PRR bit, so ADC can be enabled (not sure this is necessary, since not using power saving modes). 
	//PRR &= ~(1<<PRADC); 

	// Enable ADC   
	ADCSRA |= (1 << ADEN);  

	// Start A2D Conversions
	ADCSRA |= (1 << ADSC); 

	// Wait for ADC to complete	
	while (ADCSRA & (1<<ADSC));

	// Store both bytes into unsigned int
	ADCValue = (ADCL | (ADCH << 8)); 

	// Return combination as int
	return  (ADCValue); 
}

