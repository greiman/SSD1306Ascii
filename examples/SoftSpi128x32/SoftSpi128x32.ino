// Simple software SPI test for Adafruit 128x32 oled.
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSoftSpi.h"

// pin definitions
#define CS_PIN    7
#define RST_PIN   8
#define DC_PIN    9
#define OLED_DATA 11
#define OLED_CLK  13

SSD1306AsciiSoftSpi oled;
//------------------------------------------------------------------------------
void setup() {
  // Use next line if no RST_PIN or reset is not required.
  // oled.begin(&Adafruit128x32, CS_PIN, DC_PIN, OLED_CLK, OLED_DATA);  
  oled.begin(&Adafruit128x32, CS_PIN, DC_PIN, OLED_CLK, OLED_DATA, RST_PIN);
  oled.setFont(Adafruit5x7);  

  uint32_t m = micros();
  oled.clear(); 
  oled.println("Hello world!");
  oled.println("A long line may be truncated");
  oled.print("\nmicros: ");
  oled.print(micros() - m);
}
//------------------------------------------------------------------------------
void loop() {}