// Moist Plants
// version: 2.0
// Author: Mika Hassinen

#define FASTLED_INTERNAL  // disable pragma message for fastled
#include <FastLED.h>

#include "config.h"

int sensorMoistureValue;
int sensorLDRValue;

int ledLevel;
int blinkCounter;
int moistureLevelMin;
int ledBrightness;
CRGB smartLed[LED_COUNT];

bool blink;

/**
 * Setup pins and variables, initialise LED and run initialisation animation
 */
void setup() {
	// setup pins
	pinMode(BUTTON_PIN, INPUT);
	pinMode(SENSOR_LDR_PIN, INPUT);
	pinMode(SENSOR_MOISTURE_PIN, INPUT);

	// set initial values
	sensorMoistureValue = MOISTURE_LEVEL_MIN;
	sensorLDRValue = LOW_LIGHT_THRESHOLD;
	moistureLevelMin = MOISTURE_LEVEL_MIN;
	blink = false;
	ledBrightness = LED_BRIGHTNESS_MAX;

	// initialise fastled
	FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(smartLed, LED_COUNT);

	// animate all led levels from red to green
	for (int level=0; level < LED_LEVEL_MAX; level+=1) {
		setLedLevel(level);
		delay(10);
	}

	// show blue at the end of the animation
	smartLed[0].setRGB(10, 10, 250);
	FastLED.show();

	delay(DELAY_PAUSE);
}

/**
 * Main Arduino loop.
 * Read button, sensors and update the LED
 */
void loop() {
	readButton();
	readSensors();
	updateBrightness();
	updateLED();
	blinkLED();
	// reading both LDR and moisture sensors takes 100 ms so the real delay is 100ms + DELAY_UPDATE
	delay(DELAY_UPDATE);
}

/**
 * Read button state and set minimum moisture sensor level. Smaller sensor value is more moist soil.
 * Used to set the optimum soil moisture level after the plant has been watered properly.
 */
void readButton() {
	bool buttonState = digitalRead(BUTTON_PIN);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    moistureLevelMin = readSensor(SENSOR_MOISTURE_PIN, MOISTURE_LEVEL_MIN, MOISTURE_LEVEL_MAX);
    ledLevel = LED_LEVEL_OFF;	// set LED off momentarily to reset update
    // confirmation color
    smartLed[0].setRGB(10, 10, 250);  // blue
    FastLED.show();
    delay(DELAY_PAUSE);
  }

  // TODO: reset moisture min level when button is pressed longer
  // TODO: blink blue light if soil is too moist?
}

/**
 * Read moisture and LDR sensor values
 * This takes approximately 50 ms / sensor so total read time is 100ms for two sensors
 */
void readSensors() {
	sensorMoistureValue = readSensor(SENSOR_MOISTURE_PIN, moistureLevelMin, MOISTURE_LEVEL_MAX);
	sensorLDRValue = readSensor(SENSOR_LDR_PIN, LDR_LEVEL_MIN, LDR_LEVEL_MAX);
}

/**
 * Set LED brightness value using LDR sensor value
 */
void updateBrightness() {
	if (sensorLDRValue >= LOW_LIGHT_THRESHOLD) ledBrightness = LED_BRIGHTNESS_MAX;
	else ledBrightness = LED_BRIGHTNESS_MIN;
}

/**
 * Update LED color using moisture sensor value
 */
void updateLED() {
	// sensor values are reversed (bigger value is dry and smaller value is moist)
	int newLedLevel = map(
		sensorMoistureValue,
		moistureLevelMin,
		MOISTURE_LEVEL_MAX,
		LED_LEVEL_MAX,
		LED_LEVEL_MIN
	);

	// update only if the value changes
	if (ledLevel != newLedLevel) {
		ledLevel = newLedLevel;
		setLedLevel(ledLevel);
	}
}

/**
 * Blink red when the soil is dry
 */
void blinkLED() {
	if (ledLevel <= LOW_LEVEL_THRESHOLD && blinkCounter % 2 == 0) {
		if (blink) setLedLevel(LED_LEVEL_OFF); // turn LED off
		else setLedLevel(ledLevel);
		blink = !blink;
	}

	if (blinkCounter > 2) blinkCounter = 0;
	else blinkCounter++;
}

/**
 * Ligt the LED according to given level where 0 is LED OFF and 255 green
 * @param Integer level number of leds to light up from 0 to 5
 */
void setLedLevel(int level) {
	int ledR = 0,
		ledG = 0,
		ledB = 0;

	// turn off LED if level is zero
	if (level == 0) {
		FastLED.setBrightness(LED_BRIGHTNESS_OFF);
	} else {
		level = map(level, LED_LEVEL_MIN, LED_LEVEL_MAX, 0, 255);
		FastLED.setBrightness(ledBrightness);
	}

	// this changes the led color from red to yellow to green
	ledR = 255 - level;
	ledG = level;

	// set led color and show it to the world
	smartLed[0].setRGB(ledR, ledG, ledB);
	FastLED.show();
}

/**
 * Read sensor multiple times and return the average
 * @return Integer
 */
int readSensor(int sensorPin, int min, int max) {
	int sensorMoistureValue, average;
	float sum;
	for (int i = 0; i < 50; i++) {
		sensorMoistureValue = analogRead(sensorPin);
		sum += sensorMoistureValue;
		delay(1);
	}

	// cast to int
	average = (int)(sum/50.0);

	// limit sensor reading between min & max calibration values
	average = min(average, max);  // min: the smaller of two numbers
	average = max(average, min);  // max: the bigger of two numbers

	return constrain(average, min, max);
}
