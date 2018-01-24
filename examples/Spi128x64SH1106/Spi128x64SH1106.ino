// Simple SPI test for ebay 128x64 oled.

// pin definitions
#define OLED_RST 8
#define OLED_DC 9
#define OLED_CS 10

#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSpi.h"

SSD1306AsciiSpi oled;
//------------------------------------------------------------------------------
void setup() {         
  oled.begin(&SH1106_128x64, OLED_CS, OLED_DC, OLED_RST);
  oled.setFont(Adafruit5x7);  

  uint32_t m = micros();
  oled.clear();  
  oled.println("Hello world!");
  oled.println("A long line may be truncated");
  oled.println();
  oled.set2X();
  oled.println("2X demo");
  oled.set1X();
  oled.print("\nmicros: ");
  oled.print(micros() - m);
}
//------------------------------------------------------------------------------
void loop() {}
