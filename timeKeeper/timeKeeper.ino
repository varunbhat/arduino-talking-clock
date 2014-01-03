#include <Time.h>  
#include <Wire.h>  
#include <stdio.h>
#include <LiquidCrystal.h>
#include <DS1307RTC.h>

#define MAX_LCD_STRING_LEN 16

LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);

char displayBuffer[MAX_LCD_STRING_LEN+1] = "";

int gPrevSecond = 0;
int gPrevHour = 0;

const int BUTTON_PRESS_PIN = A1;
const int DATA_PIN = A2;
const int ACK_PIN = A3;

enum keypressed{
  RIGHT=0,
  UP,
  DOWN,
  LEFT,
  SELECT,
  NONE,
  INVALID
};

void setup() 
{
  pinMode(DATA_PIN,OUTPUT);
  pinMode(ACK_PIN,INPUT);
  pinMode(BUTTON_PRESS_PIN,OUTPUT);
  serialInit();
  lcdInit();
  rtcTimeInit();
  gPrevSecond = second();
}

void loop()
{
  if(gPrevSecond != second())
  {
    lcd.setCursor(0, 0);
    Serial.print(getTimeString());
    lcd.print(getTimeString());
    lcd.setCursor(0, 1);
    Serial.print(getDateString());
    lcd.print(getDateString());
    gPrevSecond = second();
    setSyncProvider(RTC.get);
  }
  if(get_key()!=NONE){
    Serial.println(get_key());
    sendData(get_key());
  }

  if(hour()!=gPrevHour){
    sendData(RIGHT);
    sendData(LEFT);
    gPrevHour = hour();
    Serial.println();
  }
  //  ackWait();
  //  serializeData(4);
  //  ackWait();
  //  serializeData(2);
  //  ackWait();
  //  serializeData(2);
  //  ackWait();
  //  serializeData(2);
  //  delay(5000);
}











