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
 * @file DigitalOutput.h
 * @brief Faster version of digitalWrite().
 */
#ifndef DigitalOutput_h
#define DigitalOutput_h

#include <Arduino.h>
#ifdef __AVR__
#include <util/atomic.h>
#include <avr/io.h>
/**
 * @class DigitalOutput
 * @brief Faster version of digitalWrite().
 */
class DigitalOutput {
 public:
  /**
   * @breif initialize the digital pin.
   *
   * @param[in] pin The Arduino pin number.
   */
  void begin(uint8_t pin) {
    uint8_t port = digitalPinToPort(pin);
    m_portReg = portOutputRegister(port);
    m_bit = digitalPinToBitMask(pin);
    m_mask = ~m_bit;
    pinMode(pin, OUTPUT);
  }
  /**
   * @brief Set the level of a digital pin.
   *
   * @param[in] level The value to be set.
   */
  inline __attribute__((always_inline))
  void write(bool level) {ATOMIC_BLOCK(ATOMIC_FORCEON) {writeI(level);}}
  /**
   * @brief Set the level of a digital pin.
   *
   * @param[in] level The value to be set.
   * @note This function must be called with interrupts disabled.
   */
  inline __attribute__((always_inline))
  void writeI(bool level) {
    *m_portReg = level ? *m_portReg | m_bit : *m_portReg & m_mask;
  }

 private:
  uint8_t m_bit;
  uint8_t m_mask;
  volatile uint8_t* m_portReg;
};
#else  // _AVR_
/**
 * @class DigitalOutput
 * @brief Non AVR version of digitalWrite().
 */
class DigitalOutput {
 public:
  /**
   * @brief initialize the digital pin.
   *
   * @param[in] pin The Arduino pin number.
   */
  void begin(uint8_t pin) {
    m_pin = pin;
    pinMode(m_pin, OUTPUT);
  }
  /**
   * @brief Set the level of a digital pin.
   *
   * @param[in] level The value to be set.
   */
  inline __attribute__((always_inline))
  void write(bool level) {
    digitalWrite(m_pin, level);
  }
 private:
  uint8_t m_pin;
};
#endif  // _AVR_
#endif  // DigitalOutput_h
