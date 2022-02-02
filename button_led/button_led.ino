#define INPUT_PIN 10


void setup() {
  // put your setup code here, to run once:
  pinMode(INPUT_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(INPUT_PIN);
  Serial.println(val);
  Serial.println("test");
}
