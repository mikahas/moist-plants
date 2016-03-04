int sensorPin = A1;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
 
#define TIME_INTERVAL 1000

long timer = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
   Serial.begin(115200);  
}
 
void loop() {
	unsigned long currentTime = millis();
	if (currentTime - timer > TIME_INTERVAL) {
		// read the value from the sensor:
	  sensorValue = analogRead(sensorPin);
	  Serial.print("sensor = " );              
	  Serial.println(sensorValue);

		timer = currentTime;
	}
                  
}