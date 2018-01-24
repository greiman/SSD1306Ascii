// Simple I2C test for 128x32 oled.
// Use smaller faster AvrI2c class in place of Wire.
//
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

SSD1306AsciiAvrI2c oled;
//------------------------------------------------------------------------------
void setup() {         
  
  oled.begin(&Adafruit128x32, I2C_ADDRESS);
  oled.setFont(Adafruit5x7);  

  uint32_t m = micros();
  
  oled.clear();  
  //first row
  oled.println("set1X - test");
  //second row
  oled.set2X(); 
  oled.println("set2X - test");
  //third row
  oled.set1X();
  oled.print("micros: ");
  oled.print(micros() - m);
}
//------------------------------------------------------------------------------
void loop() {}