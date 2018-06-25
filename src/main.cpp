#include <Arduino.h>
#define VOLTAGE_SRC A0 //pin for reading voltage
#define PROPORTION 204.8
#define DELAY 500000000000
#define VLT 250

const float p1 = 4.41;
const float p2 = 7.35;
const int digits[4]={11,10,9,6};
const int segmentPins[] = {5,4,0,8,2,3,7,1};
//3--dot

float voltage;
float afr;

static const byte digitCodeMap[] = {
  //     GFEDCBA  Segments      7-segment map:
  B11011110, // 0   "0"          AAA
  B00000110, // 1   "1"         F   B
  B01111100, // 2   "2"         F   B
  B01110110, // 3   "3"          GGG
  B10100110, // 4   "4"         E   C
  B11110010, // 5   "5"         E   C
  B11111010, // 6   "6"          DDD
  B00010110, // 7   "7"
  B11111110, // 8   "8"
  B11110110, // 9   "9"

};

void zeros(){
  for(int i =0;i<4;i++)
    analogWrite(digits[i],VLT);
}

void setup() {
    //Serial.begin(9600);
    pinMode(VOLTAGE_SRC,INPUT);

    for(int i=0;i<4;i++)
      pinMode(digits[i],OUTPUT);

    for(int i =0;i<8;i++)
      pinMode(segmentPins[i], OUTPUT);
}

int buff;

void loop() {
    voltage = analogRead(VOLTAGE_SRC)/PROPORTION;
    afr = p1*voltage + p2;

    //Serial.print(voltage);
    //Serial.print("--");
    //Serial.println(afr);
    zeros();

    for(int i =0;i<8;i++){
      buff = digitCodeMap[9];
      digitalWrite(segmentPins[i], (buff& (0b00000001<<i)) );
    }
    //for(int i =0;i<12;i++)
    //  digitalWrite(i,LOW);

    //digitalWrite(segmentPins[0],HIGH);
/*
    zeros();
    analogWrite(digits[0],VLT);
    delayMicroseconds(DELAY);

    zeros();
    analogWrite(digits[1],VLT);
    delayMicroseconds(DELAY);

    zeros();
    analogWrite(digits[2],VLT);
    delayMicroseconds(DELAY);


    zeros();
    analogWrite(digits[3],VLT);
    delayMicroseconds(DELAY);
    zeros();
*/
}
