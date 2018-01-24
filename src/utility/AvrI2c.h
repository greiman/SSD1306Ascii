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
 * @file AvrI2c.h
 * @brief Small fast I2C class for AVR.
 */ 
#ifndef AvrI2c_h
#define AvrI2c_h
#include <Arduino.h>

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

/** data transmitted, ACK received */
uint8_t const TWSR_MTX_DATA_ACK = 0x28;

/** slave address plus read bit transmitted, ACK received */
uint8_t const TWSR_MRX_ADR_ACK = 0x40;
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
  void begin(bool fastMode = true) {
    // Zero prescaler.
    TWSR = 0;
    // Set bit rate factor.
    TWBR = fastMode ? (F_CPU/400000 - 16)/2 : (F_CPU/100000 - 16)/2;
  }
  /** 
   * @brief Read a byte and send Ack if more reads follow else 
             Nak to terminate read.
   *
   * @param[in] last Set true to terminate the read else false.
   * @return The byte read from the I2C bus.
   */
  uint8_t read(bool last) {
    execCmd((1 << TWINT) | (1 << TWEN) | (last ? 0 : (1 << TWEA)));
    return TWDR;
  }
  /** 
   * @brief Issue a repeated start condition.
   *
   * same as start with no stop.  Included to document intention.
   *
   * @param[in] addressRW I2C address with read/write bit.
   * @return The value true, 1, for success or false, 0, for failure.
   */
  bool repeatedStart(uint8_t addressRW) {
    return start(addressRW);
  }
  /** 
   * @brief Issue a start condition.
   *
   * @param[in] addressRW I2C address with read/write bit.
   *
   * @return The value true for success or false for failure.
   */
  bool start(uint8_t addressRW) {
    // send START condition
    execCmd((1<<TWINT) | (1<<TWSTA) | (1<<TWEN));
    if (status() != TWSR_START && status() != TWSR_REP_START) {
      return false;
    }
    // send device address and direction
    TWDR = addressRW;
    execCmd((1 << TWINT) | (1 << TWEN));
    if (addressRW & I2C_READ) {
      return status() == TWSR_MRX_ADR_ACK;
    } else {
      return status() == TWSR_MTX_ADR_ACK;
    }
  }
  /** @return status from last TWI command - useful for library debug */
  uint8_t status(void) {return status_;}
  /** Issue a stop condition. */
  void stop(void) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);

    // wait until stop condition is executed and bus released
    while (TWCR & (1 << TWSTO));
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
    execCmd((1 << TWINT) | (1 << TWEN));
    return status() == TWSR_MTX_DATA_ACK;
  }
 
 private:
  uint8_t status_;
  
  void execCmd(uint8_t cmdReg) {
    // send command
    TWCR = cmdReg;
    // wait for command to complete
    while (!(TWCR & (1 << TWINT)));
    // status bits.
    status_ = TWSR & 0xF8;
  }
};
#endif  // AvrI2c_h