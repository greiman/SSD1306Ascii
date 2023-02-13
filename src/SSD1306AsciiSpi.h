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
 * @file SSD1306AsciiSpi.h
 * @brief Class for hardware SPI displays.
 */
#ifndef SSD1306AsciiSpi_h
#define SSD1306AsciiSpi_h
#include <SPI.h>

#include "SSD1306Ascii.h"
//------------------------------------------------------------------------------
/**
 * @class SSD1306AsciiSpi
 * @brief Class for SPI displays on the hardware SPI bus.
 */
class SSD1306AsciiSpi : public SSD1306Ascii {
 public:
  /**
   * @brief Initialize the display controller.
   *
   * @param[in] dev A device initialization structure.
   * @param[in] cs The display controller chip select pin.
   * @param[in] dc The display controller data/command pin.
   */
  void begin(const DevType* dev, uint8_t cs, uint8_t dc) {
    m_cs = cs;
    m_dc = dc;
    pinMode(m_cs, OUTPUT);
    pinMode(m_dc, OUTPUT);
    SPI.begin();
    init(dev);
  }
  /**
   * @brief Initialize the display controller.
   *
   * @param[in] dev A device initialization structure.
   * @param[in] cs The display controller chip select pin.
   * @param[in] dc The display controller cdata/command pin.
   * @param[in] rst The display controller reset pin.
   */
  void begin(const DevType* dev, uint8_t cs, uint8_t dc, uint8_t rst) {
    oledReset(rst);
    begin(dev, cs, dc);
  }

 protected:
  void writeDisplay(uint8_t b, uint8_t mode) {
    digitalWrite(m_dc, mode != SSD1306_MODE_CMD);
    SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
    digitalWrite(m_cs, LOW);
    SPI.transfer(b);
    digitalWrite(m_cs, HIGH);
    SPI.endTransaction();
  }

  int8_t m_cs;
  int8_t m_dc;
};
#endif  // SSD1306AsciiSpi_h
