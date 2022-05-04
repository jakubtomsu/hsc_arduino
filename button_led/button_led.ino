#include <math.h>

#define INPUT_PIN_SET A4
#define INPUT_PIN_COL A5

#define LED_PIN_R 10
#define LED_PIN_G 11
#define LED_PIN_B 9


#define ARRAY_LENGTH(a) (sizeof(a) / sizeof(a[0]))

void setup() {
  // put your setup code here, to run once:
  pinMode(INPUT_PIN_SET, INPUT_PULLUP);
  pinMode(INPUT_PIN_COL, INPUT_PULLUP);
  pinMode(LED_PIN_R, OUTPUT);
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);
  Serial.begin(9600);
}

bool set_key_down = false;
bool col_key_down = false;

int led_col_index = 0;
float led_intensity = 0.0f;

void loop() {
  // put your main code here, to run repeatedly:
  const int set_val = digitalRead(INPUT_PIN_SET);
  const int col_val = digitalRead(INPUT_PIN_COL);
  //Serial.println(val);

  const bool prev_set_key_down = set_key_down;
  const bool prev_col_key_down = col_key_down;
  set_key_down = set_val == HIGH ? false : true;
  col_key_down = col_val == HIGH ? false : true;
  const bool set_key_pressed = !prev_set_key_down && set_key_down;
  const bool col_key_pressed = !prev_col_key_down && col_key_down;

  Serial.println(led_intensity);

  if(set_key_pressed) {
    Serial.println("set");
    led_intensity = (int)(led_intensity + 255.0f/5.0f) % 255;
  }
  if(col_key_pressed) {
    Serial.println("col");
    led_col_index++;
  }

  const float led_col_table[][3] = {
    {1,0,0},
    {1,1,0},
    {0,1,0},
    {0,1,1},
    {0,0,1},
    {1,0,1},
  };

  led_col_index = led_col_index % ARRAY_LENGTH(led_col_table);
  analogWrite(LED_PIN_R, (int)((float)led_col_table[led_col_index][0] * led_intensity));
  analogWrite(LED_PIN_G, (int)((float)led_col_table[led_col_index][1] * led_intensity));
  analogWrite(LED_PIN_B, (int)((float)led_col_table[led_col_index][2] * led_intensity));

  delay(16);
}
