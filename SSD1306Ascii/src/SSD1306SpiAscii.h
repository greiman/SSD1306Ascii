/**
 * @file SSD1306SpiAscii.h
 * @brief Class for hardware SPI displays.
 */
#ifndef SSD1306SpiAscii_h
#define SSD1306SpiAscii_h
#include <SPI.h>
#include "SSD1306Ascii.h"

#if !defined(__AVR__) || OPTIMIZE_AVR_SPI == 0
//------------------------------------------------------------------------------
/**
 * @class SSD1306SpiAscii
 * @brief Class for SPI displays on the hardware SPI bus.
 */
class SSD1306SpiAscii : public SSD1306Ascii {
 public:
  /**
   * @brief Initialize the display controller.
   *
   * @param[in] dev A device initialization structure.
   * @param[in] cs The display controller chip select pin.
   * @param[in] dc The display controller cdata/command pin.   
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
    reset(rst);
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
  
 private:
  int8_t m_cs;
  int8_t m_dc;
};
//------------------------------------------------------------------------------
#else  // OPTIMIZE_AVR_SPI
#include "DigitalOutput.h"
/**
 * @class SSD1306SpiAscii
 * @brief Class for SPI displays on the hardware SPI bus.
 */
class SSD1306SpiAscii : public SSD1306Ascii {
 public:
  /**
   * @brief Initialize the display controller.
   *
   * @param[in] dev A device initialization structure.
   * @param[in] cs The display controller chip select pin.
   * @param[in] dc The display controller cdata/command pin.   
   */  
  void begin(const DevType* dev, uint8_t cs, uint8_t dc) {
    m_csPin.begin(cs);
    m_dcPin.begin(dc);
#ifdef __AVR_ATmega328P__
    // Save a few bytes for 328 CPU - gcc optimizes single bit '|' to sbi.
    PORTB |= 1 << 2;  // SS high
    DDRB  |= 1 << 2;  // SS output mode
    DDRB  |= 1 << 3;  // MOSI output mode
    DDRB  |= 1 << 5;  // SCK output mode
#else  // __AVR_ATmega328P__    
    SPI.begin();
#endif  // __AVR_ATmega328P__
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
    reset(rst);
    begin(dev, cs, dc);
  }
  
 protected:
  //----------------------------------------------------------------------------
  void writeDisplay(uint8_t b, uint8_t mode) {
    m_dcPin.write(mode != SSD1306_MODE_CMD);
    // 8 MHz, SPI_MODE0, MSBFIRST
    SPCR = (1 << SPE) | (1 << MSTR);
    SPSR = 1 << SPI2X;
    m_csPin.write(LOW);
    SPI.transfer(b);
    m_csPin.write(HIGH);
  }
  
 private:
  DigitalOutput m_csPin;
  DigitalOutput m_dcPin;
};
#endif  // OPTIMIZE_AVR_SPI
#endif SSD1306SpiAscii_h