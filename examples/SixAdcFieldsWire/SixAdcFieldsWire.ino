// Display values for six ADCs.
// On Uno, ADC4 and ADC5 are I2C pins.

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

SSD1306AsciiWire oled;

uint8_t col[2]; // Columns for ADC values.
uint8_t rows;   // Rows per line.
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

  // Setup form.  Could use F() macro to save RAM on AVR.
  oled.println("ADC0: 9999 ADC1: 9999");
  oled.println("ADC2: 9999 ADC3: 9999");
  oled.println("ADC4: 9999 ADC5: 9999");
  
  // Calculate columns for ADC values.  No RAM is used by strings.
  // Compiler replaces strlen() calc with 6 and 17.  
  col[0] = oled.fieldWidth(strlen("ADC0: "));
  col[1] = oled.fieldWidth(strlen("ADC0: 9999 ADC1: "));
  rows = oled.fontRows();
  delay(3000);  
}
//------------------------------------------------------------------------------
void loop() {
  for (uint8_t i = 0; i < 6; i++) {  
    oled.clearField(col[i%2], rows*(i/2), 4);    
    oled.print(analogRead(i));
  }
  delay(1000);
}
