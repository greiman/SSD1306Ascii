/**
 * Copyright (c) 2011-2023 Bill Greiman
 * This file is part of the Arduino SSD1306Ascii Library
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
/**
 * @file SSD1306AsciiSoftSpi.h
 * @brief Class for software SPI displays.
 */
#ifndef SSD1306AsciiSoftSpi_h
#define SSD1306AsciiSoftSpi_h

#include "SSD1306Ascii.h"
#include "utility/DigitalOutput.h"
/**
 * @class SSD1306AsciiSoftSpi
 * @brief Class for SPI displays using software SPI.
 */
class SSD1306AsciiSoftSpi : public SSD1306Ascii {
 public:
  /**
   * @brief Initialize the display controller.
   *
   * @param[in] dev A device initialization structure.
   * @param[in] cs The display controller chip select pin.
   * @param[in] dc The display controller cdata/command pin.
   * @param[in] clk The SPI clock pin.
   * @param[in] data The SPI MOSI pin.
   */
  void begin(const DevType* dev, uint8_t cs, uint8_t dc, uint8_t clk,
             uint8_t data) {
    m_csPin.begin(cs);
    m_dcPin.begin(dc);
    m_clkPin.begin(clk);
    m_dataPin.begin(data);
    init(dev);
  }
  /**
   * @brief Initialize the display controller.
   *
   * @param[in] dev A device initialization structure.
   * @param[in] cs The display controller chip select pin.
   * @param[in] dc The display controller cdata/command pin.
   * @param[in] clk The SPI clock pin.
   * @param[in] data The SPI MOSI pin.
   * @param[in] rst The display controller reset pin.
   */
  void begin(const DevType* dev, uint8_t cs, uint8_t dc, uint8_t clk,
             uint8_t data, uint8_t rst) {
    pinMode(rst, OUTPUT);
    digitalWrite(rst, LOW);
    delay(10);
    digitalWrite(rst, HIGH);
    delay(10);
    begin(dev, cs, dc, clk, data);
  }

 protected:
  void writeDisplay(uint8_t b, uint8_t mode) {
    m_dcPin.write(mode != SSD1306_MODE_CMD);
    m_csPin.write(LOW);
    for (uint8_t m = 0X80; m; m >>= 1) {
      m_clkPin.write(LOW);
      m_dataPin.write(m & b);
      m_clkPin.write(HIGH);
    }
    m_csPin.write(HIGH);
  }

 protected:
  DigitalOutput m_csPin;
  DigitalOutput m_dcPin;
  DigitalOutput m_clkPin;
  DigitalOutput m_dataPin;
};
#endif  // SSD1306AsciiSoftSpi_h
