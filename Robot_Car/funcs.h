void disableLeftMotor() {
  analogWrite(LW_EN, 0);
}

void disableRightMotor() {
  analogWrite(RW_EN, 0);
}

void startEngine() {
    motorInhibit = 1;
}

// Set Right Wheel Direction and Speed
void setRightWheel(uint8_t speed, int direction) {
  switch(direction){
    case FORWARD:
      digitalWrite(RW2, LOW);
      digitalWrite(RW1, HIGH);
      analogWrite(RW_EN, speed);
      break;
    case BACKWARD:
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
    case FORWARD:
      digitalWrite(LW2, LOW);
      digitalWrite(LW1, HIGH);
      analogWrite(LW_EN, speed);
      break;
    case BACKWARD:
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
  if (direction == LEFT) {
    setLeftWheel(speed, BACKWARD);
    setRightWheel(speed, FORWARD);
    }
  else if (direction == RIGHT){
    setRightWheel(speed, BACKWARD);
    setLeftWheel(speed, FORWARD);
  }
}

void normalTurn(int speed, int direction) {
  switch(direction){
    case LEFT: //Left
      disableLeftMotor();
      setRightWheel(speed, FORWARD);
      break;
    case RIGHT: //Right
      disableRightMotor();
      setLeftWheel(speed, FORWARD);
      break;
    default:
      break;
  }
}

void slowTurn(int speed, int direction) {
  switch(direction){
    case LEFT: //Left
      setLeftWheel(speed/2, FORWARD);
      setRightWheel(speed, FORWARD);
    case RIGHT: //Right
      setRightWheel(speed/2, FORWARD);
      setLeftWheel(speed, FORWARD);
    default:
      break;
  }
}

// Inturupt Function
void stopCar() {
  digitalWrite(RW_EN, LOW);
  digitalWrite(LW_EN, LOW);
  ISGOING = 0;
  //delay(10);
  //Serial.println("Button Press");
}

//Slow Down Function
void slowDown() {    
    while (motorInhibit >= 0.05)
    {
        motorSpeed = (potVal/4) * motorInhibit * ISGOING;
        straight(motorSpeed, FORWARD);
        motorInhibit -= 0.1;
        delay(20);
    }
    straight(0, FORWARD);
}

//Line Follow Function
void lineFollow(int speed) {
    
    if ((digitalRead(LREFLECT) == 1) && (digitalRead(CREFLECT) == 0) && (digitalRead(RREFLECT) == 1) && (ISGOING == 1)){
        straight(speed, FORWARD); 
    }
    else if((digitalRead(LREFLECT) == 1) && (digitalRead(CREFLECT) == 1) && (digitalRead(RREFLECT) == 0) && (ISGOING == 1)){
        normalTurn(speed, RIGHT);
        //delay(50);
    }
    else if((digitalRead(LREFLECT) == 0) && (digitalRead(CREFLECT) == 1) && (digitalRead(RREFLECT) == 1) && (ISGOING == 1)){
        normalTurn(speed, LEFT);
        //delay(50);
    }
    else if((ISGOING == 1)) {
        straight(speed/2, FORWARD);
    }
}