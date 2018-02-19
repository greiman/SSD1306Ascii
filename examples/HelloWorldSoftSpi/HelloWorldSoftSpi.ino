// Test for minimum program size.

// pin definitions
#define OLED_DC    9
#define OLED_CS   10
#define OLED_CLK  13
#define OLED_DATA 11

#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSoftSpi.h"

SSD1306AsciiSoftSpi oled;
//------------------------------------------------------------------------------
void setup() {                
  oled.begin(&Adafruit128x64, OLED_CS, OLED_DC, OLED_CLK, OLED_DATA);
  oled.setFont(System5x7);
  oled.clear();
  oled.print("Hello world!");
}
//------------------------------------------------------------------------------
void loop() {}