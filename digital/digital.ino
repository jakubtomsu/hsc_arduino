// cv 5

#define INPUT_PIN 10
#define LED_PIN 11
#define REPEAT_INITIAL_DELAY_MS 1000
#define REPEAT_DELAY_MS 120

#define LED_SET_DELAY 750

bool key_down = false;
int key_repeat_begin = 0;
int key_down_begin = 0;
bool key_repeated_before = false;

unsigned int led_val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(INPUT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("begin");
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(INPUT_PIN);
  //Serial.println(val);
  if(val == HIGH) {
    //Serial.println("high");
    digitalWrite(LED_PIN, 1);
  } else {
    //Serial.println("low");
    digitalWrite(LED_PIN, 0);
  }

  const int time_now = millis();
  const bool prev_key_down = key_down;
  key_down = val == HIGH ? false : true;
  const bool is_pressed = !prev_key_down && key_down;
  const bool is_released = prev_key_down && !key_down;
  const int down_time = time_now - key_down_begin;

  if(is_pressed) {
    Serial.println("pressed");
    key_down_begin = time_now;
    key_repeat_begin = time_now;
    key_repeated_before = false;
  }
  if(is_released) {
    Serial.println("released");
  }

  const int repeat_delay = key_repeated_before ? REPEAT_DELAY_MS : REPEAT_INITIAL_DELAY_MS;
  const bool is_repeated = key_down && (time_now - key_repeat_begin > repeat_delay);
  if(is_repeated) {
    key_repeat_begin = millis();
    key_repeated_before = true;
  }

  if(is_repeated && key_down) {
    Serial.println("repeated");
  }

  if(down_time > LED_SET_DELAY) {
    led_val += 4;
  } else if (is_released) { // set led val
    led_val = led_val < 500 ? 1023 : 0;
  }

  analogWrite(LED_PIN, led_val);

  
  
  delay(2);
}
