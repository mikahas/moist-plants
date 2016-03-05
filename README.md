# Moist plants v0.1

Create a soil hygrometer using an Arduino and check the moisture levels of your plant!

This small project lights up 1-5 LEDs depending to the soil moisture level.

## Requirements

### Arduino

For this project I used an Arduino nano but most Arduino boards will suffice.
Only requirements are 5 volts for the moisture sensor, 6 output pins for the LEDs and a sensor enabler pin.
One analog input pin is needed to read the data from the sensor. The Arduino should be powered with a normal
USB charger and that should be enough for the sensor as well.

### Components

- Moisture sensor, mine has "Moisture Sensor Meroduino" printed on it
- 5 LEDs, I like to have lots of colors so I chose blue, green and red but you can choose any color you want
- 5 resistors (e.g. 220 ohm) for the LEDs
- 1 general purpose NPN transistor
- Wires and a breadboard
