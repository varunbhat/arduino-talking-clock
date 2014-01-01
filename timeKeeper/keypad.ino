#define NUM_KEYS 5
unsigned int adc_key_val[NUM_KEYS] ={
  50, 200, 400, 600, 800 
};


enum keydown{
  PRESSED,
  RELEASED
};


keydown keypadStatus = RELEASED;
keypressed prevKey = NONE;

int get_key()
{
  unsigned int k;
  unsigned int input = analogRead(0); 
  for (k = 0; k < NUM_KEYS; k++){
    if (input < adc_key_val[k]){
      switch(k){
      case 0: 
        return RIGHT; 
        break;
      case 1: 
        return UP; 
        break;
      case 2: 
        return DOWN; 
        break;
      case 3: 
        return LEFT; 
        break;
      case 4: 
        return SELECT; 
        break;
      default: 
        return INVALID; 
        break;

      }
    }
  }
  return NONE;
}



