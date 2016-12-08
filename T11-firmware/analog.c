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

	// Disables PRR bit, so ADC can be enabled
	//PRR &= ~(1<<PRADC); 

	// Enable ADC   
	ADCSRA |= (1 << ADEN);  

	// Start A2D Conversions
	ADCSRA |= (1 << ADSC); 

	// Wait for ADC to complete	
	while (ADCSRA & (1<<ADSC));

	// Store both bytes into unsigned int
	ADCValue = (ADCL | (ADCH << 8)); 
	
	#ifdef DEBUG
		USART_TransmitString("Analog Pin 0 (High,Low): ", 28);
		unsigned char HIGH = (ADCValue>>8); 
		unsigned char LOW = (unsigned char)ADCValue; 		
		USART_Transmit(HIGH);
		USART_Transmit(44); 
		USART_Transmit(LOW); 
		USART_Transmit(CARRIAGERETURN); 
	#endif
	// Return combination as int
	return  (ADCValue); 
}




// Analog Pin 1
int AnalogRead_PC1(void){
	
	int ADCValue = 0;

	// Set ADC clock prescaler to 128. If this is too low, won't get good resolution
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 

	// Set the ADC Reference to AVCC
   	ADMUX &= ~(1 << REFS1);  
   	ADMUX |= (1 << REFS0);  

	// Disable left adjust (use both ADCH and ADCL)
   	ADMUX &= ~(1 << ADLAR);

   	// Set MUX[3:0] to 0001 to enable ADC1
	ADMUX &= ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX1); 
	ADMUX |=  (1<<MUX0); 

	// Disables PRR bit, so ADC can be enabled
	//PRR &= ~(1<<PRADC); 

	// Enable ADC   
	ADCSRA |= (1 << ADEN);  

	// Start A2D Conversions
	ADCSRA |= (1 << ADSC); 

	// Wait for ADC to complete	
	while (ADCSRA & (1<<ADSC));

	// Store both bytes into unsigned int
	ADCValue = (ADCL | (ADCH << 8)); 

	#ifdef DEBUG
		USART_TransmitString("Analog Pin 1 (High,Low): ", 28);
		unsigned char HIGH = (ADCValue>>8); 
		unsigned char LOW = (unsigned char)ADCValue; 		
		USART_Transmit(HIGH);
		USART_Transmit(44); 
		USART_Transmit(LOW); 
		USART_Transmit(CARRIAGERETURN); 
	#endif

	// Return combination as int
	return  (ADCValue); 
}




// Analog Pin 2
int AnalogRead_PC2(void){
	
	int ADCValue = 0;

	// Set ADC clock prescaler to 128. If this is too low, won't get good resolution
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 

	// Set the ADC Reference to AVCC
   	ADMUX &= ~(1 << REFS1);  
   	ADMUX |= (1 << REFS0);  

	// Disable left adjust (use both ADCH and ADCL)
   	ADMUX &= ~(1 << ADLAR);

   	// Set MUX[3:0] to 0010 to enable ADC2
	ADMUX &= ~(1<<MUX3) & ~(1<<MUX2) & ~(1<<MUX0); 
	ADMUX |=  (1<<MUX1); 

	// Disables PRR bit, so ADC can be enabled
	//PRR &= ~(1<<PRADC); 

	// Enable ADC   
	ADCSRA |= (1 << ADEN);  

	// Start A2D Conversions
	ADCSRA |= (1 << ADSC); 

	// Wait for ADC to complete	
	while (ADCSRA & (1<<ADSC));

	// Store both bytes into unsigned int
	ADCValue = (ADCL | (ADCH << 8)); 

	#ifdef DEBUG
		USART_TransmitString("Analog Pin 2 (High,Low): ", 28);
		unsigned char HIGH = (ADCValue>>8); 
		unsigned char LOW = (unsigned char)ADCValue; 		
		USART_Transmit(HIGH);
		USART_Transmit(44); 
		USART_Transmit(LOW); 
		USART_Transmit(CARRIAGERETURN); 
	#endif

	// Return combination as int
	return  (ADCValue); 
}


