// Hygrometer
// version: 0.1
// Author: Mika Hassinen


#define TIME_INTERVAL 1000	// 1000 ms interval
#define ENABLER_PIN 2		// output pin that enables the sensor while reading the value
#define SENSOR_PIN A1		// input pin for the sensor

int ledPins[] = {3, 4, 5, 6, 7};

int sensorValue = 0;  // variable to store the value coming from the sensor

int ledLevel = 0;

long timer = 0;

void setup() {

	// setup serial for debugging
	Serial.begin(115200);

	// setup outputs
	pinMode(SENSOR_PIN, OUTPUT);

	// test leds
	for (int pin = 0; pin < (sizeof(ledPins)/sizeof(int)); pin++ ) {
		pinMode(ledPins[pin], OUTPUT);
		delay(150);
		digitalWrite(ledPins[pin], HIGH);
	}
	delay(1000);
	setLedLevel(0);

	// test sensor
	digitalWrite(ENABLER_PIN, HIGH);
	delay(100);
	sensorValue = analogRead(SENSOR_PIN);
	Serial.print("[DEBUG]: test read value: ");
	Serial.println(sensorValue);
	digitalWrite(ENABLER_PIN, LOW);
}

void loop() {

	unsigned long currentTime = millis();
	if ((unsigned long)(currentTime - timer) >= TIME_INTERVAL) {

		// enable probe
		digitalWrite(ENABLER_PIN, HIGH);
		delay(100);
		// read the value from the sensor:
		sensorValue = analogRead(SENSOR_PIN);
		// disable probe after reading values
		digitalWrite(ENABLER_PIN, LOW);

		// breakpoints for different led levels:
		if (sensorValue > 550) ledLevel = 5;
		if (sensorValue < 550) ledLevel = 4;
		if (sensorValue < 450) ledLevel = 3;
		if (sensorValue < 350) ledLevel = 2;
		if (sensorValue < 250) ledLevel = 1;
		setLedLevel(ledLevel);

		// debug data
		Serial.print("[DEBUG]: current value: ");
		Serial.println(sensorValue);

		// save time
		timer = currentTime;
	}

}

void setLedLevel(int level) {
	int ledArraySize = (sizeof(ledPins)/sizeof(int));
	if (level < 0) level = 0;
	if (level > (ledArraySize) )
		level = ledArraySize;

	for (int pin = 0; pin < ledArraySize; pin++ ) {
		pinMode(ledPins[pin], OUTPUT);
		if (level >= pin+1)
			digitalWrite(ledPins[pin], HIGH);
		else
			digitalWrite(ledPins[pin], LOW);
	}
}
