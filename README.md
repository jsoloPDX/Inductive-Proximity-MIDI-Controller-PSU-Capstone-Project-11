# Inductive-Proximity-MIDI-Controller
A theremin style inductive controller for MIDI devices
A Senior ECE practicum project for Portland State University

This device will use large inductive coils as part of an LC filter to sense proximity and turn that information into MIDI data (like pitch, volume, and filter effects) which can be used to control musical instruments like synthesizers and drum machines. An AC signal will be generated at some frequency and sent VIA a cable to the LC proximity sensor filter. The coils will attenuate the signal based on the inductance of the coil. The returning signal will be compared to the original and the difference will be interpreted as a proximity value by a microcontroller(likely of the ATMEGA variety). The Microcontroller will organize, process, and convert that information into MIDI data, which will be sent to a MIDI capable device VIA a standard MIDI or USB MIDI connector. There is some room for automation as far as built in “calibration” sequences to adjust the sensitivity of the coils. The device will be somewhat modular in design and construction, which will allow for expansion of the variety of proximity sensors used and versatility of output signals.

The code library "Arduino_MIDI_Library_v4.2.zip" is not our work and is taken from the project at: https://github.com/FortySevenEffects/arduino_midi_library/

The EagleCAD library "adafruit-Adafruit-Eagle-Library-4abf84c.zip" is not our work and is taken from the project at:
https://github.com/adafruit/Adafruit-Eagle-Library
