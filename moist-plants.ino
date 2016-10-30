// Arduino Hygrometer
// version: 1.0
// Author: Mika Hassinen

#include <FastLED.h>

// fastled defines
#define NUM_LEDS 1
#define DATA_PIN 0
#define MAX_LED_VALUE 255

// timer and sensor
#define TIME_INTERVAL 1000	// 1 second interval
#define FLASH_TIME_INTERVAL 400	// 400 ms flash interval
#define SENSOR_PIN A1		// input pin for the sensor

// To test the capacitive sensor put it in a body of water and read the value of 100 % humidity
// 0 % is measured when the sensor is held in air and not touching anything.
// moisture sensor test values:
// 0% humidity (air):	575
// 100% humidity (water): 285
#define MIN_LEVEL 300	// 99% humidity
#define MAX_LEVEL 450	// 1% humidity
#define LOW_LEVEL_THRESHOLD 1	// minimum threshold for the water level (=desert dry soil)

#define BRIGHTNESS_OFF 0
#define BRIGHTNESS_MIN 10
#define BRIGHTNESS_MAX 150
#define BRIGHTNESS_PIN A2
#define BRIGHTNESS_THRESHOLD 70

int sensorValue = 0;  // variable to store the value coming from the sensor

int ledLevel = 0;
CRGB smartLed[NUM_LEDS];

bool blink = false;

long timer, flashTimer = 0;

void setup() {

	// setup outputs
	pinMode(SENSOR_PIN, INPUT);

	FastLED.addLeds<NEOPIXEL, DATA_PIN>(smartLed, NUM_LEDS);
	setLedLevel(0);
	delay(400);	// add a short delay so the transition to real led level is more subtle
	for (int i = 0; i < MAX_LED_VALUE; i++) {
		setLedLevel(i);
		delay(25);
	}
}

void loop() {

	unsigned long currentTime = millis();

	if ((unsigned long)(currentTime - timer) >= TIME_INTERVAL) {
		doUpdate();
		timer = currentTime; // save time
	}

	// flash red LED if water level is below threshold
	if ((unsigned long)(currentTime - flashTimer) >= FLASH_TIME_INTERVAL) {

		if (ledLevel <= LOW_LEVEL_THRESHOLD) {
			if (blink) setLedLevel(0); // turn off all LEDs
			else setLedLevel(ledLevel);
			blink = !blink;
		}

		flashTimer = currentTime;
	}

}

// TODO: do function that handles the sensor reading and led update
void doUpdate() {
	int newLedLevel;
	// read the value from the sensor:
	sensorValue = readSensor(SENSOR_PIN, MIN_LEVEL, MAX_LEVEL);

	// sensor values are reversed (bigger value is dry and smaller value is moist)
	newLedLevel = map(sensorValue, MIN_LEVEL, MAX_LEVEL, 255, 1);

	// update if the value changes
	if (ledLevel != newLedLevel) {
		ledLevel = newLedLevel;
		setLedLevel(ledLevel);
	}

}

/**
 * Ligt the LED according to given level where 0 is LED OFF and 255 green
 * @param Integer level number of leds to light up from 0 to 5
 */
void setLedLevel(int level) {
	int ledR = 0,
		ledG = 0,
		ledB = 0;

	int brightnessValue = readSensor(BRIGHTNESS_PIN, 0, 200);

	// turn off LED if level is zero
	if (level == 0) {
		FastLED.setBrightness(BRIGHTNESS_OFF);
	} else {
		if (brightnessValue > BRIGHTNESS_THRESHOLD) FastLED.setBrightness(BRIGHTNESS_MAX);
		else FastLED.setBrightness(BRIGHTNESS_MIN);
	}

	// reverse LED level so red is shown when the soil is dry and green when moist
	level = map(constrain(level, 0, MAX_LED_VALUE), 0, 255, 255, 0);

	// this changes the led color from red to yellow to green
	ledR = constrain(2 * level, 0, 255);
	ledG = constrain(2 * (255 - level), 0, 255);

	// set led color and show it to the world
	smartLed[0].setRGB(ledR, ledG, ledB);
	FastLED.show();
}

/**
 * Read moisture sensor multiple times and return the average
 * @return Integer
 */
int readSensor(int sensorPin, int min, int max) {

	int average;
	float sensorValue, sum;
	for (int i = 0; i < 50; i++) {
		sensorValue = analogRead(sensorPin);
		sum += sensorValue;
		delay(1);
	}

	// cast to int
	average = (int)(sum/50.0);

	// limit sensor reading between min & max calibration values
	average = min(average, max);	// min: the smaller of two numbers
	average = max(average, min);	// max: the bigger of two numbers

	return constrain(average, min, max);
}
