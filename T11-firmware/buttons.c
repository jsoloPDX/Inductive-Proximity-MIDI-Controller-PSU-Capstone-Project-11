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
