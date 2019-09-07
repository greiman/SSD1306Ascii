// Ticker demo for I2C 128x64 oled.

// The ticker shifts text through a one line field on the display.
// A queue of text pointers is maintained by the ticker. You must
// not modify a text string while its pointer is in the queue.
// The display queue size is define by TICKER_QUEUE_DIM in SSD1306Ascii.h.

// tickerTick() returns the current length of the display pointer queue.
// If tickerText() is called for a return <= one, the display is continuous.
// If tickerText() is called for return zero, all text will be shifted off
// the display before another string starts.
//
// Try values of zero or one for RTN_CHECK.
#define RTN_CHECK 1

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

SSD1306AsciiWire oled;

// Ticker state. Maintains text pointer queue and current ticker state.
TickerState state;

// Use two strings to avoid modifying string being displayed.
String str[2];
//------------------------------------------------------------------------------
void setup() {
  Wire.begin();
  Wire.setClock(400000L);

#if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
#endif // RST_PIN >= 0

  // Use Adafruit5x7, field at row 2, set2X, columns 16 through 100.
  oled.tickerInit(&state, Adafruit5x7, 2, true, 16, 100);
}

uint16_t count;
uint32_t tickTime = 0;

void loop() {
  if (tickTime <= millis()) {
    tickTime = millis() + 30;

    // Should check for error. rtn < 0 indicates error.
    int8_t rtn = oled.tickerTick(&state);

    // See above for definition of RTN_CHECK.
    if (rtn <= RTN_CHECK) {
      uint8_t pin = count%4;

      // ping-pong string selection so displayed string is not modified.
      uint8_t n = count%2;

      str[n] = "ADC" + String(pin) + ": " + analogRead(pin) + ", ";

      // Should check for error. Return of false indicates error.
      oled.tickerText(&state, str[n]);
      count++;
    }
  }
}
