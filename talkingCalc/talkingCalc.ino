#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>

#if defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_Timer1
#include <TimerOne.h>
#elif defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer
#include <SimpleTimer.h>
#endif

const int BUTTON_PRESS_PIN = A1;
const int DATA_PIN = A0;
const int ACK_PIN = A3;


SdFat sd;
SFEMP3Shield MP3player;

int language=1;
int hours = 1;
int mins = 2;
int secs = 1;
int ampm = 62;

void setup() {
  uint8_t result;
  pinMode(DATA_PIN,INPUT);
  pinMode(ACK_PIN,OUTPUT);
  pinMode(BUTTON_PRESS_PIN,INPUT);

  Serial.begin(115200);
  if (!sd.begin(SD_SEL, SPI_HALF_SPEED))
    sd.initErrorHalt();
  if (!sd.chdir("/"))
    sd.errorHalt("sd.chdir");
  result = MP3player.begin();
  if (result != 0) {
    Serial.print(F("Error code: "));
    Serial.print(result);
    Serial.println(F(" when trying to start MP3 player"));
    if (result == 6) {
      Serial.println(F("Warning: patch file not found, skipping.")); // can be removed for space, if needed.
      Serial.println(
      F("Use the \"d\" command to verify SdCard can be read")); // can be removed for space, if needed.
    }
  }
}

void loop() {
#if defined(USE_MP3_REFILL_MEANS) \
  && ( (USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer) \
    ||   (USE_MP3_REFILL_MEANS == USE_MP3_Polled)      )

    MP3player.available();
#endif

  if (checkButtonPin(10)==1) {
    sendAck();
    Serial.print("Time Recvd ");
    language = receiveData();
    waitBetweenData();
    hours = receiveData();
    waitBetweenData();
    Serial.print(hours);
    mins = receiveData();
    waitBetweenData();
    Serial.print(":");
    Serial.print(mins);
    secs = receiveData();
    Serial.print(":");
    Serial.println(secs);
    if (hours != -1 && mins != -1 && secs != -1 || language != -1)
    {
      if(hours >= 12){
        hours -=12;
        ampm = 62;
      }
      else
        ampm=61;
      hours = (hours==0)?12:hours;
      playTime();
    }
  }
  //for(int i=0;i<100;i++){
  //   hours=i; 
  //    playTime();
  //    while(1);
  //    delay(2000);
  //}
  //  for (int i = 0; i < 62; i++) {
  //    hours = i;
  //    playTime();
  //    delay (1000);
  //  }

  //  if(checkButtonPin(100)==1){
  //    sendAck();
  //    receiveData();
  //    Serial.println();
  //  }
}

