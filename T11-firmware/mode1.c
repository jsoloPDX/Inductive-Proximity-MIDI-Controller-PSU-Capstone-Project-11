/* 
  This function returns a logorithmic pitch value between 0 and 29
  The inputs are the pitch sensor number, and the minimum pitch sensor
 value that was used during calibration. 
*/
unsigned char getPitch(unsigned char sensorNum, unsigned char minCalVal)
{

	// Determine which sensor to read from and store into sensorVal
	unsigned int sensorVal = 0;
	switch(sensorNum)
	{
	case(1):
	sensorVal = AnalogRead_MeanPC0(16); 
	break;

	case(2):
	sensorVal = AnalogRead_MeanPC1(16); 
	break;

	case(3):
	sensorVal = AnalogRead_MeanPC2(16);
	break;
	}

	sensorVal = sensorVal - minCalVal; 

	if (sensorVal < 0){
		return 0; 
	}else if (sensorVal > 969){
		return 29; 
	}else if (sensorVal > 755){
		return 28; 
	}else if (sensorVal > 588){
		return 27; 
	}else if (sensorVal > 459){
		return 26; 
	}else if (sensorVal > 358){
		return 25; 
	}else if (sensorVal > 279){
		return 24; 
	}else if (sensorVal > 217){
		return 23; 
	}else if (sensorVal > 170){
		return 22; 
	}else if (sensorVal > 132){
		return 21; 
	}else if (sensorVal > 104){
		return 20; 
	}else if (sensorVal > 81){
		return 19; 
	}else if (sensorVal > 63){
		return 18; 
	}else if (sensorVal > 50){
		return 17; 
	}else if (sensorVal > 39){
		return 16; 
	}else if (sensorVal > 31){
		return 15; 
	}else if (sensorVal > 24){
		return 14; 
	}else if (sensorVal > 19){
		return 13;
	}else if (sensorVal > 15){
		return 12; 
	}else if (sensorVal > 12){
		return 11;
	}else if (sensorVal > 9){
		return 10;
 	}else if (sensorVal < 10){
		return sensorVal; 
	}
}


/* 
  Function returns the velocity value from a given sensor (0 127)
*/ 
unsigned char getVelocity(sensNum)
{
	unsigned int analogReadValue = 0; 
	switch(sensNum)
	{
	case(1): 
	analogReadValue = AnalogRead_MeanPC0(16); 
	break; 

	case(2): 
	analogReadValue = AnalogRead_MeanPC1(16); 
	break; 

	case(3): 
	analogReadValue = AnalogRead_MeanPC2(16); 
	break; 
	}

	// Divide by 3. 
	return(analogReadValue >> 3); 
}


/*
  For this state, a note is pretty much always being played, even if at no
 velocity, so we don't need to know the current play state. 

You need to give it: 
 pitchSensNum: Which antenna is the pitch sensor
 minCalVal: The value you used to calibrate the lowest sensor value. 
 velocitySensNum: Which antenna is the velocity sensor. 
 lowMidiNote: What the lowest midi value is
 curPlayNote: What the most recently played note is. 
*/
unsigned char updatePitchChangeMode(unsigned char pitchSensNum, unsigned char minCalVal, unsigned char velocitySensNum, unsigned char lowMidiNote, unsigned char curPlayNote)
{
	unsigned char nextPlayNote = 5; 
	nextPlayNote = getPitch(pitchSensNum, minCalVal) + lowMidiNote;

	if (nextPlayNote != curPlayNote)
	{
		MIDI_Transmit(NoteOFF, curPlayNote, 127);

		unsigned char velocity = 0; 
		velocity = getVelocity(velocitySensNum);
		curPlayNote = nextPlayNote; 

		MIDI_Transmit(NoteON, curPlayNote, velocity);  
	}
	return curPlayNote; 	
}




