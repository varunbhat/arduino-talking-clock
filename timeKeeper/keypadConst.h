#define NUM_KEYS 5
unsigned int adc_key_val[NUM_KEYS] ={
  50, 200, 400, 600, 800 
};


enum keypressed{
  RIGHT=0,
  UP,
  DOWN,
  LEFT,
  SELECT,
  NONE,
  INVALID
};

enum keydown{
  PRESSED,
  RELEASED
};
