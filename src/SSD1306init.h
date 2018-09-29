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
#ifndef __AVR__
/** Handle AVR flash addressing. */
#define MEM_TYPE
#else  // __AVR__
#define MEM_TYPE __attribute__ ((progmem))
#endif  // __AVR__
//------------------------------------------------------------------------------
/** Set Lower Column Start Address for Page Addressing Mode. */
#define SSD1306_SETLOWCOLUMN 0x00
/** Set Higher Column Start Address for Page Addressing Mode. */
#define SSD1306_SETHIGHCOLUMN 0x10
/** Set Memory Addressing Mode. */
#define SSD1306_MEMORYMODE 0x20
/** Set display RAM display start line register from 0 - 63. */
#define SSD1306_SETSTARTLINE 0x40
/** Set Display Contrast to one of 256 steps. */
#define SSD1306_SETCONTRAST 0x81
/** Enable or disable charge pump.  Follow with 0X14 enable, 0X10 disable. */
#define SSD1306_CHARGEPUMP 0x8D
/** Set Segment Re-map between data column and the segment driver. */
#define SSD1306_SEGREMAP 0xA0
/** Resume display from GRAM content. */
#define SSD1306_DISPLAYALLON_RESUME 0xA4
/** Force display on regardless of GRAM content. */
#define SSD1306_DISPLAYALLON 0xA5
/** Set Normal Display. */
#define SSD1306_NORMALDISPLAY 0xA6
/** Set Inverse Display. */
#define SSD1306_INVERTDISPLAY 0xA7
/** Set Multiplex Ratio from 16 to 63. */
#define SSD1306_SETMULTIPLEX 0xA8
/** Set Display off. */
#define SSD1306_DISPLAYOFF 0xAE
/** Set Display on. */
#define SSD1306_DISPLAYON 0xAF
/**Set GDDRAM Page Start Address. */
#define SSD1306_SETSTARTPAGE 0XB0
/** Set COM output scan direction normal. */
#define SSD1306_COMSCANINC 0xC0
/** Set COM output scan direction reversed. */
#define SSD1306_COMSCANDEC 0xC8
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
/** Deactivate scroll */
#define SSD1306_DEACTIVATE_SCROLL 0x2E
/** No Operation Command. */
#define SSD1306_NOP 0XE3
//------------------------------------------------------------------------------
/** Set Pump voltage value: (30H~33H) 6.4, 7.4, 8.0 (POR), 9.0. */
#define SH1106_SET_PUMP_VOLTAGE 0X30
/** First byte of set charge pump mode */
#define SH1106_SET_PUMP_MODE 0XAD
/** Second byte charge pump on. */
#define SH1106_PUMP_ON 0X8B
/** Second byte charge pump off. */
#define SH1106_PUMP_OFF 0X8A
//------------------------------------------------------------------------------
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
  const uint8_t initSize;
  /**
   * Width of the diaplay in pixels.
   */
  const uint8_t lcdWidth;
  /**
   * Height of the display in pixels.
   */
  const uint8_t lcdHeight;
  /**
   * Column offset RAM to display.  Used to pick start column of SH1106.
   */
  const uint8_t colOffset;
};
//------------------------------------------------------------------------------
/** Initialization commands for a 64x48 Micro OLED display (by r7) */
static const uint8_t MEM_TYPE MicroOLED64x48init[] = {
    // Init sequence for 64x48 Micro OLED module
    SSD1306_DISPLAYOFF,
    SSD1306_SETDISPLAYCLOCKDIV, 0x80,  // the suggested ratio 0x80
    SSD1306_SETMULTIPLEX, 0x2F,        //
    SSD1306_SETDISPLAYOFFSET, 0x0,     // no offset
    SSD1306_SETSTARTLINE | 0x0,        // line #0
    SSD1306_CHARGEPUMP, 0x14,          // internal vcc
    SSD1306_NORMALDISPLAY,
    SSD1306_DISPLAYALLON_RESUME,
    SSD1306_SEGREMAP | 0x1,            // column 127 mapped to SEG0
    SSD1306_COMSCANDEC,                // column scan direction reversed
    SSD1306_SETCOMPINS, 0x12,          // 0x12 if height > 32 else 0x02
    SSD1306_SETCONTRAST, 0x7F,         // contrast level 127
    SSD1306_SETPRECHARGE, 0xF1,        // pre-charge period (1, 15)
    SSD1306_SETVCOMDETECT, 0x40,       // vcomh regulator level
    SSD1306_DISPLAYON
};
/** Initialize a 64x48 Micro OLED display. */
static const DevType MEM_TYPE MicroOLED64x48 = {
  MicroOLED64x48init,
  sizeof(MicroOLED64x48init),
  64,
  48,
  32
};
//------------------------------------------------------------------------------
// this section is based on
// https://github.com/olikraus/u8g2/blob/master/csrc/u8x8_d_ssd1306_96x16.c
/** Initialization commands for a 96x16 SSD1306 oled display. */
static const uint8_t MEM_TYPE SSD1306_96x16init[] = {
    // Init sequence for Generic 96x16 OLED module
    SSD1306_DISPLAYOFF,
    SSD1306_SETDISPLAYCLOCKDIV, 0x80, // clock divide ratio and osc frequency
    SSD1306_SETMULTIPLEX, 0x0F,       // multiplex ratio
    SSD1306_SETDISPLAYOFFSET, 0x0,    // display offset zero
    SSD1306_SETSTARTLINE | 0x0,       // set display start line to 0
    SSD1306_CHARGEPUMP, 0x14,         // charge pump setting enable
    SSD1306_MEMORYMODE, 0x00,         // page addressing mode
    SSD1306_SEGREMAP | 0xA1,          // segment remap
    SSD1306_COMSCANDEC,               // scan dir reverse
    SSD1306_SETCOMPINS, 0x02,         // com pin HW config
    SSD1306_SETCONTRAST, 0xAF,        // set contrast level 0xaf
    SSD1306_SETPRECHARGE, 0xF1,       // pre-charge period 0x0f1
    SSD1306_SETVCOMDETECT, 0x20,      // vcomh deselect level
    SSD1306_DEACTIVATE_SCROLL,        //  Deactivate scroll
    SSD1306_DISPLAYALLON_RESUME,
    SSD1306_NORMALDISPLAY,
    SSD1306_DISPLAYON
};
/* Initialize a 96x16 SSD1306 oled display. */
static const DevType MEM_TYPE SSD1306_96x16 = {
  SSD1306_96x16init,
  sizeof(SSD1306_96x16init),
  96,
  16,
  0
};
//------------------------------------------------------------------------------
// this section is based on https://github.com/adafruit/Adafruit_SSD1306
/** Initialization commands for a 128x32 SSD1306 oled display. */
static const uint8_t MEM_TYPE Adafruit128x32init[] = {
    // Init sequence for Adafruit 128x32 OLED module
    SSD1306_DISPLAYOFF,
    SSD1306_SETDISPLAYCLOCKDIV, 0x80,  // the suggested ratio 0x80
    SSD1306_SETMULTIPLEX, 0x1F,        // ratio 32
    SSD1306_SETDISPLAYOFFSET, 0x0,     // no offset
    SSD1306_SETSTARTLINE | 0x0,        // line #0
    SSD1306_CHARGEPUMP, 0x14,          // internal vcc
    SSD1306_MEMORYMODE, 0x02,          // page mode
    SSD1306_SEGREMAP | 0x1,            // column 127 mapped to SEG0
    SSD1306_COMSCANDEC,                // column scan direction reversed
    SSD1306_SETCOMPINS, 0x02,          // sequential COM pins, disable remap
    SSD1306_SETCONTRAST, 0x7F,         // contrast level 127
    SSD1306_SETPRECHARGE, 0xF1,        // pre-charge period (1, 15)
    SSD1306_SETVCOMDETECT, 0x40,       // vcomh regulator level
    SSD1306_DISPLAYALLON_RESUME,
    SSD1306_NORMALDISPLAY,
    SSD1306_DISPLAYON
};
/** Initialize a 128x32 SSD1306 oled display. */
static const DevType MEM_TYPE Adafruit128x32 = {
  Adafruit128x32init,
  sizeof(Adafruit128x32init),
  128,
  32,
  0
};
//------------------------------------------------------------------------------
// This section is based on https://github.com/adafruit/Adafruit_SSD1306
/** Initialization commands for a 128x64 SSD1306 oled display. */
static const uint8_t MEM_TYPE Adafruit128x64init[] = {
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
    SSD1306_SETCONTRAST, 0x7F,         // contrast level 127
    SSD1306_SETPRECHARGE, 0xF1,        // pre-charge period (1, 15)
    SSD1306_SETVCOMDETECT, 0x40,       // vcomh regulator level
    SSD1306_DISPLAYALLON_RESUME,
    SSD1306_NORMALDISPLAY,
    SSD1306_DISPLAYON
};
/** Initialize a 128x64 oled display. */
static const DevType MEM_TYPE Adafruit128x64 = {
  Adafruit128x64init,
  sizeof(Adafruit128x64init),
  128,
  64,
  0
};
//------------------------------------------------------------------------------
// This section is based on https://github.com/stanleyhuangyc/MultiLCD
/** Initialization commands for a 128x64 SH1106 oled display. */
static const uint8_t MEM_TYPE SH1106_128x64init[] = {
  SSD1306_DISPLAYOFF,
  SSD1306_SETSTARTPAGE | 0X0,            // set page address
  SSD1306_SETCONTRAST, 0x80,             // 128
  SSD1306_SEGREMAP | 0X1,                // set segment remap
  SSD1306_NORMALDISPLAY,                 // normal / reverse
  SSD1306_SETMULTIPLEX, 0x3F,            // ratio 64
  SH1106_SET_PUMP_MODE, SH1106_PUMP_ON,  // set charge pump enable
  SH1106_SET_PUMP_VOLTAGE | 0X2,         // 8.0 volts
  SSD1306_COMSCANDEC,                    // Com scan direction
  SSD1306_SETDISPLAYOFFSET, 0X00,        // set display offset
  SSD1306_SETDISPLAYCLOCKDIV, 0X80,      // set osc division
  SSD1306_SETPRECHARGE, 0X1F,            // set pre-charge period
  SSD1306_SETCOMPINS, 0X12,              // set COM pins
  SSD1306_SETVCOMDETECT,  0x40,          // set vcomh
  SSD1306_DISPLAYON
};
/** Initialize a 128x64 oled SH1106 display. */
static const DevType MEM_TYPE SH1106_128x64 =  {
  SH1106_128x64init,
  sizeof(SH1106_128x64init),
  128,
  64,
  2    // SH1106 is a 132x64 controller.  Use middle 128 columns.
};
#endif  // SSD1306init_h
