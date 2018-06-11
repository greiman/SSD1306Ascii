// Set display remap mode.
// displayRemap(bool mode) selects normal mode or 180 degree rotation mode.

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
  oled.setFont(Adafruit5x7);

  // Use true, normal mode, since default for Adafruit display is remap mode.
  oled.displayRemap(true);

  oled.clear();
  oled.println("Hello world!");
  oled.println("displayRemap(false)");
  oled.print("for other mode.");
}
//------------------------------------------------------------------------------
void loop() {}
