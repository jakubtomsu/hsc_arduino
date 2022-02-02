
#define LED_PIN 12
#define SHORT_PAUSE 100
#define LONG_PAUSE 250

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void blink_ms(const unsigned int ms) {
    delay(ms);
    digitalWrite(LED_PIN, HIGH);
    delay(ms);
    digitalWrite(LED_PIN, LOW);
}

void blink_multiple(const unsigned int count) {
  for(int i = 0; i < count; i++) {
    blink_ms(SHORT_PAUSE);
  }
  delay(LONG_PAUSE);
}


void blink_morse_char(const char in_char) {
  const char* morse_codes[] = {
    ".-","-...","-.-.","-..", ".", "..-.", "--.", "....", "..", 
    ".---", "-.-", ".-..", "--","-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--..","   ","       ",".-.-."
  };

  char* ch = (char*)(morse_codes[in_char - 'a']);
  do {
    if(*ch == '.') {
      blink_ms(SHORT_PAUSE);
    } else {
      blink_ms(LONG_PAUSE);
    }
    ch++;
  } while(*ch);
}

void blink_morse_str(const char* str) {
  char* ch = (char*)str;
  while(*ch) {
    blink_morse_char(*ch);
    delay(LONG_PAUSE * 3);
    ch++;
  }
}

void loop() {
  //blink_multiple(3);
  blink_morse_str("bab");
}
