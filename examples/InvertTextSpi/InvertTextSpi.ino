// Demo of invertMode and invertDisplay.
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