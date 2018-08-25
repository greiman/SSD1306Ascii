// Example scrolling display for 64 pixel high display.

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

SSD1306AsciiWire oled;
//------------------------------------------------------------------------------
void setup() {
  Wire.begin();
  Wire.setClock(400000L);

#if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
#endif // RST_PIN >= 0

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