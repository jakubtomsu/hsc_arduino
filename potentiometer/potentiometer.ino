
#define LED_PIN 9
#define POTENTIOMETER_PIN A0

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  const int potentiometer_val = analogRead(POTENTIOMETER_PIN);
  Serial.println(potentiometer_val);
  analogWrite(LED_PIN, potentiometer_val / (1023 / 255));
  delay(1);
}
