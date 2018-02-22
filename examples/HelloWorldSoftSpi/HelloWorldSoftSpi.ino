// Test for minimum program size.

#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSoftSpi.h"

// pin definitions
#define CS_PIN    7
#define RST_PIN   8
#define DC_PIN    9
#define MOSI_PIN 11
#define CLK_PIN  13

SSD1306AsciiSoftSpi oled;
//------------------------------------------------------------------------------
void setup() {
  // Use next line if no RST_PIN or reset is not required.
  // oled.begin(&Adafruit128x64, CS_PIN, DC_PIN, CLK_PIN, MOSI_PIN);  
  oled.begin(&Adafruit128x64, CS_PIN, DC_PIN, CLK_PIN, MOSI_PIN, RST_PIN);
  oled.setFont(System5x7);
  oled.clear();
  oled.print("Hello world!");
}
//------------------------------------------------------------------------------
void loop() {}