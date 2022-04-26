#include <stdio.h>
#include <stdlib.h>
const int trigPin = 3;
const int echoPin = 2;
const int buzzer = 5;
const int button = 11;            // GPIO 11 for the button
int ledflag=0;                   // LED status flag
const int led =10;
int isFlamePin = A0;  // This is our flame input pin
int isFlamePin2 = A1;  // This is our flame input pin 2
int isFlame1 = HIGH;  // HIGH MEANS NO FLAME
int isFlame2 = HIGH;

long duration;
int distance;
int safetyDistance;


void setup() {
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
pinMode(isFlamePin, INPUT);
pinMode(led,OUTPUT);           // define LED as an output
pinMode(isFlamePin2, INPUT);
pinMode(buzzer, OUTPUT);
pinMode(button,INPUT);         // define button as an input
Serial.begin(9600); 
}


void loop() {
flamesensor();
SendSoS();
distance50();
distance25();
}

void flamesensor(){

  isFlame1 = digitalRead(isFlamePin);//Readd the data gien by the flame sensor
  isFlame2 = digitalRead(isFlamePin2);

  if (isFlame1 == LOW)  //if it is low
  {
    Serial.println("FLAME on Sensor 2"); //Print Flame Sensor 2

    digitalWrite(5, HIGH);
  }
  else if ( isFlame2 == LOW)  //if it is low
  {
    Serial.println("FLAME on Sensor 1"); //Print Flame sensor 1
    digitalWrite(5, HIGH);
  }
  else                           //if not
  {                               
    Serial.println("no flame"); //print no  flame
   // digitalWrite(5, LOW);    //off the LED
    noTone(5);
  }

}

void SendSoS() {
  if (digitalRead(button)==HIGH){ // if button is pressed
    if (ledflag==0) {             // and the status flag is LOW
      ledflag=1;                  // make status flag HIGH
      digitalWrite(led,HIGH);     // and turn on the LED
      for (int i = 0; i <= 15; i++) {
    tone(buzzer,2010,15);
    delay(600);
    noTone(5);
  }
      }                           // 
    else {                        // otherwise...
      ledflag=0;                  // make status flag LOW
      digitalWrite(led,LOW);      // and turn off the LED
      //noTone(5);
      tone(buzzer,890,200); //user has turned off the emergency SoS switch
    }
  delay(1000);                    // wait a sec for the 
  }                               // hardware to stabilize
}  

void distance50() {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);


digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);


duration = pulseIn(echoPin, HIGH);


distance= duration*0.034/2;

safetyDistance = distance;
if (safetyDistance <=50  ){
  tone(5,2960,30);
}


else{
 
  noTone(5);
}


Serial.print("Distance1: ");
Serial.println(distance);
}

void distance25() {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);


digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);


duration = pulseIn(echoPin, HIGH);


distance= duration*0.034/2;

safetyDistance = distance;
if (safetyDistance < 25 ){
  tone(5,2160,30);
}


else{
 
  noTone(5);
}


Serial.print("Distance2: ");
Serial.println(distance);
}
