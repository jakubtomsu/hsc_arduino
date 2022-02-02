
#define LED_PIN_0 13
#define LED_PIN_1 12
#define LED_PIN_2 11
#define LED_PIN_3 10
#define DELAY_MS 50

#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

const static int pins[] = {
  LED_PIN_0,
  LED_PIN_1,
  LED_PIN_2,
  LED_PIN_3,
};

void setup() {
   Serial.begin(9600);
   for(int i = 0; i < ARRAY_LENGTH(pins); i++) {
      pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  for(int pin_index = 0; pin_index < ARRAY_LENGTH(pins); pin_index++) {
    const int pin = pins[pin_index];
    digitalWrite(pin, HIGH);
    delay(DELAY_MS);
    digitalWrite(pin, LOW);
    Serial.println("hello");
  }
}
