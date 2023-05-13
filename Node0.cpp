#include <SPI.h>
#include "RF24.h"

int data[2];
RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int potpin1 = A1;
int valOne;
int potpin2 = A2;
int valTwo;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop() {{
    valOne = analogRead(potpin1);
    valOne = map(valOne, 0, 1023, 0, 127);
    data[0] = valOne;
    radio.write(data, 1);
  }
  {
    valTwo = analogRead(potpin2);
    valTwo = map(valTwo, 0, 1023, 128, 255);
    data[0] = valTwo;
    radio.write(data, 1);
  }
  Serial.println(valOne);
  Serial.println(valTwo);
}}