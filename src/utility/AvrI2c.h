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
 * @file AvrI2c.h
 * @brief Small fast I2C class for AVR.
 */
#ifndef AvrI2c_h
#define AvrI2c_h
#include <Arduino.h>
#if !defined(__AVR__) || !defined(TWSR)
#error AvrI2c not supported for this chip.
#else  // !defined(__AVR__) || !defined(TWSR)

/** Maximum SCL frecquency */
const uint32_t MAX_SCL_CLOCK = F_CPU / (16 + 2 * 10);

/** Minimum SCL frecquency */
const uint32_t MIN_SCL_CLOCK = F_CPU / (16 + 2 * 255);

/** Bit to or with address for read start and read restart */
uint8_t const I2C_READ = 1;

/** Bit to or with address for write start and write restart */
uint8_t const I2C_WRITE = 0;
//------------------------------------------------------------------------------
// Status codes in TWSR - names are from Atmel TWSR.h with TWSR_ added

/** start condition transmitted */
uint8_t const TWSR_START = 0x08;

/** repeated start condition transmitted */
uint8_t const TWSR_REP_START = 0x10;

/** slave address plus write bit transmitted, ACK received */
uint8_t const TWSR_MTX_ADR_ACK = 0x18;

/** slave address plus write bit transmitted, NACK received */
uint8_t const TWSR_MTX_ADR_NACK = 0x20;

/** data transmitted, ACK received */
uint8_t const TWSR_MTX_DATA_ACK = 0x28;

/** data transmitted, NACK received */
uint8_t const TWSR_MTX_DATA_NACK = 0x30;

/** arbitration lost */
uint8_t const TWSR_ARB_LOST = 0x38;

/** slave address plus read bit transmitted, ACK received */
uint8_t const TWSR_MRX_ADR_ACK = 0x40;

/** slave address plus read bit transmitted, NACK received */
uint8_t const TWSR_MRX_ADR_NACK = 0x48;

/** data byte has been received and ACK tramsmitted */
uint8_t const TWSR_MRX_DATA_ACK = 0x50;

/** data byte has been received and NACK tramsmitted */
uint8_t const TWSR_MRX_DATA_NACK = 0x58;
//------------------------------------------------------------------------------
#define AVR_I2C_DBG 0
#if AVR_I2C_DBG
static void AvrI2cFail(uint16_t line) {
  Serial.print(F("DBG_FAIL: AvrI2c.h:"));
  Serial.println(line);
}
#define DBG_PRINT_HEX(msg, val) \
  {                             \
    Serial.print(F(msg));       \
    Serial.println(val, HEX);   \
  }
#define AVR_I2C_FAIL_MACRO AvrI2cFail(__LINE__)
#else  // AVR_I2C_DBG
#define AVR_I2C_FAIL_MACRO
#define DBG_PRINT_HEX(msg, val)
#endif  // AVR_I2C_DBG
//------------------------------------------------------------------------------
/**
 * \class AvrI2c
 * \brief Hardware I2C master class for AVR.
 *
 * Uses ATmega TWI hardware port
 */
class AvrI2c {
 public:
  /**
   * @brief Initialize prescalar and SLC clock rate.
   * @param[in] fastMode Fast 400 kHz mode if true else standard 100 kHz mode.
   */
  bool begin(bool fastMode = true) {
    // Zero prescaler.
    TWSR = 0;
    // Enable module and acks.
    TWCR = (1 << TWEN) | (1 << TWEA);
    // Set bit rate.
    return setClock(fastMode && F_CPU > 15000000 ? 400000 : 100000);
  }
  /**
   * @brief Disable TWI module.
   */
  void end() { TWCR &= ~((1 << TWEN) | (1 << TWEA)); }
  /**
   * @brief Read a byte and send Ack if more reads follow else
             Nak to terminate read.
   *
   * @param[out] data byte received.
   * @param[in] last Set true to terminate the read else false.
   * @return true for success.
   */
  bool read(uint8_t* data, bool last) {
    if (!execCmd((1 << TWINT) | (1 << TWEN) | (last ? 0 : (1 << TWEA)))) {
      AVR_I2C_FAIL_MACRO;
      return false;
    }
    *data = TWDR;
    if (status() != (last ? TWSR_MRX_DATA_NACK : TWSR_MRX_DATA_ACK)) {
      AVR_I2C_FAIL_MACRO;
      return false;
    }
    return true;
  }
  /**
   * @brief Issue a repeated start condition.
   *
   * same as start with no stop.  Included to document intention.
   *
   * @param[in] addressRW I2C address with read/write bit.
   * @return The value true, 1, for success or false, 0, for failure.
   */
  bool repeatedStart(uint8_t addressRW) { return start(addressRW); }
  /**
   * @brief Set the I2C bit rate.
   *
   * @param[in] clock Desired frequency in Hz.
   *            Valid range for a 16 MHz board is about 40 kHz to 444,000 kHz.
   */
  bool setClock(uint32_t clock) {
    if (clock < MIN_SCL_CLOCK || clock > MAX_SCL_CLOCK) {
      AVR_I2C_FAIL_MACRO;
      return false;
    }
    TWBR = ((F_CPU / clock) - 16) / 2;
    return true;
  }
  /**
   * @brief Issue a start condition.
   *
   * @param[in] addRW I2C address with read/write bit.
   *
   * @return The value true for success or false for failure.
   */
  bool start(uint8_t addRW) {
    // send START condition
    if (!execCmd((1 << TWINT) | (1 << TWSTA) | (1 << TWEN))) {
      AVR_I2C_FAIL_MACRO;
      return false;
    }
    if (status() != TWSR_START && status() != TWSR_REP_START) {
      AVR_I2C_FAIL_MACRO;
      return false;
    }
    // send device address and direction
    TWDR = addRW;
    if (!execCmd((1 << TWINT) | (1 << TWEN))) {
      AVR_I2C_FAIL_MACRO;
      return false;
    }
    if (status() != (addRW & I2C_READ ? TWSR_MRX_ADR_ACK : TWSR_MTX_ADR_ACK)) {
      AVR_I2C_FAIL_MACRO;
      return false;
    }
    return true;
  }
  /** @return status from last TWI command - useful for library debug */
  uint8_t status(void) { return status_; }
  /** Issue a stop condition. */
  bool stop(void) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

    // wait until stop condition is executed and bus released
    for (uint8_t tout = 100; TWCR & (1 << TWSTO); tout--) {
      if (tout == 0) {
        AVR_I2C_FAIL_MACRO;
        return false;
      }
    }
    return true;
  }
  /**
   * @brief Write a byte.
   *
   * @param[in] data The byte to send.
   *
   * @return The value true, 1, if the slave returned an Ack or false for Nak.
   */
  bool write(uint8_t data) {
    TWDR = data;
    if (!execCmd((1 << TWINT) | (1 << TWEN))) {
      AVR_I2C_FAIL_MACRO;
      return false;
    }
    if (status() != TWSR_MTX_DATA_ACK) {
      AVR_I2C_FAIL_MACRO;
      return false;
    }
    return true;
  }

 private:
  uint8_t status_;

  bool execCmd(uint8_t cmdReg) {
    // send command
    TWCR = cmdReg;
    // wait for command to complete
    for (uint16_t n = 0; n != 0XFFFF; n++) {
      if (TWCR & (1 << TWINT)) {
        status_ = TWSR & 0xF8;
        return true;
      }
    }
    AVR_I2C_FAIL_MACRO;
    return false;
  }
};
#endif  // !defined(__AVR__) || !defined(TWSR)
#endif  // AvrI2c_h
