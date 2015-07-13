// Display differences in 5x7 fonts.

#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSpi.h"

// pin definitions
#define OLED_RST 8
#define OLED_DC  9
#define OLED_CS 10

SSD1306AsciiSpi oled;

const char* fontName[] = {
  "Adafruit5x7",
  "font5x7",
  "lcd5x7",
  "System5x7"  
};
const uint8_t* fontList[] = {
  Adafruit5x7,
  font5x7,
  lcd5x7,
  System5x7
};
const uint8_t nFont = sizeof(fontList)/sizeof(const char*);
//------------------------------------------------------------------------------
// Assume fonts start with ' ' and have 96 chars
void checkFont(const uint8_t* font, const char* name) {
  if (pgm_read_byte(font++) ||
      pgm_read_byte(font++) ||
      pgm_read_byte(font++) != 5 ||
      pgm_read_byte(font++) != 7 ||
      pgm_read_byte(font++) != ' ' ||
      pgm_read_byte(font++) < 96) {
      oled.clear();
      oled.print("Bad: ");
      oled.print(name);
      while(1);
   } 
}
//------------------------------------------------------------------------------
void cmp5x7Fonts(const uint8_t* font1, const char* name1,
                 const uint8_t* font2, const char* name2) {
  uint8_t diff[96];
  uint8_t nDiff = 0;
  uint8_t w = 5;
  for (uint8_t i = 0; i < 96; i++) {
    const uint8_t* base1 = font1 + i*w + 6;
    const uint8_t* base2 = font2 + i*w + 6;
    for (uint8_t j = 0; j < w; j++) {
      uint8_t b1 = pgm_read_byte(base1 + j);
      uint8_t b2 = pgm_read_byte(base2 + j);
      if (b1 != b2) {
       diff[nDiff++] = ' ' + i;
       break;
      }
    }
  }
  oled.clear();
  delay(200);
  oled.setFont(font1);
  oled.print(name1);
  oled.setCol(78);
  oled.print("nDiff ");
  oled.println(nDiff);
  oled.setFont(font2);  
  oled.println(name2);

  const uint8_t lineCount = 21;
  if (nDiff > 3*lineCount) nDiff = 3*lineCount;
  for (uint8_t i = 0; i < nDiff; i += lineCount) {  
    oled.setFont(font1);      
    for (uint8_t j = 0; j < lineCount && (j + i) < nDiff; j++) {
      oled.write(diff[i + j]);
    }
    oled.println();
    oled.setFont(font2);
    uint8_t nc = (nDiff - i) > lineCount ? lineCount : nDiff - i;    
    for (uint8_t j = 0; j < nc; j++) {
      oled.write(diff[i + j]);
    }
    oled.println();
  }
  delay(2000 + 500*nDiff);  
}
//------------------------------------------------------------------------------
void setup() { 
  oled.begin(&Adafruit128x64, OLED_CS, OLED_DC);
  oled.setFont(Adafruit5x7);
  oled.clear();
  
  oled.print("Start");
  
  checkFont(Stang5x7, "Stang5x7"); 
  for (uint8_t i = 0; i < nFont; i++) {
    checkFont(fontList[i], fontName[i]);
  }
  
  for (uint8_t i = 0; i < nFont; i++) {
    for (uint8_t j = i + 1; j < nFont; j++) {
      cmp5x7Fonts(fontList[i], fontName[i], fontList[j], fontName[j]);
    }
  }
  // System5x7 derived from Stang5x7? 
  cmp5x7Fonts(Stang5x7, "Stang5x7", System5x7, "System5x7");
 
  oled.print("\nDone");
}
//------------------------------------------------------------------------------
void loop() {}