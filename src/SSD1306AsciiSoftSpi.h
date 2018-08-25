/* Arduino SSD1306Ascii Library
 * Copyright (C) 2015 by William Greiman
 *
 * This file is part of the Arduino SSD1306Ascii Library
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Arduino SSD1306Ascii Library.  If not, see
 * <http://www.gnu.org/licenses/>.
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
  void begin(const DevType* dev, uint8_t cs,
             uint8_t dc, uint8_t clk, uint8_t data) {
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
  void begin(const DevType* dev, uint8_t cs,
             uint8_t dc, uint8_t clk, uint8_t data, uint8_t rst) {
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
