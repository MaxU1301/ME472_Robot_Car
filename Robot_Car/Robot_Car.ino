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
int motorSpeed = 0;

volatile uint8_t ISSTOPPED = 0; // Flag to determine if the car has run into something

#define LEFT 1
#define RIGHT 2

#define FORWARD 1
#define BACKWARD 0

void setup() {

  pinMode(RW1, OUTPUT);
  pinMode(RW2, OUTPUT);
  pinMode(LW1, OUTPUT);
  pinMode(LW2, OUTPUT);
  pinMode(RW_EN, OUTPUT);
  pinMode(LW_EN, OUTPUT);

  pinMode(DSENSE, INPUT);

  digitalWrite(RW_EN, HIGH);
  digitalWrite(LW_EN, HIGH);

  attachInterrupt(digitalPinToInterrupt(FRONT_SW), stopCar, FALLING);
  Serial.begin(9600);
}

void loop() {
  potVal = analogRead(SPEED_POT);
  motorSpeed = potVal/4;
  
  // reflectiveSensorDebug();
  // Serial.println(potVal);

 /*
  if (ISSTOPPED == 0) { // normal operation
    straight(motorSpeed, FORWARD);
    delay(1500);
    tightTurn(motorSpeed, LEFT);
    delay(500);
  } 
  else if (ISSTOPPED == 1) {} // operation to exec if it has run into an object. Possibly back up, turn 90, go foward, and reset flag
 */

 distanceDebug();
 delay(200);


}

// Set Right Wheel Direction and Speed
void setRightWheel(uint8_t speed, int direction) {
  switch(direction){
    case 1:
      digitalWrite(RW2, LOW);
      digitalWrite(RW1, HIGH);
      analogWrite(RW_EN, speed);
      break;
    case 0:
      digitalWrite(RW1, LOW);
      digitalWrite(RW2, HIGH);
      analogWrite(RW_EN, speed);
      break;
    default:
      break;
  }
  
}

// Set Left Wheel Direction and Speed
void setLeftWheel(int speed, int direction) {
    switch(direction){
    case 1:
      digitalWrite(LW2, LOW);
      digitalWrite(LW1, HIGH);
      analogWrite(LW_EN, speed);
      break;
    case 0:
      digitalWrite(LW1, LOW);
      digitalWrite(LW2, HIGH);
      analogWrite(LW_EN, speed);
      break;
    default:
      break;
  }
}

// Function to make the car go straight with a specified direction and speed
void straight(int speed, int direction) {
  setLeftWheel(speed, direction);
  setRightWheel(speed*0.95, direction);
}

// Function to make the car turn left(1) or right(2) with specified speed
void tightTurn(int speed, int direction) {
  if (direction == 1) {
    setLeftWheel(speed, BACKWARD);
    setRightWheel(speed, FORWARD);
    }
  else if (direction == 2){
    setRightWheel(speed, BACKWARD);
    setLeftWheel(speed, FORWARD);
  }
}

void normalTurn(int speed, int direction) {
  switch(direction){
    case LEFT: //Left
      disableLeftMotor();
      setRightWheel(speed, FORWARD);
    case RIGHT: //Right
      disableRightMotor();
      setLeftWheel(speed, FORWARD);
    default:
      break;
  }
}

void disableLeftMotor() {
  analogWrite(LW_EN, 0);
}

void disableRightMotor() {
  analogWrite(RW_EN, 0);
}

// Inturupt Function
void stopCar() {
  digitalWrite(RW_EN, LOW);
  digitalWrite(LW_EN, LOW);
  ISSTOPPED = 1;
}

void reflectiveSensorDebug() {
  Serial.print("Right Sensor ");
  Serial.println(digitalRead(RREFLECT));

  Serial.print("Center Sensor ");
  Serial.println(digitalRead(CREFLECT));

  Serial.print("Left Sensor ");
  Serial.println(digitalRead(LREFLECT));

  Serial.print("\n");
}

void distanceDebug() {
  Serial.print("Distance Sensor ");
  Serial.println(analogRead(DSENSE));
  Serial.print("\n");
}
