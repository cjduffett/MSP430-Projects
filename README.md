MSP430 Projects
===============
A series of small microcontroller projects I developed while a student in EC450 at Boston University. We chose the TI MSP430 for its affordability and many features. Most of these projects require external circuitry, documented in each project description.

1. SOS Blinker
--------------
This simple program uses the MSP430's Watchdog timer to periodically blink the Morse Code SOS signal using the on-board red LED. Code is only executed during the infrenquent Watchdog timer interrupts to save CPU power.

2. I/O Pin Transfer Characteristic
----------------------------------
The output characteristic of the MSP430's GPIO pins. I measured current and voltage as a function of output resistance in both the active high (logical 1) and active low (logical 0) states.

3. One Button Echo Light
------------------------
This program records a series of button presses from the on-board pushbutton. When the button is pressed, it lights the on-board green LED. After recording is finished, the program plays back the sequence recorded by the user, flashing the green LED with the same pattern recorded by the users button presses. Record mode is indicated by a steady red LED. Transitions between record and playback mode are indicated by 3 flashes of the red LED.

4. Digitally Controlled Oscillator (DCO)
----------------------------------------
The DCO freqency was tuned to several different values using the DCOCTL and BSCCTL1 registers. I measured the MSP430's default DCO freqency (1.1MHz) and maximum DCO frequency (19.7MHz). I also tuned the DCO as close as possible to 4MHz (I was able to get 4.01MHz).

5. Music Player
---------------
This system plays a variety of 8-bit tunes using an external 32 Ohm speaker. 4 buttons are used to Restart, Play/Pause, Speedup, or Slowdown the current score. 2 additional buttons are used to select the current score. The two scores I've written are "Joy to the World" and the "Super Mario Theme".

6. ADC and Serial Communication
-------------------------------
Two MSP430s are used in this exercise. The Transmitter uses an Analog-to-Digital Converter (ADC) to measure the voltage across a potentiometer and voltage-divider circuit. The result of the ADC conversion is sent using SPI to the Receiver, which displays result of the ADC conversion on a 7-segment display.
