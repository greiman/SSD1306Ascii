// Demo of invertMode and invertDisplay.
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
  oled.clear();
  oled.println("normal");
  oled.println();
}
//------------------------------------------------------------------------------
void loop() {
  for (int i = 0; i < 4; i++) {
    // Toggle invert mode for next line of text.
    oled.setInvertMode(i%2);
    oled.print("\rinvert");
    delay(500);
  }
  for (int i = 0; i < 4; i++) {
    // Invert all text on screen.
    oled.invertDisplay(!(i%2));
    delay(1000);
  }
}