 const uint8_t RW_EN = 3;
 const uint8_t RW1 = 2;
 const uint8_t RW2 = 4;
 const uint8_t LW_EN = 5;
 const uint8_t LW1 = 7;
 const uint8_t LW2 = 8;
 const uint8_t POT = A0;

 int potVal = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(RW1, OUTPUT);
  pinMode(RW2, OUTPUT);
  pinMode(LW1, OUTPUT);
  pinMode(LW2, OUTPUT);
  pinMode(RW_EN, OUTPUT);
  pinMode(LW_EN, OUTPUT);
  // pinMode(POT, INPUT);

  digitalWrite(RW_EN, HIGH);
  digitalWrite(LW_EN, HIGH);

  //digitalWrite(RW2, LOW);
  //digitalWrite(RW1, HIGH);

  //digitalWrite(LW2, LOW);
  //digitalWrite(LW1, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  potVal = analogRead(POT);

  straight(potVal/4, 1);
  delay(200);
  turn(potVal/4, 1);
  delay(200);


}

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

void straight(int speed, int direction) {
  setLeftWheel(speed, direction);
  setRightWheel(speed, direction);
}

void turn(int speed, int direction) {
  if (direction == 1) {
    setLeftWheel(speed, 0);
    setRightWheel(speed, 1);
    }
  else if (direction == 2){
    setRightWheel(speed, 0);
    setLeftWheel(speed, 1);
  }
}
