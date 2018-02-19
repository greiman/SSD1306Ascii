// This example is a development tool and does not use the display.
// Print simple representation of ASCII characters for 5x7 fixed fonts.
//
#include "SdFat.h"
#include "SSD1306Ascii.h"
const char* fontName[] = {
  "Adafruit5x7",
  "font5x7",
  "lcd5x7",
  "Stang5x7",
  "System5x7"  
};
const uint8_t* fontList[] = {
  Adafruit5x7,
  font5x7,
  lcd5x7,
  Stang5x7,
  System5x7
};
const uint8_t nFont = sizeof(fontList)/sizeof(const char*);
SdFat sd;
SdFile file;
//------------------------------------------------------------------------------
// return bitmap for a character
void charBitmap(const uint8_t* font, uint8_t c, uint8_t* bits) {
  c -= 32;
  const uint8_t *base = font + 6 + 5 * c;
  for (uint8_t i =0; i < 5; i++ ) {
    bits[i] = pgm_read_byte(base + i);
  }
}
//------------------------------------------------------------------------------
void printChar(const uint8_t*font, uint8_t c) {
  uint8_t bits[192];
  // get bit maps
  for (uint8_t i = 0; i < 32;  i++) {    
    charBitmap(font, c + i, bits + 6*i);
    bits[6*i + 5] = 0;
  }
  // print characters
  for (uint8_t m = 1; m; m <<= 1) {
    for (uint8_t i = 0; i < 192; i++) {
      file.write(bits[i] & m ? 'X' : ' ');
    }
    file.println();
  }
}
//------------------------------------------------------------------------------
void setup()   {
  Serial.begin(9600);
  if (!sd.begin()) {
    Serial.println("begin error"); 
    return;   
  }
  char name[] = "5x7fonts.txt";
  if (!file.open(name, O_CREAT | O_WRITE |O_TRUNC)) {
    Serial.println("OPEN ERROR");
    return;
  }
  for (uint8_t i = 0; i < nFont; i++) {
    file.println();
    file.println(fontName[i]);
    for (uint8_t c = 32; c < 128; c += 32) {
      file.println();
      printChar(fontList[i], c);
    }
    file.println();
  }
  file.close();
  Serial.println("DONE");
}
//------------------------------------------------------------------------------
void loop(){ }