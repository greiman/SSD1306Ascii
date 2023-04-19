// SSD1306AsciiSoftWire.h Sample Program
// https://youtu.be/JHlt9EG22BI

// https://github.com/stevemarple/SoftWire
#include <SoftWire.h>

#include <SSD1306Ascii.h>
#include <SSD1306AsciiSoftWire.h>

#define OLED_I2C_ADDRESS 0x3C

// ESP32-C3 Tested OK
// #define OLED_SDA 0
// #define OLED_SCL 1

// ESP32-S2 Tested OK
#define OLED_SDA 7
#define OLED_SCL 9

// RP2040 Tested NG SoftWire signal contain Pulse
// #define OLED_SDA 20
// #define OLED_SCL 21

SoftWire WireOled = SoftWire(OLED_SDA, OLED_SCL);
SSD1306AsciiSoftWire oled = SSD1306AsciiSoftWire(&WireOled);

void setup() {
  // put your setup code here, to run once:
  static uint8_t txBuffer[32];
  WireOled.setTxBuffer(txBuffer, 32);
  // WireOled.setClock(10000);
  WireOled.begin();

  oled.begin(&MicroOLED64x32, OLED_I2C_ADDRESS);
  // oled.begin(&Adafruit128x32, OLED_I2C_ADDRESS);
  oled.setFont(System5x7);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  static int invert = 0;

  invert = 1 - invert;

  oled.setInvertMode(invert);
  oled.setCursor(0, 0);
  oled.set1X();
  oled.print("SoftWire");

  oled.setCursor(0, 1);
  oled.set2X();
  oled.print("SoftWire");

  oled.setInvertMode(!invert);
  oled.setCursor(0, 3);
  oled.set1X();
  oled.print("SoftWire");
}

