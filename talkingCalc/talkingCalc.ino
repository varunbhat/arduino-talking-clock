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
const int DATA_PIN = A2;
const int ACK_PIN = A3;


SdFat sd;
SFEMP3Shield MP3player;

int language=0;
int hours = 0;
int mins = 0;
int secs = 0;
int ampm = 0;

void setup() {

  uint8_t result;
  pinMode(DATA_PIN,INPUT);
  pinMode(ACK_PIN,OUTPUT);
  pinMode(BUTTON_PRESS_PIN,INPUT);

  Serial.begin(115200);
  Serial.print(F("Free RAM = "));
  Serial.print(FreeRam(), DEC);
  Serial.println(
  F(" Should be a base line of 1040, on ATmega328 when using INTx"));
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

#if (0)
  // Typically not used by most shields, hence commented out.
  Serial.println(F("Applying ADMixer patch."));
  if(MP3player.ADMixerLoad("admxster.053") == 0) {
    Serial.println(F("Setting ADMixer Volume."));
    MP3player.ADMixerVol(-3);
  }
#endif

}

void loop() {

#if defined(USE_MP3_REFILL_MEANS) \
  && ( (USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer) \
    ||   (USE_MP3_REFILL_MEANS == USE_MP3_Polled)      )

    MP3player.available();
#endif

  if (checkButtonPin(10)) {
    sendAck();
    language = receiveData();
    hours = receiveData();
    mins = receiveData();
    secs = receiveData();
    if (hours != -1 && mins != -1 && secs != -1 || language != -1)
    {
      if(hours > 12){
        hours -=12;
        ampm = 62;
      }
      else
        ampm=61;
      playTime();
    }

  }

  for (int i = 0; i < 10; i++) {
    hours = i;
    playTime();
  }
}










