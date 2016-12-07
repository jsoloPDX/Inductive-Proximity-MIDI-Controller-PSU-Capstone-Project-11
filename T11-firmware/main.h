#define LINEFEED 10
#define CARRIAGERETURN 13

#define DelayOn 50
#define DelayOff 100
#define CALIBRATION_START_VOLTAGE 51
#define ADC_THRESHOLD 20 // 20 has been used multiple times and confirmed working
#define numSam 8         // number of samples for averaging buffer

/* These are sensor values */
#define f0 50
#define f1 60
#define f2 70
#define f3 80
#define f4 96
#define f5 128
#define f6 256
#define f7 384
#define m0 512
#define m1 640
#define c0 768
#define c1 896
#define c2 960

// Global variables
#define InitialPWMValue 127
unsigned char PWMValue1 = InitialPWMValue; 
unsigned char OldPWMValue1 = InitialPWMValue; 
unsigned char PWMValue2 = InitialPWMValue; 
unsigned char OldPWMValue2 = InitialPWMValue; 
unsigned char PWMValue3 = InitialPWMValue; 
unsigned char OldPWMValue3 = InitialPWMValue; 

//Mode stuff
#define IDLE 0
#define MODE_1 1
#define MODE_2 2
#define MODE_3 3
#define CALIBRATION 4
unsigned char CurrentMode = IDLE;
 
// Functions
void InitializePorts(void);
void InitializeBuffer(int* ADC_Buffer1);
void InitializeSensors(unsigned char Voltage);
int IsButtonOnePressed(void);
int IsButtonTwoPressed(void);
void BlinkLED_PD4(unsigned char NumOfBlinks);
void BlinkLED_PD7(unsigned char NumOfBlinks);
void BlinkLED_PB0(unsigned char NumOfBlinks);
void BlinkLED_PB1(unsigned char NumOfBlinks);
void BlinkLED_PB2(unsigned char NumOfBlinks);
int AnalogRead_PC0(void);
int AnalogRead_PC1(void);
int AnalogRead_PC2(void);
int Average_PC0(int* ADC_Buffer1);
