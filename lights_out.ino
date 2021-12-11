#include "Adafruit_NeoTrellisM4.h"

// The NeoTrellisM4 object is a keypad and neopixel strip subclass
// that does things like auto-update the NeoPixels and stuff!
Adafruit_NeoTrellisM4 trellis = Adafruit_NeoTrellisM4();

int *lit_keys;

int NUM_KEYS=32;
int NUM_ROWS=4;
int NUM_COLS=8;
int NUM_COLORS=3;

void setup(){
  Serial.begin(115200);
    
  trellis.begin();
  trellis.setBrightness(80);

  Serial.println("toggle keypad test!");

  lit_keys = new int[NUM_KEYS];

  randomSeed(13);
  for (int i=0; i<NUM_KEYS; i++) {
    lit_keys[i] = random(3);
    trellis.setPixelColor(i, to_color(lit_keys[i]));
  }
}

uint32_t to_color(int v) {
   switch(v) {
      case 0 : return 0;
      case 1 : return trellis.Color(0,0,255);
      case 2 : return trellis.Color(0,255,0);
      default : return trellis.Color(255,0,0);
   }
}

int coords_to_key(int row, int col) {
  return row * NUM_COLS + col;
}

int key_to_row(int key) {
  return key / NUM_COLS;
}

int key_to_col(int key) {
  return key % NUM_COLS;
}

void increment_key(int row, int col, int amount) {
   if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS) {
      int key = coords_to_key(row, col);
      lit_keys[key] = (lit_keys[key] + amount) % NUM_COLORS;
      trellis.setPixelColor(key, to_color(lit_keys[key]));
   }
   
}

void loop() {
  // put your main code here, to run repeatedly:
  trellis.tick();

  while (trellis.available()){
    keypadEvent e = trellis.read();
    
    if (e.bit.EVENT == KEY_JUST_PRESSED) {
      int key = e.bit.KEY;  // shorthand for what was pressed
      int row = key_to_row(key);
      int col = key_to_col(key);
      Serial.print(row); Serial.print(","); Serial.print(col);
      Serial.println(" pressed");
      increment_key(row, col, 2);
      increment_key(row - 1, col, 1);
      increment_key(row + 1, col, 1);
      increment_key(row, col - 1, 1);
      increment_key(row, col + 1, 1);
  
            
    }
  }
  
  delay(10);
}
