int checkButtonPin(int ms) {
  for (int i = 0; i < ms; i++) {
    if (digitalRead (BUTTON_PRESS_PIN))
      return 1;
    delay(1);
  }
  return 0;
}

void sendAck() {
  digitalWrite(ACK_PIN, HIGH);
  delay(10);
  digitalWrite(ACK_PIN, LOW);
}

int receiveData() {
  int data = 0;
  for (int i = 0; i < 8; i++) {
    if (checkButtonPin(100))
      return -1;
    data |= digitalRead(DATA_PIN) << i;
    sendAck();
  }
  Serial.print("DataReceived:");
  Serial.print(data);
  return data;
}

