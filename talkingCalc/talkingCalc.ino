#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>

#if defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_Timer1
#include <TimerOne.h>
#elif defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer
#include <SimpleTimer.h>
#endif

SdFat sd;
SFEMP3Shield MP3player;

void setup() {

	uint8_t result;
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

	if (Serial.available()) {
		parse_menu(Serial.read()); // get command from serial input
	}

	delay(100);
}

void parse_menu(byte key_command) {

	uint8_t result;
	Serial.print(F("Received command: "));
	Serial.write(key_command);
	Serial.println(F(" "));

	char title[30];
	char artist[30];
	char album[30];

	if (key_command >= 1 && key_command <= 62) {
		key_command = key_command - 48;
		result = MP3player.playTrack(key_command);
		if (result != 0) {
			Serial.print(F("Error code: "));
			Serial.print(result);
			Serial.println(F(" when trying to play track"));
		} else {
			Serial.println(F("Playing:"));
			MP3player.trackTitle((char*) &title);
			MP3player.trackArtist((char*) &artist);
			MP3player.trackAlbum((char*) &album);
			Serial.write((byte*) &title, 30);
			Serial.println();
			Serial.print(F("by:  "));
			Serial.write((byte*) &artist, 30);
			Serial.println();
			Serial.print(F("Album:  "));
			Serial.write((byte*) &album, 30);
			Serial.println();
		}
	}
}


