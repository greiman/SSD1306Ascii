// Form with proportional font.
#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSpi.h"

// pin definitions
#define CS_PIN  7
#define RST_PIN 8
#define DC_PIN  9

SSD1306AsciiSpi oled;

uint8_t col0 = 0;  // First value column
uint8_t col1 = 0;  // Last value column. 
uint8_t rows;      // Rows per line.
//------------------------------------------------------------------------------
void setup() {
  const char* label[] = {"Voltage:", "Load:", "Runtime:"};
  const char* units[] = {"volts", "watts", "mins"}; 
  // Use next line if no RST_PIN or reset is not required.
  // oled.begin(&Adafruit128x64, CS_PIN, DC_PIN);  
  oled.begin(&Adafruit128x64, CS_PIN, DC_PIN, RST_PIN);
  
  oled.setFont(Callibri15);
// oled.setFont(Arial14);
// oled.setFont(Callibri11_bold);
// oled.setFont(TimesNewRoman13);

  // Increase space between letters.
  oled.setLetterSpacing(2);
  
  oled.clear();

  // Setup form and find longest label.
  for (uint8_t i = 0; i < 3; i++) {
    oled.println(label[i]);
    uint8_t w = oled.strWidth(label[i]);
    col0 = col0 < w ? w : col0; 
  }
  // Three pixels after label.
  col0 += 3;
  // Allow two or more pixels after value.
  col1 = col0 + oled.strWidth("99.9") + 2;
  // Line height in rows.
  rows = oled.fontRows();
  
  // Print units.
  for ( uint8_t i = 0; i < 3; i++) {
    oled.setCursor(col1 + 1, i*rows);
    oled.print(units[i]);
  }
  delay(3000);  
}
//------------------------------------------------------------------------------
void clearValue(uint8_t row) {
  oled.clear(col0, col1, row, row + rows - 1);
}
//------------------------------------------------------------------------------
void loop() {
  // Fake system model.
  double volts = 0.1*random(110, 130);
  double watts = 0.1*random(200, 500);
  // 100 Wh battery.
  int run = 100*60/(int)watts;
  clearValue(0);
  oled.print(volts, 1);
  clearValue(rows);
  oled.print(watts, 1);
  clearValue(2*rows);
  oled.print(run); 
  delay(1000);  
}

