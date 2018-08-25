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
 * @file SSD1306AsciiWire.h
 * @brief Class for I2C displays using Wire.
 */
#ifndef SSD1306AsciiWire_h
#define SSD1306AsciiWire_h
#include <Wire.h>
#include "SSD1306Ascii.h"
/**
 * @class SSD1306AsciiWire
 * @brief Class for I2C displays using Wire.
 */
class SSD1306AsciiWire : public SSD1306Ascii {
 public:
  /**
   * @brief Initialize the display controller.
   *
   * @param[in] dev A device initialization structure.
   * @param[in] i2cAddr The I2C address of the display controller.
   */
  void begin(const DevType* dev, uint8_t i2cAddr) {
#if OPTIMIZE_I2C
    m_nData = 0;
#endif  // OPTIMIZE_I2C
    m_i2cAddr = i2cAddr;
    init(dev);
  }
  /**
   * @brief Initialize the display controller.
   *
   * @param[in] dev A device initialization structure.
   * @param[in] i2cAddr The I2C address of the display controller.
   * @param[in] rst The display controller reset pin.
   */
  void begin(const DevType* dev, uint8_t i2cAddr, uint8_t rst) {
    oledReset(rst);
    begin(dev, i2cAddr);
  }
  /**
   * @brief Set the I2C clock rate to 400 kHz.
   * Deprecated use Wire.setClock(400000L)
   */
  void set400kHz() __attribute__((deprecated("use Wire.setClock(400000L)"))) {
    Wire.setClock(400000L);
  }

 protected:
  void writeDisplay(uint8_t b, uint8_t mode) {
#if OPTIMIZE_I2C
    if (m_nData > 16 || (m_nData && mode == SSD1306_MODE_CMD)) {
      Wire.endTransmission();
      m_nData = 0;
    }
    if (m_nData == 0) {
      Wire.beginTransmission(m_i2cAddr);
      Wire.write(mode == SSD1306_MODE_CMD ? 0X00 : 0X40);
    }
    Wire.write(b);
    if (mode == SSD1306_MODE_RAM_BUF) {
      m_nData++;
    } else {
      Wire.endTransmission();
      m_nData = 0;
    }
#else  // OPTIMIZE_I2C
    Wire.beginTransmission(m_i2cAddr);
    Wire.write(mode == SSD1306_MODE_CMD ? 0X00: 0X40);
    Wire.write(b);
    Wire.endTransmission();
#endif    // OPTIMIZE_I2C
  }

 protected:
  uint8_t m_i2cAddr;
#if OPTIMIZE_I2C
  uint8_t m_nData;
#endif  // OPTIMIZE_I2C
};
#endif  // SSD1306AsciiWire_h
