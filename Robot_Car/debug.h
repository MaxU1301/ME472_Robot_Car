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
  Serial.println(digitalRead(DSENSE));
  Serial.print("\n");
}
