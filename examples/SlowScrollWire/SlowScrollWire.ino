// Demo of smooth scrolling by an application.
//
// Note - smooth scrolling only works well on displays with height < 64.
// Smaller displays allow the line being written to be hidden until it
// is scrolled.  The newly written line will flash at the top of 64
// high displays.
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C
// Define proper RST_PIN if required.

#define RST_PIN -1
SSD1306AsciiWire oled;

void setup() {
  Wire.begin();
  Wire.setClock(400000L);
#if RST_PIN >= 0
  oled.begin(&Adafruit128x32, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x32, I2C_ADDRESS);
#endif // RST_PIN >= 0

  oled.setFont(System5x7);
  oled.clear();
  
  // Application will handle scrolling
  oled.setScrollMode(SCROLL_MODE_APP);
  
  // Set cursor to last line of RAM window.
  oled.setRow(oled.displayRows() - oled.fontRows());
}

uint32_t scrollTime;
uint16_t line;
void loop() {
  if (oled.scrollIsSynced()) {
    // Scroll memory window one row (8 scan lines) with a newline ('\n').
    oled.print("\nLine ");
    oled.print(line++);
  } else {
    uint32_t now = millis();
    if ((now - scrollTime) > 50) {
      // Scroll display window one scan line. 
      oled.scrollDisplay(1);
      scrollTime = now;
    }
  }
}

