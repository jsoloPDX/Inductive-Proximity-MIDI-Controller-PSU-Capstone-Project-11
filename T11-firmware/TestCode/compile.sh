rm main.o
rm main.elf
rm main.hex
avr-gcc -g -Os -mmcu=atmega328 -c main_BlinkLEDs.c
avr-gcc -g -mmcu=atmega328 -o main_BlinkLEDs.elf main_BlinkLEDs.o
avr-objcopy -j .text -j .data -O ihex main_BlinkLEDs.elf main_BlinkLEDs.hex
avr-size main_BlinkLEDs.hex

