#include "SoftwareSerial.h"

SoftwareSerial chat_serial = SoftwareSerial(2, 3);

#define RECIEVED_BUFFER_SIZE 512
char recieved_buffer[RECIEVED_BUFFER_SIZE];
int recieved_count;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  chat_serial.begin(9600);
}

void tone(const float dur, const float height) {
  for(float acc = 0.0; acc < dur; acc += height * 2.0) {
    
  }
}

void loop() {
  while(Serial.available() > 0) {
    const char b = Serial.read();
    Serial.write(b);
    chat_serial.write(b);
  }

  while(chat_serial.available() > 0) {
    const char b = chat_serial.read();
    //Serial.write(b);
    recieved_buffer[recieved_count] = b;
    recieved_count++;

    if(recieved_count > RECIEVED_BUFFER_SIZE) {
      break;
    }

    if(b == '\n' || b == '\r' || b == '\0') {
      recieved_buffer[recieved_count] = '\0';
      if(recieved_count > 1) {
        Serial.print(recieved_buffer);
      }
      recieved_count = 0;
      break;
    }
  }
}
