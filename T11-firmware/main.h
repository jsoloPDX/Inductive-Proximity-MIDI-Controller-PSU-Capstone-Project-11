

// Functions
void InitializePorts(void);
void AutoCalibration(void);
int IsButtonOnePressed(void);
int IsButtonTwoPressed(void);
void BlinkLED_PD4(unsigned char NumOfBlinks);
void BlinkLED_PD7(unsigned char NumOfBlinks);
void BlinkLED_PB0(unsigned char NumOfBlinks);
void BlinkLED_PB1(unsigned char NumOfBlinks);
void BlinkLED_PB2(unsigned char NumOfBlinks);
uint16_t adc_read(uint8_t adcx);