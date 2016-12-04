# MIDI-THEREMIN-Controller
A theremin style controller for MIDI devices
A Senior ECE practicum project for Portland State University

Background

Most electronic musical instruments are controlled by small motions such as knob-turns or button-pushes. Such actions tend to be neither as interesting to watch nor as expressive as, for example, a guitarist strumming or a drummer drumming (or a piper piping). Using hand gestures and arm motions to control musical instruments would allow more precise and expressive control of electronic instrument parameters. The theremin, an analog electronic instrument can be controlled by hand gestures, but it’s ability to interface with modern equipment is lacking and or restrictive.

Objective

Our objective is to update the Theremin-style analog instrument to contain digital features, mainly a MIDI output. This will allow it to expressively control all kinds of modern musical instruments and equipment.


HOW IT SHOULD WORK:
An analog theremin circuit will send proximity information to a Microcontroller. The Microcontroller will organize, process, and convert that information into MIDI data, which will be sent to a MIDI capable device VIA a standard MIDI or USB MIDI connector. There is some room for automation as far as built in “calibration” sequences to adjust the sensitivity of the coils. The device will be somewhat modular in design and construction, which will allow for expansion of the variety of proximity sensors used and versatility of output signals.

![myimage-alt-tag](https://github.com/jsoloPDX/Inductive-Proximity-MIDI-Controller-PSU-Capstone-Project-11/blob/master/Overview%20Operation%20Block%20Diagram.jpg)

![myimage-alt-tag](https://github.com/jsoloPDX/Inductive-Proximity-MIDI-Controller-PSU-Capstone-Project-11/blob/master/Calibration%20Block%20Diagram.jpg)

The code library "Arduino_MIDI_Library_v4.2.zip" is not our work and is taken from the project at: https://github.com/FortySevenEffects/arduino_midi_library/

The EagleCAD library "adafruit-Adafruit-Eagle-Library-4abf84c.zip" is not our work and is taken from the project at:
https://github.com/adafruit/Adafruit-Eagle-Library
