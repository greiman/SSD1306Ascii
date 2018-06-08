// Display values for six ADCs.
#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSpi.h"

// pin definitions
#define CS_PIN  7
#define RST_PIN 8
#define DC_PIN  9

SSD1306AsciiSpi oled;

uint8_t col[2]; // Columns for ADC values.
uint8_t rows;   // Rows per line.
//------------------------------------------------------------------------------
void setup() {
  // Use next line if no RST_PIN or reset is not required.
  // oled.begin(&Adafruit128x64, CS_PIN, DC_PIN);  
  oled.begin(&Adafruit128x64, CS_PIN, DC_PIN, RST_PIN);
  oled.setFont(System5x7);
  oled.clear();

  // Setup form.  Could use F() macro to save RAM on AVR.
  oled.println("ADC0: 9999 ADC1: 9999");
  oled.println("ADC2: 9999 ADC3: 9999");
  oled.println("ADC4: 9999 ADC5: 9999");
  
  // Calculate columns for ADC values.  No RAM is used by the strings.
  // The gcc compiler replaces strlen() with 6 and 17.
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
