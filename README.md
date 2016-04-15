# Moist plants

Create a soil hygrometer using an Arduino and check the moisture levels of your plant!

This small project lights up 1-9 LEDs depending to the soil moisture level. If the moisture level gets really low, the red led starts blinking.

[Picture of the finished project](https://www.flickr.com/photos/133800349@N02/26164452130/in/dateposted-public/)

### Notes

It is important to use a capacitive soil moisture sensor so the sensor elements are underneath a protective film. Resistive soil moisture sensors rely on measuring the resistance between two rods of metal which are exposed to water and salts in the ground which can cause corrosion. Also the DC current between the resistive sensor rods are creating an electrolysis and oxidation in the metal.

## Requirements

### Arduino

For this project I used an Arduino nano but most Arduino boards will suffice.
Only requirements are 5 volts for the moisture sensor, 9 output pins for the LEDs.
One analog input pin is needed to read the data from the sensor. The Arduino should be powered with a normal
USB charger and that should be enough for the sensor as well.

### Components

- Moisture sensor (capacitive type)
- 9 LEDs, I chose blue, green and red
- 9 resistors (e.g. 220 ohm) for the LEDs
- Wires and a breadboard

## Pros & cons

+ + Simple to make, suitable for beginners
+ + fun to build
+ + Affordable: Arduino, sensor & LEDs cost less than 20 €, the most expensive part is the sensor (mine cost about 10 €)
+ + helps to keep the plants watered
- - continuous DC voltage damages the sensor (only if you use a resistive type sensor)
