#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stepperMotor.h>
#define VRX_PIN  A0
#define VRY_PIN  A1
int xValue = 0; 
int yValue = 0; 
#define button 12
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};
stepperMotor myMotor;
boolean buttonState = 0;

void setup() {
  pinMode(button, INPUT);
  myMotor.attach(3);
  radio.begin();
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.setPALevel(RF24_PA_MIN);
  delay(2000);
}

void loop() {
  delay(10);
  radio.startListening();
  if ( radio.available()) {
    while (radio.available()) {
      xValue = analogRead(VRX_PIN);
      yValue = analogRead(VRY_PIN);
      int angleV = 0;
      radio.read(&angleV, sizeof(angleV));
      myMotor.write(angleV);
    }
    delay(10);
    radio.stopListening();
    buttonState = digitalRead(button);
    radio.write(&buttonState, sizeof(buttonState));
  }
}
