int IsButtonOnePressed(void){
	if(~PIND & 0b00000100){
		// Button pressed. Wait 40 ms, and if still pressed(x3), return.
		_delay_ms(40);		
		if(~PIND & 0b00000100){
			_delay_ms(40);		
			if(~PIND & 0b00000100){
				_delay_ms(40);		
				if(~PIND & 0b00000100){
					// Small delay to handle depress.
					_delay_ms(100);
					return(1);
				}
			}
		}
	}
	// Return 0 if false, 1 if true
	return(0);	
}




int IsButtonTwoPressed(void){
	if(~PIND & 0b00001000){
		// Button pressed. Wait 20 ms, and if still pressed(x3), return.
		_delay_ms(40);		
		if(~PIND & 0b00001000){
			_delay_ms(40);		
			if(~PIND & 0b00001000){
				_delay_ms(40);		
				if(~PIND & 0b00001000){
					// Small delay to handle depress.
					_delay_ms(100);
					return(1);
				}
			}
		}
	}
	// Return 0 if false, 1 if true
	return(0);	
}

void HandleButtonOnePress(void)
{
		if(IsButtonOnePressed()){
			/* 
			Conditionals to toggle between all modes per the software
			state diagram. (Switch 1: Mostly used for play modes)
			*/
			#ifdef DEBUG
				USART_TransmitString("Button 1 Pressed.", 17); 
			#endif
			
			if (CurrentMode >= MODE_3)
			{
				CurrentMode = IDLE; 
				LED_OFF_All();
			}else
			{
				CurrentMode = CurrentMode + 1; 
				switch(CurrentMode)
				{
					case MODE_1:
					LED_ON_One();
					break;
					case MODE_2:
					LED_ON_Two();
					break;
					case MODE_3:
					LED_ON_Three();
					break;	
				}
			}

		}
}



void HandleButtonTwoPress(void)
{
		if(IsButtonTwoPressed()){
			/* 
			Conditionals to toggle between all modes per the software
			state diagram. (Switch 2: Mostly used for calibration)
			*/
			#ifdef DEBUG
				USART_TransmitString("Button 2 Pressed.", 17); 
			#endif
			
			CurrentMode = CALIBRATION; 
		}
}


