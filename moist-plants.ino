// Arduino Hygrometer
// version: 0.3
// Author: Mika Hassinen

#define TIME_INTERVAL 5000	// 5000 ms interval
#define FLASH_TIME_INTERVAL 400	// 400 ms flash interval
#define SENSOR_PIN A1		// input pin for the sensor
#define LOW_LEVEL_THRESHOLD 200	// minimum threshold for the water level (=desert dry soil)

int ledPins[] = {3, 4, 5, 6, 7, 8, 9, 10, 11};

int sensorValue = 0;  // variable to store the value coming from the sensor

int ledLevel = 0;

bool blink = false;

long timer, flashTimer = 0;

void setup() {

	// setup serial for debugging
	Serial.begin(115200);

	// setup outputs
	pinMode(SENSOR_PIN, INPUT);

	// test leds
	for (int pin = 0; pin < (sizeof(ledPins)/sizeof(int)); pin++ ) {
		pinMode(ledPins[pin], OUTPUT);
		delay(150);	// light up each LED in 0.15 second intervals
		digitalWrite(ledPins[pin], HIGH);
	}
	delay(1000);	// show all LEDs on for a second
	setLedLevel(0);

	// test sensor
	sensorValue = readSensor();
	Serial.print("[DEBUG]: test read value: ");
	Serial.println(sensorValue);
}

void loop() {

	unsigned long currentTime = millis();
	int newLedLevel;

	if ((unsigned long)(currentTime - timer) >= TIME_INTERVAL) {

		// read the value from the sensor:
		sensorValue = readSensor();

		// thresholds for different LED levels:
		// You may want to tweak these values depending on the readings of your sensor
		if (sensorValue >= 550) newLedLevel = 9;
		if (sensorValue < 550) newLedLevel = 7;
		if (sensorValue < 450) newLedLevel = 5;
		if (sensorValue < 350) newLedLevel = 3;
		if (sensorValue < 250) newLedLevel = 1;

		// update if the value changes
		if (ledLevel != newLedLevel) {
			ledLevel = newLedLevel;
			setLedLevel(ledLevel);
		}

		// debug data
		Serial.print("[DEBUG]: current value: ");
		Serial.println(sensorValue);

		// save time
		timer = currentTime;
	}

	// flash red LED if water level is below threshold
	if ((unsigned long)(currentTime - flashTimer) >= FLASH_TIME_INTERVAL) {

		if (sensorValue < LOW_LEVEL_THRESHOLD) {
			if (blink)
				setLedLevel(1);	// turn on first (red) LED
			else
				setLedLevel(0); // turn off all LEDs

			blink = !blink;
		}

		flashTimer = currentTime;
	}

}

/**
 * Ligts LEDs according to given level where 0 is all LEDs are OFF and 5 is all LEDs are ON
 * @param Integer level number of leds to light up from 0 to 5
 */
void setLedLevel(int level) {
	int ledArraySize = (sizeof(ledPins)/sizeof(int));
	if (level < 0) level = 0;
	if (level > (ledArraySize) ) level = ledArraySize;

	for (int pin = 0; pin < ledArraySize; pin++ ) {
		pinMode(ledPins[pin], OUTPUT);
		if (level >= pin+1)
			digitalWrite(ledPins[pin], HIGH);
		else
			digitalWrite(ledPins[pin], LOW);
	}
}

/**
 * Read moisture sensor multiple times and return the average
 * @return Integer
 */
int readSensor() {

	int average;
	float sensorValue, sum;
	for (int i = 0; i < 50; i++) {
		sensorValue = analogRead(SENSOR_PIN);
		sum += sensorValue;
		delay(1);
	}

	// cast to int
	average = (int)(sum/50.0);
	return average;
}
