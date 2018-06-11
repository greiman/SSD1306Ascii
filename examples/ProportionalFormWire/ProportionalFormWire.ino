// Form with proportional font.
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

SSD1306AsciiWire oled;

uint8_t col0 = 0;  // First value column
uint8_t col1 = 0;  // Last value column.
uint8_t rows;      // Rows per line.
//------------------------------------------------------------------------------
void setup() {
  const char* label[] = {"Voltage:", "Load:", "Runtime:"};
  const char* units[] = {"volts", "watts", "mins"};   
  Wire.begin();
  Wire.setClock(400000L);

#if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
#endif // RST_PIN >= 0

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
