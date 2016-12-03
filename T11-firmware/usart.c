void USART_Init( unsigned int ubrr)
{
	/*Set baud rate */
	/* UBRR0H contains the 4 most significant bits of the
	baud rate. UBRR0L contains the 8 least significant
	bits.*/  
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	

	/*Enable transmitter */
	UCSR0B = (1<<TXEN0);
	
	/* Set frame format: 8data */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void MIDI_Transmit(unsigned char System, unsigned char Data1, unsigned char Data2)
{
	USART_Transmit(System); 
	USART_Transmit(Data1);
	USART_Transmit(Data2);
}

void MIDI_Init()
{
	USART_Init(MYUBRR);
}

void USART_TransmitString(char* StringToSend, unsigned char StringLength)
{
	unsigned char i = 0; 
	for (i=1; i <= StringLength; i++)
	{
		USART_Transmit((unsigned char)StringToSend[i-1]); 
	}
	USART_Transmit((unsigned char)CARRIAGERETURN); 
}
