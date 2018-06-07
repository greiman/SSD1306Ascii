// Test of clearField() and fieldWidth().
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