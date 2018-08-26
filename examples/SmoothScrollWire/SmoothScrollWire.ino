// Demo of advanced scrolling features.
// This example is based on a program by david gauchard.
// Use a display with height < 64.
// You may want to look at the SSD1306 data sheet for more info.
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN 8

SSD1306AsciiWire oled;

int blank = 0; // Count of blank lines.
int count = 0; // Count of displayed lines.
int dir = 1;   // Scroll direction.
uint32_t scrollTime = 0;
//------------------------------------------------------------------------------
void setup () {
  Wire.begin();
  Wire.setClock(400000L);

  // MicroOLED64x48 or Adafruit128x32 work well.
#if RST_PIN >= 0
  oled.begin(&Adafruit128x32, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x32, I2C_ADDRESS);
#endif // RST_PIN >= 0
  oled.setFont(System5x7);
  oled.clear();

  // Not really needed since newline will not scroll the display in this example.
  oled.setScrollMode(SCROLL_MODE_APP);

  oled.print("Smooth\nScrolling\ndemo");
  delay(3000);

  // Set cursor to last row of window.
  oled.setRow(oled.displayRows() - oled.fontRows());
}
//------------------------------------------------------------------------------
void loop () {
  if (!oled.scrollIsSynced()) {
    uint32_t now = millis();
    if ((now - scrollTime) >= 15) {
      // Scroll display window.
      oled.scrollDisplay(dir);
      scrollTime = now;
    }
    // Reduce flicker by allowing display to scroll before writing.
  } else if ((millis() - scrollTime) > 15) {
    // Done if screen is blank.
    if (blank*oled.fontRows() > oled.displayRows()) {
      // Set new direction and magnification.
      blank = 0;
      count = 0;
      // Reverse scroll direction.
      dir = -dir;
      // Set font magnification.
      if (dir > 0) {
        if (oled.magFactor() == 1) {
          oled.set2X();
        } else {
          oled.set1X();
        }
      }
      // Set cursor to first or last line of memory window.
      oled.setCursor(0, dir < 0 ? 0 : oled.displayRows() - oled.fontRows());
    }
    // Scroll memory window.
    oled.scrollMemory(dir*oled.fontRows());
    oled.setCol(0);
    if (count*oled.fontRows() <= oled.displayRows()) {
      oled.print(dir < 0 ? "DN " : "UP ");
      oled.print(++count);
    } else {
      blank++;
    }
    oled.clearToEOL();
  }
}