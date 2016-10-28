rm main.o
rm main.elf
rm main.hex
avr-gcc -g -Os -mmcu=atmega328 -c main.c
avr-gcc -g -mmcu=atmega328 -o main.elf main.o
avr-objcopy -j .text -j .data -O ihex main.elf main.hex
avr-size main.hex

