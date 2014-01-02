void playTime() {
  uint8_t result;
  int key_command = 0;
  char title[30];
  char artist[30];
  char album[30];

  if(language == 2)
  {
    if (!sd.chdir("/english/"))
    {
      sd.errorHalt("sd.chdir");
      Serial.print(F("Error ChangeDir"));
      return;
    }
  }
  else if(language == 1)
  {
    if (!sd.chdir("/arabic/"))
    {
      sd.errorHalt("sd.chdir");
      Serial.print(F("Error ChangeDir"));
      return;
    }
  }
  else{
    return;
  }


  for (int i = 0; i < 3; i++) {
    switch (i) {
    case 0:
      key_command = hours;
      break;
    case 1:
      key_command = mins;
      break;
    case 2:
      key_command = ampm;
      break;
    default:
      break;
    }

    if (key_command >= 1 && key_command <= 62) {
      result = MP3player.playTrack(key_command);
      if (result != 0) {
        Serial.print(F("Error code: "));
        Serial.print(result);
        Serial.println(F(" when trying to play track"));
      } 
      else {
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
}



