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
 * @file DigitalOutput.h
 * @brief Faster version of digitalWrite().
 */
#ifndef DigitalOutput_h
#define DigitalOutput_h

#include <Arduino.h>
#ifdef __AVR__
#include <avr/io.h>
#include <util/atomic.h>
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
  inline __attribute__((always_inline)) void write(bool level) {
    ATOMIC_BLOCK(ATOMIC_FORCEON) { writeI(level); }
  }
  /**
   * @brief Set the level of a digital pin.
   *
   * @param[in] level The value to be set.
   * @note This function must be called with interrupts disabled.
   */
  inline __attribute__((always_inline)) void writeI(bool level) {
    *m_portReg = level ? *m_portReg | m_bit : *m_portReg & m_mask;
  }

 private:
  uint8_t m_bit;
  uint8_t m_mask;
  volatile uint8_t* m_portReg;
};
#else   // _AVR_
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
  inline __attribute__((always_inline)) void write(bool level) {
    digitalWrite(m_pin, level);
  }

 private:
  uint8_t m_pin;
};
#endif  // _AVR_
#endif  // DigitalOutput_h
