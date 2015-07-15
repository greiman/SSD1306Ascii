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
 * @file SSD1306init.h
 * @brief Display controller initialization commands.
 */
#ifndef SSD1306init_h
#define SSD1306init_h
//------------------------------------------------------------------------------
/** No Operation Command. */
#define SSD1306_NOP 0XE3
/** Set Display Contrast to one of 256 steps. */
#define SSD1306_SETCONTRAST 0x81
/** Resume display from GRAM content. */
#define SSD1306_DISPLAYALLON_RESUME 0xA4
/** Force display on regardless of GRAM content. */
#define SSD1306_DISPLAYALLON 0xA5
/** Set Normal Display. */
#define SSD1306_NORMALDISPLAY 0xA6
/** Set Inverse Display. */
#define SSD1306_INVERTDISPLAY 0xA7
/** Set Display off. */
#define SSD1306_DISPLAYOFF 0xAE
/** Set Display on. */
#define SSD1306_DISPLAYON 0xAF
/** Set Display Offset. */
#define SSD1306_SETDISPLAYOFFSET 0xD3
/** Sets COM signals pin configuration to match the OLED panel layout. */
#define SSD1306_SETCOMPINS 0xDA
/** This command adjusts the VCOMH regulator output. */
#define SSD1306_SETVCOMDETECT 0xDB
/** Set Display Clock Divide Ratio/ Oscillator Frequency. */
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
/** Set Pre-charge Period */
#define SSD1306_SETPRECHARGE 0xD9
/** Set Multiplex Ratio from 16 to 63. */
#define SSD1306_SETMULTIPLEX 0xA8
/** Set Lower Column Start Address for Page Addressing Mode. */
#define SSD1306_SETLOWCOLUMN 0x00
/** Set Higher Column Start Address for Page Addressing Mode. */
#define SSD1306_SETHIGHCOLUMN 0x10
/** Set display RAM display start line register from 0 - 63. */
#define SSD1306_SETSTARTLINE 0x40
/**Set GDDRAM Page Start Address. */
#define SSD1306_SETSTARTPAGE 0XB0
/** Set Memory Addressing Mode. */
#define SSD1306_MEMORYMODE 0x20
/** Set COM output scan direction normal. */
#define SSD1306_COMSCANINC 0xC0
/** Set COM output scan direction reversed. */
#define SSD1306_COMSCANDEC 0xC8
/** Set Segment Re-map between data column and the segment driver. */ 
#define SSD1306_SEGREMAP 0xA0
/** Enable or disable charge pump.  Follow with 0X14 enable, 0X10 disable. */
#define SSD1306_CHARGEPUMP 0x8D
/**
 * @struct DevType
 * @brief Device initialization structure.
 */
struct DevType {
  /**
   * Pointer to initialization command bytes.
   */
  const uint8_t* initcmds; 
  /**
   * Number of initialization bytes.
   */
  const uint8_t  initSize;
  /**
   * Width of the diaplay in pixels.
   */
  const uint8_t  lcdWidth;
  /**
   * Height of the display in pixels.
   */
  const uint8_t  lcdHeight; 
};
//------------------------------------------------------------------------------
#ifndef __AVR__
/** Initialization commands for a 128x32 oled display. */
static const uint8_t Adafruit128x32init[] = {
#else  // __AVR__
static const uint8_t Adafruit128x32init[] PROGMEM = {
#endif  // __AVR
    // Init sequence for Adafruit 128x32 OLED module
    SSD1306_DISPLAYOFF,
    SSD1306_SETDISPLAYCLOCKDIV, 0x80,  // the suggested ratio 0x80
    SSD1306_SETMULTIPLEX, 0x1F,        // ratio 32
    SSD1306_SETDISPLAYOFFSET,0x0,      // no offset
    SSD1306_SETSTARTLINE | 0x0,        // line #0
    SSD1306_CHARGEPUMP, 0x14,          // internal vcc
    SSD1306_MEMORYMODE, 0x02,          // page mode
    SSD1306_SEGREMAP | 0x1,            // column 127 mapped to SEG0
    SSD1306_COMSCANDEC,                // column scan direction reversed
    SSD1306_SETCOMPINS, 0x02,          // sequential COM pins, disable remap
    SSD1306_SETCONTRAST, 0x7F,         // contrast level
    SSD1306_SETPRECHARGE, 0xF1,        // pre-charge period (1, 15)
    SSD1306_SETVCOMDETECT, 0x40,       // vcomh regulator level 
    SSD1306_DISPLAYALLON_RESUME,
    SSD1306_NORMALDISPLAY,
    SSD1306_DISPLAYON
};
#ifndef __AVR__
/** Initialize a 128x32 oled display. */
static const DevType Adafruit128x32 = {
#else  // __AVR__  
static const DevType Adafruit128x32 PROGMEM = {
#endif  // __AVR__  
  Adafruit128x32init, 
  sizeof(Adafruit128x32init),
  128,
  32
};
//------------------------------------------------------------------------------
#ifndef __AVR__
/** Initialization commands for a 128x64 oled display. */
static const uint8_t Adafruit128x64init[] = {
#else  // __AVR__
static const uint8_t Adafruit128x64init[] PROGMEM = {
#endif  // __AVR__
    // Init sequence for Adafruit 128x64 OLED module
    SSD1306_DISPLAYOFF,
    SSD1306_SETDISPLAYCLOCKDIV, 0x80,  // the suggested ratio 0x80
    SSD1306_SETMULTIPLEX, 0x3F,        // ratio 64
    SSD1306_SETDISPLAYOFFSET, 0x0,     // no offset
    SSD1306_SETSTARTLINE | 0x0,        // line #0
    SSD1306_CHARGEPUMP, 0x14,          // internal vcc
    SSD1306_MEMORYMODE, 0x02,          // page mode
    SSD1306_SEGREMAP | 0x1,            // column 127 mapped to SEG0
    SSD1306_COMSCANDEC,                // column scan direction reversed
    SSD1306_SETCOMPINS, 0x12,          // alt COM pins, disable remap
    SSD1306_SETCONTRAST, 0x7F,         // contrast level
    SSD1306_SETPRECHARGE, 0xF1,        // pre-charge period (1, 15)
    SSD1306_SETVCOMDETECT, 0x40,       // vcomh regulator level 
    SSD1306_DISPLAYALLON_RESUME,
    SSD1306_NORMALDISPLAY,
    SSD1306_DISPLAYON
};
#ifndef __AVR__
/** Initialize a 128x64 oled display. */
static const DevType Adafruit128x64 = {
#else  // __AVR__ 
static const DevType Adafruit128x64 PROGMEM = {
#endif  // __AVR__  
  Adafruit128x64init, 
  sizeof(Adafruit128x64init),
  128,
  64
};
#endif SSD1306init_h