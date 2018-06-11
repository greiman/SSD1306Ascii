// Set display remap mode.
// displayRemap(bool mode) selects normal mode or 180 degree rotation mode.

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

  // Use true, normal mode, since default for Adafruit display is remap mode.
  oled.displayRemap(true);

  oled.clear();
  oled.println("Hello world!");
  oled.println("displayRemap(false)");
  oled.print("for other mode.");
}
//------------------------------------------------------------------------------
void loop() {}
