#include "DHT.h"
#include <iostream>
#define DHTPIN 14
#define DHTTYPE DHT11

using namespace std; 

DHT dht(DHTPIN, DHTTYPE);
//19 ---- 18 ---- 5
int led1 = 5;
int led2 = 18;
int led3 = 19;
int bpin = 27;
int countbtnpressed = 1;

bool modestat = 0;
bool currentstatb = LOW;
bool lastpushb = LOW;
bool ledstat = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(bpin, INPUT);
  
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  bool pushstat = LOW;
  currentstatb = digitalRead(bpin);
  if(currentstatb == HIGH){
    delay(1);
    countbtnpressed = countbtnpressed + 1;
    if(countbtnpressed < 2){
      pushstat = HIGH;
      modestat = 1;
    }
    else{
      pushstat = LOW;
      countbtnpressed = 0;
      modestat = 0;
    }
  }
  
  if(modestat == 1){
    delay(1000);
    ledstat = HIGH;
    float temp = dht.readTemperature();
  
    if (isnan(temp)) {
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
    return;
    }

    Serial.print("%  Temperature: ");
    Serial.printf("%.2f",temp);
    Serial.print(F("% \n"));
    //Serial.cout << round(temp);
  
    if(temp < 35){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
    }
    else if(temp >= 35 && temp <= 50){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
    }
    else{
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
    }
  }
  else{
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
}
