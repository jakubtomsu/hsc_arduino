#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define WIDTH 16
#define BUTTON_PIN 7

bool button_down = false;

void setup() {
  lcd.begin(WIDTH, 2);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  static int counter = 0;

  const int btn_val = digitalRead(BUTTON_PIN);
  const bool button_pressed = btn_val == HIGH && !button_down;
  button_down = btn_val == HIGH ? false : true;

  if(button_pressed) {
    counter++;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(counter);
  }

  delay(300);
}
