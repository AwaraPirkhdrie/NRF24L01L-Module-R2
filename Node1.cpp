#include <SPI.h>
#include "RF24.h"

int data[2];
int forward = A1;
int backward = A2;
int left = A3;
int right = A4;
const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(9,10); // CE,CSN:

void setup() {
    pinMode (forward,OUTPUT);
    pinMode (backward,OUTPUT);
    pinMode (left,OUTPUT);
    pinMode (right,OUTPUT);
    Serial.begin(9600);
    radio.begin();
    radio.openReadingPipe(1,pipe);
    radio.startListening();
}

void loop() {
    if(radio.available()){
        radio.read(data,1);{
            if(data[0]<127&&data[0]>66){
                digitalWrite(forward,LOW);
                digitalWrite(backward,HIGH);
            }
            if(data[0]<60&&data[0]>1){
                digitalWrite(forward,HIGH);
                digitalWrite(backward,LOW);
            }
            if(data[0]<65&&data[0]>61){
                digitalWrite(forward,LOW);
                digitalWrite(backward,LOW);
            }
    
            if(data[0]<255&&data[0]>193){
                digitalWrite(left,LOW);
                digitalWrite(right,HIGH);
            }
            if(data[0]<186&&data[0]>129){
                digitalWrite(left,HIGH);
                digitalWrite(right,LOW);
            }
            if(data[0]<192&&data[0]>185){
                digitalWrite(left,LOW);
                digitalWrite(right,LOW);
            }
        }
    }
}
