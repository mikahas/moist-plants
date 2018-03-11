# Moist Plants v.2.0

Moist Plants is a soil hygrometer which uses an Arduino to check the moisture levels of your plant soil!

This bad boy lights up a color changing LED from red to green depending on the soil moisture level. If the moisture level gets really low, the LED starts blinking red.

It features a button to set the optimum moisture level. Button is pressed when the plant is watered and the soil is at the desired moisture level.

An LDR (Light Dependand Resistor) is used to measure the ambient light to dim the LED at night.

[Picture of the project](https://www.flickr.com/photos/133800349@N02/30547128132/in/dateposted-public/)

## Future devopment

- 3D printed casing
- Reset moisture level when button is pressed longer
- Blink blue light if moisture level is above the optimum

## Notes

It is important to use a capacitive soil moisture sensor so the sensor elements are underneath a protective film. Resistive soil moisture sensors rely on measuring the resistance between two rods of metal which are exposed to water and salts in the ground which can cause corrosion. Also the DC current between the resistive sensor rods are creating an electrolysis and oxidation in the metal.

## Requirements

### Arduino

The development was done with an Arduino Nano and UNO but the final product uses an ATtiny85 chip to reduce the project size (some pins may have to be changed from the code for ATtiny).

The board and the LED are powered by an old mobile phone USB charger. Two analog inputs are used for the soil sensor and the photo resistor. One output pin is used for the LED.

One input pin is used for the button to set the optimum moisture level.

### Components

- Moisture sensor (capacitive type)
- Photo resistor for reading the ambient light level
- Fastled (WS2812B) to change colors
- Momentary button for user input
- Wires, resistors and a breadboard

## Pros & cons

+ + Simple to make, suitable for beginners
+ + fun to build
+ + Affordable: Arduino, sensor & LEDs cost about 20 €, the most expensive part is the sensor (mine cost about 10 €)
+ + Helps to keep the plants watered
- - Continuous DC voltage damages a resistive sensor and capasitive sensor is expensive
- - Not all features are implemented (reset with button, blink blue if moisture above optimum etc.)
