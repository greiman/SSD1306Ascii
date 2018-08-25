// Example scrolling display for 64 pixel high display.

#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSpi.h"

// pin definitions
#define CS_PIN  7
#define RST_PIN 8
#define DC_PIN  9

SSD1306AsciiSpi oled;
//------------------------------------------------------------------------------
void setup() {
  // Use next line if no RST_PIN or reset is not required.
  // oled.begin(&Adafruit128x64, CS_PIN, DC_PIN); 
  oled.begin(&Adafruit128x64, CS_PIN, DC_PIN, RST_PIN);
  oled.setFont(System5x7);
  
  #if INCLUDE_SCROLLING == 0
  #error INCLUDE_SCROLLING must be non-zero.  Edit SSD1306Ascii.h
  #endif //  INCLUDE_SCROLLING
  // Set auto scrolling at end of window.
  oled.setScrollMode(SCROLL_MODE_AUTO);
  
  for (int i = 0; i <= 20; i++) {
    if (i == 10) {
      oled.clear();
    }  
    oled.print("Line ");
    oled.println(i);
    delay(500);
  }
  // don't scroll last line.
  oled.print("Done");
}
//------------------------------------------------------------------------------
void loop() {}