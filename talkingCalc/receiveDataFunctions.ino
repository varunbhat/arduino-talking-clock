int checkButtonPin(int ms) {
  for (int i = 0; i < ms; i++) {
    if (digitalRead (BUTTON_PRESS_PIN)){
      return 1;
    }
    delay(1);
  }
  return 0;
}

void sendAck() {
  digitalWrite(ACK_PIN, HIGH);
  delay(10);
  digitalWrite(ACK_PIN, LOW);
}

int waitBetweenData(){
  if(checkButtonPin(100)==1)
    sendAck();
}

int receiveData() {
  int data = 0;
  for (int i = 0; i < 8; i++) {
    if (checkButtonPin(1000)==0)
      return -1;
//    Serial.print(digitalRead(DATA_PIN));
    data |= digitalRead(DATA_PIN) << i;
    sendAck();
  }
//  Serial.println();
  return data;
}



