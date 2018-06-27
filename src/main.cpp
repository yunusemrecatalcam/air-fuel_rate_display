#include <Arduino.h>
#include <math.h>
#define VOLTAGE_SRC A0 //pin for reading voltage
#define PROPORTION 204.8
#define DELAY      5
#define IDLE_VLT   255
#define ACTIVE_VLT 230

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
    analogWrite(digits[i],IDLE_VLT);
}
void write(int num_to_write){
  int buff;
  if(num_to_write <=9 && num_to_write >=0){
    for(int i =0;i<8;i++){
      buff = digitCodeMap[num_to_write];
      digitalWrite(segmentPins[i], (buff& (0b00000001<<i)) );
    }
  }
}

void setup() {
    //Serial.begin(9600);
    pinMode(VOLTAGE_SRC,INPUT);

    for(int i=0;i<4;i++)
      pinMode(digits[i],OUTPUT);

    for(int i =0;i<8;i++)
      pinMode(segmentPins[i], OUTPUT);
}



void loop() {
    voltage = analogRead(VOLTAGE_SRC)/PROPORTION;
    afr = p1*voltage + p2;

    //Serial.print(voltage);
    //Serial.print("--");
    //Serial.println(afr);

    zeros();
    analogWrite(digits[0],ACTIVE_VLT);
    write(afr/10);
    delay(DELAY);

    zeros();
    analogWrite(digits[1],ACTIVE_VLT);
    write(fmod(afr, 10));
    digitalWrite(segmentPins[0], HIGH);
    delay(DELAY);

    zeros();
    analogWrite(digits[2],ACTIVE_VLT);
    write(fmod(afr,1)*10);
    delay(DELAY);


    zeros();
    analogWrite(digits[3],ACTIVE_VLT);
    write(fmod(afr,0.1)*100);
    delay(DELAY);
    zeros();

}
