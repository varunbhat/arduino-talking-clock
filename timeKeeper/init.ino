void rtcTimeInit(){
  setSyncProvider(RTC.get);
  if(timeStatus()!= timeSet) 
  {
    Serial.println("Unable to sync with the RTC");
    lcd.print("Clock Init Failed!");
  }
  else
  {
    Serial.println("RTC has set the system time");
    lcd.print("-Talking Clock-");
  }
}

void serialInit(){
  Serial.begin(9600);
}

void lcdInit(){
  memset(displayBuffer,MAX_LCD_STRING_LEN,0);
  lcd.begin(16, 2);
}


