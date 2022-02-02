#define LED_PIN 9

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  //Fading the LED
  for(int i=0; i<255; i++){
    analogWrite(LED_PIN, i);
    delay(2);
  }
  for(int i=255; i>0; i--){
    analogWrite(LED_PIN, i);
    delay(2);
  }
}
