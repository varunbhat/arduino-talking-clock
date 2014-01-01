#include <LiquidCrystal.h>
#include <LCDKeypad.h>
LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);
char msgs[5][16] = {"Right Key OK ",
                    "Up Key OK    ",               
                    "Down Key OK  ",
                    "Left Key OK  ",
                    "Select Key OK" };
int adc_key_val[5] ={50, 200, 400, 600, 800 };
int NUM_KEYS = 5;
int adc_key_in;
int key=-1;
int oldkey=-1;
 
void setup()
{
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("     helle! ");
  lcd.print("      welcome!");
  lcd.setCursor(0,1);
  lcd.print("   LinkSprite");
  lcd.print("    LCD Shield");
  delay(1000);
 
  lcd.setCursor(0,0);
  for (char k=0;k<26;k++)
  {
    lcd.scrollDisplayLeft();
    delay(400);
  }
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("ADC key testing"); 
}
void loop()
{
   adc_key_in = analogRead(0);    // read the value from the sensor 
   key = get_key(adc_key_in);  // convert into key press
   if (key != oldkey)   // if keypress is detected
   {
     delay(50);  // wait for debounce time
     adc_key_in = analogRead(0);    // read the value from the sensor 
     key = get_key(adc_key_in);    // convert into key press
     if (key != oldkey)    
     {   
       lcd.setCursor(0, 1);
       oldkey = key;
       if (key >=0)
       {
           lcd.print(msgs[key]);              
       }
     }
   }
   delay(100);
}
// Convert ADC value to key number
int get_key(unsigned int input)
{
    int k;
    for (k = 0; k < NUM_KEYS; k++)
    {
      if (input < adc_key_val[k])
      {
        return k;
      }
    }   
    if (k >= NUM_KEYS)k = -1;  // No valid key pressed
    return k;
}
