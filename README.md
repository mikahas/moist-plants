# Moist Plants

Moist Plants is a soil hygrometer which uses an Arduino to check the moisture levels of your plant soil!

This bad boy lights up a color changing LED from red to green depending on the soil moisture level. If the moisture level gets really low, the LED starts blinking red.

[Picture of the finished project](https://www.flickr.com/photos/133800349@N02/30547128132/in/dateposted-public/)

## future devopment

- possibility to use potentiometers to set the range for optimum soil moisture levels
-- useful for plants with different thirstiness
- 3D printed casing

### Notes

It is important to use a capacitive soil moisture sensor so the sensor elements are underneath a protective film. Resistive soil moisture sensors rely on measuring the resistance between two rods of metal which are exposed to water and salts in the ground which can cause corrosion. Also the DC current between the resistive sensor rods are creating an electrolysis and oxidation in the metal.

## Requirements

### Arduino

The development was done with an Arduino Nano and UNO but the final product uses an ATtiny85 chip to reduce the project size.
The board and the LED are powered by an old mobile phone USB charger. Two analog inputs are used for the soil sensor and the photo resistor. One output pin is used for the LED.

### Components

- Moisture sensor (capacitive type)
- Photo resistor for reading the ambient light level
- Fastled (WS2812B) to change colors
- Wires, resistors and a breadboard

## Pros & cons

+ + Simple to make, suitable for beginners
+ + fun to build
+ + Affordable: Arduino, sensor & LEDs cost less than 20 €, the most expensive part is the sensor (mine cost about 10 €)
+ + helps to keep the plants watered
- - continuous DC voltage damages the sensor (only if you use a resistive type sensor)
