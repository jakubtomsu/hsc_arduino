
#define SENSOR_PIN A0
#define LED_PIN 9

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(LED_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  int sensor_val = analogRead(SENSOR_PIN);
  int led_val = (sensor_val - 520) / 2;
  Serial.println(sensor_val);
  //Serial.println(led_val);
  analogWrite(LED_PIN, led_val);
  delay(4);
}
