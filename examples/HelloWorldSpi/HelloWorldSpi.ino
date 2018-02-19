// Test for minimum program size.

// pin definitions
#define OLED_DC 9
#define OLED_CS 10

#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSpi.h"

SSD1306AsciiSpi oled;
//------------------------------------------------------------------------------
void setup() {                
  oled.begin(&Adafruit128x64, OLED_CS, OLED_DC);
  oled.setFont(System5x7);
  oled.clear();
  oled.print("Hello world!");
}
//------------------------------------------------------------------------------
void loop() {}