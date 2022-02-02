
#define SENSOR_PIN A0
#define LED_PIN 9
#define SIGNAL_LED_PIN 10


#define BLINK_DELAY 100
#define SENSOR_THRESHOLD 900

#define SEND_DELAY 500

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(SIGNAL_LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void blink_led() {
  digitalWrite(LED_PIN, HIGH);
  delay(BLINK_DELAY);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  int sensor_val = analogRead(SENSOR_PIN);
  //Serial.println(sensor_val);
  if(sensor_val > SENSOR_THRESHOLD) {
    digitalWrite(SIGNAL_LED_PIN, HIGH);
    delay(SEND_DELAY / 2);
    digitalWrite(SIGNAL_LED_PIN, LOW);
    blink_led();
  }

  if(Serial.available() > 0) {
    blink_led();
  }
}
