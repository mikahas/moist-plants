// fastled
#define LED_COUNT 1
#define LED_LEVEL_OFF 0
#define LED_LEVEL_MIN 1
#define LED_LEVEL_MAX 255
#define LED_BRIGHTNESS_OFF 0
#define LED_BRIGHTNESS_MIN 10
#define LED_BRIGHTNESS_MAX 150
#define LED_DATA_PIN 6	// data output pin for LED

// inputs
#define BUTTON_PIN A1	// input pin for momentary button
#define SENSOR_MOISTURE_PIN A2 // input pin for moisture sensor
#define SENSOR_LDR_PIN A3 	// input pin for light dependant resistor

// To test the capacitive sensor dip it in water and read the value of 100 % humidity.
// 0 % is measured when the sensor dry and not touching anything.
// moisture sensor test values:
// 0% humidity (air): 535
// 100% humidity (water): 335
#define MOISTURE_LEVEL_MIN 340  // 99% humidity
#define MOISTURE_LEVEL_MAX 530// 1% humidity

// LDR min & max
#define LDR_LEVEL_MIN 0
#define LDR_LEVEL_MAX 1023

// threshold for the water level (=dry soil) when red light starts blinking
#define LOW_LEVEL_THRESHOLD 1

// threshold LDR sensor value when LED brightness should be reduced
#define LOW_LIGHT_THRESHOLD 820

// sensor read & led level update interval
#define DELAY_UPDATE 100	// 0.1 seconds
#define DELAY_PAUSE 500	// 0.5 seconds
