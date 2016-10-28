sudo avrdude -B5 -p m328p -c usbasp -P usb -v -U flash:w:./main.hex
