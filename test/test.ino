
#include <stdlib.h>



#define LED_PIN_G 10
#define LED_PIN_R 11
#define LED_PIN_B 12
#define SHORT_PAUSE 100
#define LONG_PAUSE 200

#define BLINK_RATE_MIN 100
#define BLINK_RATE_MAX 1000
#define BLINK_RATE_DELTA 30
#define BLINK_FREQ 200



void blink_pin(const int pin, const unsigned int ms) {
    delay(ms);
    digitalWrite(pin, HIGH);
    delay(ms);
    digitalWrite(pin, LOW);
}

void led_rgb_write(const int r, const int g, const int b) {
  digitalWrite(LED_PIN_G, g);
  digitalWrite(LED_PIN_R, r);
  digitalWrite(LED_PIN_B, b);
}

void blink_multiple(const int pin, const unsigned int count) {
  for(int i = 0; i < count; i++) {
    blink_pin(pin, SHORT_PAUSE);
  }
  delay(LONG_PAUSE);
}

int int_rand01() {
  return (rand() > (RAND_MAX / 2));
}



void setup() {
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_R, OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);
  Serial.begin(9600);
}



void loop() {
  static int blink_rate = BLINK_RATE_MAX;
  static bool is_blink_rate_increasing = false;
  static int change_accumulator = 0;
  static int blink_accumulator = 0;

  static int last_time = 0;
  const int current_time = millis();
  const int delta_time = current_time - last_time;
  last_time = current_time;

  change_accumulator += delta_time;
  if(change_accumulator > BLINK_FREQ) {
      change_accumulator = 0;
      blink_rate += delta_time * BLINK_RATE_DELTA * (is_blink_rate_increasing ? 1 : -1);
      if(blink_rate > BLINK_RATE_MAX || blink_rate < BLINK_RATE_MIN) {
        is_blink_rate_increasing = !is_blink_rate_increasing;
      }
  }

  blink_accumulator += delta_time;
  if(blink_accumulator > blink_rate) {
    static int tick = 0;
    tick++;
    led_rgb_write((tick) % 3 == 0, (tick + 1) % 3 == 0, (tick + 2) % 3 == 0);
    //led_rgb_write(int_rand01(), int_rand01(), int_rand01());
    blink_accumulator = 0;
  }

  Serial.println("hello world");

  delay(1);
}
