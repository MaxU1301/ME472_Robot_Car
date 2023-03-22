//Max Ullrich
const uint8_t RW_EN = 6; // Right Wheel Enable [Used to be pin3]
const uint8_t RW1 = 4; // Right Wheel Direction 1
const uint8_t RW2 = 2; // Right Wheel Direction 2
const uint8_t LW_EN = 5; // Left Wheel Enable
const uint8_t LW1 = 7; // Left Wheel Direction 1
const uint8_t LW2 = 8; // Left Wheel Direction 2
const uint8_t SPEED_POT = A0; // Speed Potentiometer

const uint8_t RREFLECT = A1;
const uint8_t CREFLECT = A2;
const uint8_t LREFLECT = A3;

const uint8_t DSENSE = A5;

const uint8_t FRONT_SW = 3; // Front Mircroswitch [Needs to be pin 3 for interrupt]

int potVal = 0;
volatile int motorSpeed = 0;

float motorInhibit = 1;

volatile int ISGOING = 1; // Flag to determine if the car has run into something

#define LEFT 1
#define RIGHT 2

#define FORWARD 1
#define BACKWARD 0

#include "funcs.h"
#include "debug.h"

void setup() {

  pinMode(RW1, OUTPUT);
  pinMode(RW2, OUTPUT);
  pinMode(LW1, OUTPUT);
  pinMode(LW2, OUTPUT);
  pinMode(RW_EN, OUTPUT);
  pinMode(LW_EN, OUTPUT);

  //digitalWrite(RW_EN, HIGH);
  //digitalWrite(LW_EN, HIGH);

  attachInterrupt(digitalPinToInterrupt(FRONT_SW), stopCar, FALLING);
  Serial.begin(9600);
}

void loop() {
  potVal = analogRead(SPEED_POT);
  motorSpeed = (potVal/4) * motorInhibit * ISGOING;


  if (digitalRead(DSENSE) == 1){
    //straight(motorSpeed, FORWARD);
    lineFollow(motorSpeed);
  }
  else if(digitalRead(DSENSE) == 0){
    slowDown();
  }

  //reflectiveSensorDebug();
  //delay(500);
  //Serial.println(ISGOING);
  //delay(500);

}