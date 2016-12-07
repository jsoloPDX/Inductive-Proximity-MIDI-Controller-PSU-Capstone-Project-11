//Code to calibrate Sensor 1
unsigned char AutoCalibrate_1(unsigned char StartingVoltage, unsigned int MinCalVal)
{

	// Set initial voltage. Delay long enough to reach steady state
	PWM_Change_PB3(StartingVoltage);
	_delay_ms(1000); 

	// Define current PWMValue
	unsigned char CurrentVoltage = StartingVoltage; 


	// Store ADC value for sensor
	unsigned int FrequencyToDCValue = 0; 
	FrequencyToDCValue = AnalogRead_MeanPC0(16);

	for (CurrentVoltage = StartingVoltage; CurrentVoltage <= 255; CurrentVoltage = CurrentVoltage + 1)
	{
		PWM_Change_PB3(CurrentVoltage); 
		_delay_ms(100); 
		FrequencyToDCValue = AnalogRead_MeanPC0(16);
		if (FrequencyToDCValue <= MinCalVal)
		{
			return(CurrentVoltage); 
		} 
	}
}
