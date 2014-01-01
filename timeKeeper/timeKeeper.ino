#include <Time.h>  
#include <Wire.h>  
#include <stdio.h>
#include <LiquidCrystal.h>
#include <DS1307RTC.h>

#define MAX_LCD_STRING_LEN 16

LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);

char displayBuffer[MAX_LCD_STRING_LEN+1] = "";

int gPrevSecond = 0;

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
  }
  Serial.println(get_key());
  if(get_key()!=NONE)
    sendData(get_key());
}