// Analog Mean read of Analog Pin 0
unsigned int AnalogRead_MeanPC0(unsigned char NumOfSamplesToAverage){

	int TotalValue = 0;  
	int MeanValue = 0; 
	int i = 0; 
	
	for (i = 1; i <= NumOfSamplesToAverage; i++)
	{		
		TotalValue = TotalValue + AnalogRead_PC0();
		_delay_ms(10); // Tweak value as needed. 
	}
	MeanValue = TotalValue/NumOfSamplesToAverage; 

	#ifdef DEBUG
		USART_TransmitString("Analog Pin 0 Mean Value: ", 25);
		unsigned char HIGH = (MeanValue>>8); 
		unsigned char LOW = (unsigned char)MeanValue; 		
		USART_Transmit(HIGH);
		USART_Transmit(44); 
		USART_Transmit(LOW); 
		USART_Transmit(CARRIAGERETURN); 
	#endif
	return MeanValue; 
}



// Analog Mean read of Analog Pin 1
int AnalogRead_MeanPC1(unsigned char NumOfSamplesToAverage){

	int TotalValue = 0;  
	int MeanValue = 0; 
	int i = 0; 
	
	for (i = 1; i <= NumOfSamplesToAverage; i++)
	{		
		TotalValue = TotalValue + AnalogRead_PC1();
		_delay_ms(10); // Tweak value as needed. 
	}
	MeanValue = TotalValue/NumOfSamplesToAverage; 

	#ifdef DEBUG
		USART_TransmitString("Analog Pin 1 Mean Value: ", 25);
		unsigned char HIGH = (MeanValue>>8); 
		unsigned char LOW = (unsigned char)MeanValue; 		
		USART_Transmit(HIGH);
		USART_Transmit(44); 
		USART_Transmit(LOW); 
		USART_Transmit(CARRIAGERETURN); 
	#endif
	return MeanValue; 
}




// Analog Mean read of Analog Pin 2
int AnalogRead_MeanPC2(unsigned char NumOfSamplesToAverage){

	int TotalValue = 0;  
	int MeanValue = 0; 
	int i = 0; 
	
	for (i = 1; i <= NumOfSamplesToAverage; i++)
	{		
		TotalValue = TotalValue + AnalogRead_PC2();
		_delay_ms(10); // Tweak value as needed. 
	}
	MeanValue = TotalValue/NumOfSamplesToAverage; 

	#ifdef DEBUG
		USART_TransmitString("Analog Pin 2 Mean Value: ", 25);
		unsigned char HIGH = (MeanValue>>8); 
		unsigned char LOW = (unsigned char)MeanValue; 		
		USART_Transmit(HIGH);
		USART_Transmit(44); 
		USART_Transmit(LOW); 
		USART_Transmit(CARRIAGERETURN); 
	#endif
	return MeanValue; 
}

// Analog Mean 2 read of Analog Pin 0
unsigned int AnalogRead_Mean2PC0(void){
	unsigned char i = 0;

	// If not enough samples, fill buffer first 	
	while (AverageCount <= AverageTotal)
	{
		for (i = 0; i < AverageTotal; i = i + 1)
		{
			AverageArray[(AverageTotal-1)-i] = AverageArray[(AverageTotal-2)-i]; 
		}
		AverageArray[0] = AnalogRead_PC0(); 
		AverageCount = AverageCount+1; 
	}

	// Shift Array
	for (i = 0; i < AverageTotal; i = i + 1)
	{
		AverageArray[16-i] = AverageArray[15-i]; 
	}
	AverageArray[0] = AnalogRead_PC0(); 

	unsigned int TotalValue = 0; 
	for (i = 0; i < AverageTotal; i = i + 1)
	{
		TotalValue = TotalValue + AverageArray[i]; 
	}	
	return (TotalValue >> 4); 
}
