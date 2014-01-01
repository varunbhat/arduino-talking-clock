const int BUTTON_PRESS_PIN = A1;
const int DATA_PIN = A2;
const int ACK_PIN = A3;

char * getDateString(){
  snprintf(displayBuffer,MAX_LCD_STRING_LEN,"Date:%d/%d/%d\n",day(),month(),year());
  return displayBuffer;
}

char * getTimeString(){
  snprintf(displayBuffer,MAX_LCD_STRING_LEN,"%d:%d%d:%d%d %s\n",hour()%12,minute()/10,minute()%10,second()/10,second()%10,(hour()/12)?"PM":"AM");
  return displayBuffer;
}

void sendData(int type) {
  ackWait();
  if(type==RIGHT)
    serializeData(1);
  else
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
    digitalWrite(DATA_PIN, data & 0x01);
    ackWait();
  }
}

void ackWait() {
  digitalWrite(BUTTON_PRESS_PIN, HIGH);
  while (digitalRead(ACK_PIN) == HIGH);
  while (digitalRead(ACK_PIN) == LOW);
  digitalWrite(BUTTON_PRESS_PIN, LOW);
}



