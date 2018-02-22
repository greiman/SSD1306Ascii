// Simple software SPI test for ebay 128x64 oled.

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
