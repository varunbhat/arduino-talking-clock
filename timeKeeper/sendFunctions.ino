
void sendData(int type) {
  ackWait();
  if(type==RIGHT)
    serializeData(1);
  else if(type==LEFT)
    serializeData(2);
  ackWait();
  serializeData(hour());
  ackWait();
  serializeData(minute());
  ackWait();
  serializeData(second());
}

void serializeData(int data) {
  for (int j = 8; j; j--, data >>= 1) {
    Serial.print(data & 0x01);
    if(data & 0x01)
      digitalWrite(DATA_PIN, HIGH);
    else
      digitalWrite(DATA_PIN, LOW);
    ackWait();
  }
  Serial.println();
}

void ackWait() {
  digitalWrite(BUTTON_PRESS_PIN, HIGH);
  while (digitalRead(ACK_PIN) == HIGH);
  while (digitalRead(ACK_PIN) == LOW);
  digitalWrite(BUTTON_PRESS_PIN, LOW);
  delay(2);
}



