// Arduino Hygrometer
// version: 0.4
// Author: Mika Hassinen

#define TIME_INTERVAL 60000	// 60 second interval
#define FLASH_TIME_INTERVAL 400	// 400 ms flash interval
#define SENSOR_PIN A1		// input pin for the sensor

// To test the capacitive sensor put it in a body of water and read the value of 100 % humidity
// 0 % is measured when the sensor is held in air and not touching anything.
// moisture sensor test values:
// 0% humidity (air):	575
// 100% humidity (water): 285
#define MIN_LEVEL 300	// 99% humidity
#define MAX_LEVEL 550	// 1% humidity
#define LOW_LEVEL_THRESHOLD 1	// minimum threshold for the water level (=desert dry soil)

int ledPins[] = {3, 4, 5, 6, 7, 8, 9, 10, 11};
int ledArraySize = (sizeof(ledPins)/sizeof(int));

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
	delay(400);	// add a short delay so the transition to real led level is more subtle

	// print led array size
	Serial.print("[DEBUG]: led count: ");
	Serial.println(ledArraySize);

	// update LEDs now
	doUpdate();
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
			if (blink)
				setLedLevel(1);	// turn on first (red) LED
			else
				setLedLevel(0); // turn off all LEDs

			blink = !blink;
		}

		flashTimer = currentTime;
	}

}

// TODO: do function that handles the sensor reading and led update
void doUpdate() {
	int newLedLevel;
	// read the value from the sensor:
	sensorValue = readSensor();

	// since the sensor values are reversed (bigger value is dry and smaller value is moist)
	// we should reverse the led values at this point
	newLedLevel = map(sensorValue, MIN_LEVEL, MAX_LEVEL, ledArraySize, 1);

	// update if the value changes
	if (ledLevel != newLedLevel) {
		ledLevel = newLedLevel;
		setLedLevel(ledLevel);
	}

	// debug data
	Serial.print("[DEBUG]: current value, led level: ");
	Serial.print(sensorValue);
	Serial.print("\t");
	Serial.println(ledLevel);
}

/**
 * Ligts LEDs according to given level where 0 is all LEDs are OFF and 5 is all LEDs are ON
 * @param Integer level number of leds to light up from 0 to 5
 */
void setLedLevel(int level) {
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

	// limit sensor reading between min & max calibration values
	average = min(average, MAX_LEVEL);	// min: the smaller of two numbers
	average = max(average, MIN_LEVEL);	// max: the bigger of two numbers

	return average;
}
