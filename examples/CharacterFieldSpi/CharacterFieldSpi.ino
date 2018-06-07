// Test of clearField() and fieldWidth().

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
  
  // Start row and column of field.
  uint8_t col = 20;
  uint8_t row = 2;
  
  // Set cursor to start of field. 
  oled.setCursor(col, row);
  
  // print test pattern.
  oled.print("123456789");
  delay(1000);
  
  // Clear 4 characters starting at character 2.
  oled.clearField(col + oled.fieldWidth(2), row, 4);
  delay(1000);
  
  // Print three characters in cleared area.
  oled.print("ABC");
}
//------------------------------------------------------------------------------
void loop() {}