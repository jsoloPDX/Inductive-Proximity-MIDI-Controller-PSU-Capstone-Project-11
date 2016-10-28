sudo avrdude -B5 -p m328p -c usbasp -P usb -v -U lfuse:w:0xFF:m -U hfuse:w:0xDE:m -U efuse:w:0xFD:m
