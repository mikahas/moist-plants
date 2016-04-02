# Moist plants

Create a soil hygrometer using an Arduino and check the moisture levels of your plant!

This small project lights up 1-9 LEDs depending to the soil moisture level.

### notes

It is important to use a capacitive soil moisture sensor so the sensor elements are underneath a protective film. Resistive soil moisture sensors rely on measuring the resistance between two rods of metal which are exposed to water and salts in the ground which can cause corrosion. Also the DC current between the resistive sensor rods are creating an electrolysis and oxidation in the metal.

## Requirements

### Arduino

For this project I used an Arduino nano but most Arduino boards will suffice.
Only requirements are 5 volts for the moisture sensor, 9 output pins for the LEDs.
One analog input pin is needed to read the data from the sensor. The Arduino should be powered with a normal
USB charger and that should be enough for the sensor as well.

### Components

- Moisture sensor (capacitive type)
- 5 LEDs, I chose blue, green and red
- 5 resistors (e.g. 220 ohm) for the LEDs
- Wires and a breadboard

## Pros & cons

+ + Simple to make
+ + Affordable: Arduino, sensor & LEDs cost less than 20 €
+ + Beginner project
- - continuous DC voltage damages the sensor
- - not a long term solution due to sensor damage
