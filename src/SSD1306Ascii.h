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
 * @file SSD1306Ascii.h
 * @brief Base class for ssd1306 displays.
 */
#ifndef SSD1306Ascii_h
#define SSD1306Ascii_h
#include "Arduino.h"
#include "SSD1306init.h"
#include "fonts/allFonts.h"
//------------------------------------------------------------------------------
/** SSD1306Ascii version */
#define SDD1306_ASCII_VERSION 1.2.2
//------------------------------------------------------------------------------
// Configuration options.
/** Set Scrolling mode for newline.
 *
 * If INCLUDE_SCROLLING is defined to be zero, newline will not scroll
 * the display and code for scrolling will not be included.  This option
 * will save some code space and three bytes of RAM.
 *
 * If INCLUDE_SCROLLING is nonzero, the scroll feature will included.
 */
#define INCLUDE_SCROLLING 1

/** Initial scroll mode, SCROLL_MODE_OFF,
    SCROLL_MODE_AUTO, or SCROLL_MODE_APP. */
#define INITIAL_SCROLL_MODE SCROLL_MODE_OFF

/** Use larger faster I2C code. */
#define OPTIMIZE_I2C 1

/** AvrI2c uses 400 kHz fast mode if AVRI2C_FASTMODE is nonzero else 100 kHz. */
#define AVRI2C_FASTMODE 1
//------------------------------------------------------------------------------
// Values for setScrolMode(uint8_t mode)
/** Newline will not scroll the display or RAM window. */
#define SCROLL_MODE_OFF  0
/** Newline will scroll both the display and RAM windows. */
#define SCROLL_MODE_AUTO 1
/** Newline scrolls the RAM window. The app scrolls the display window. */
#define SCROLL_MODE_APP  2
//------------------------------------------------------------------------------
// Values for writeDisplay() mode parameter.
/** Write to Command register. */
#define SSD1306_MODE_CMD     0
/** Write one byte to display RAM. */
#define SSD1306_MODE_RAM     1
/** Write to display RAM with possible buffering. */
#define SSD1306_MODE_RAM_BUF 2
//-----------------------------------------------------------------------------
/**
 * @brief Reset the display controller.
 *
 * @param[in] rst Reset pin number.
 */
inline void oledReset(uint8_t rst) {
  pinMode(rst, OUTPUT);
  digitalWrite(rst, LOW);
  delay(10);
  digitalWrite(rst, HIGH);
  delay(10);
}
//------------------------------------------------------------------------------
/**
 * @class SSD1306Ascii
 * @brief SSD1306 base class
 */
class SSD1306Ascii : public Print {
 public:
  using Print::write;
  SSD1306Ascii() {}
#if INCLUDE_SCROLLING
//------------------------------------------------------------------------------
  /**
   * @return the RAM page for top of the RAM window.
   */
  uint8_t pageOffset() const {return m_pageOffset;}
  /**
   * @return the display line for pageOffset.
   */
  uint8_t pageOffsetLine() const {return 8*m_pageOffset;}
  /**
   * @brief Scroll the Display window.
   *
   * @param[in] lines Number of lines to scroll the window.
   */
  void scrollDisplay(int8_t lines) {setStartLine(m_startLine + lines);}
  /**
   * @brief Scroll the RAM window.
   *
   * @param[in] rows Number of rows to scroll the window.
   */
  void scrollMemory(int8_t rows) {setPageOffset(m_pageOffset + rows);}
  /**
   * @return true if the first display line is equal to the
   *         start of the RAM window.
   */
  bool scrollIsSynced() const {return startLine() == pageOffsetLine();}
  /**
   * @brief Set page offset.
   *
   * @param[in] page the RAM page for start of the RAM window
   */
  void setPageOffset(uint8_t page);
  /**
   * @brief Enable or disable scroll mode. Deprecated use setScrollMode().
   *
   * @param[in] enable true enable scroll on newline false disable scroll.
   */
  void setScroll(bool enable) __attribute__((deprecated("use setScrollMode"))) {
    setScrollMode(enable ? SCROLL_MODE_AUTO : SCROLL_MODE_OFF);
  }
  /**
   * @brief Set scroll mode.
   *
   * @param[in] mode One of the following.
   *
   * SCROLL_MODE_OFF - newline will not scroll the display or RAM window.
   *
   * SCROLL_MODE_AUTO - newline will scroll both the display and RAM windows.
   *
   * SCROLL_MODE_APP - newline scrolls the RAM window.
   *                   The app scrolls the display window.
   */
  void setScrollMode(uint8_t mode) {m_scrollMode = mode;}
  /**
   * @brief Set the display start line register.
   *
   * @param[in] line RAM line to be mapped to first display line.
   */
  void setStartLine(uint8_t line);
  /**
   * @return the display startline.
   */
  uint8_t startLine() const {return m_startLine;}
#endif  // INCLUDE_SCROLLING
  //----------------------------------------------------------------------------
  /**
   * @brief Determine the width of a character.
   *
   * @param[in] c Character code.
   * @return Width of the character in pixels.
   */
  uint8_t charWidth(uint8_t c) const;
  /**
   * @brief Clear the display and set the cursor to (0, 0).
   */
  void clear();
  /**
   * @brief Clear a region of the display.
   *
   * @param[in] c0 Starting column.
   * @param[in] c1 Ending column.
   * @param[in] r0 Starting row;
   * @param[in] r1 Ending row;
   * @note The final cursor position will be (c0, r0).
   */
  void clear(uint8_t c0, uint8_t c1, uint8_t r0, uint8_t r1);
  /**
   * @brief Clear a field of n fieldWidth() characters.
   *
   * @param[in] col Field start column.
   *
   * @param[in] row Field start row.
   *
   * @param[in] n Number of characters in the field.
   *
   */
  void clearField(uint8_t col, uint8_t row, uint8_t n);
  /**
   * @brief Clear the display to the end of the current line.
   * @note The number of rows cleared will be determined by the height
   *       of the current font.
   * @note The cursor will be returned to the original position.
   */
  void clearToEOL();
  /**
   * @return The current column in pixels.
   */
  uint8_t col() const {return m_col;}
  /**
   * @return The display hight in pixels.
   */
  uint8_t displayHeight() const {return m_displayHeight;}
  /**
   * @brief Set display to normal or 180 degree remap mode.
   *
   * @param[in] mode true for normal mode, false for remap mode.
   *
   * @note Adafruit and many ebay displays use remap mode.
   *       Use normal mode to rotate these displays 180 degrees.
   */
  void displayRemap(bool mode);
  /**
   * @return The display height in rows with eight pixels to a row.
   */
  uint8_t displayRows() const {return m_displayHeight/8;}
  /**
   * @return The display width in pixels.
   */
  uint8_t displayWidth() const {return m_displayWidth;}
  /**
   * @brief Width of a field in pixels.
   *
   * @param[in] n Number of characters in the field.
   *
   * @return Width of the field.
   */
  size_t fieldWidth(uint8_t n);
  /**
   * @return The current font pointer.
   */
  const uint8_t* font() const {return m_font;}
  /**
   * @return The count of characters in a font.
   */
  uint8_t fontCharCount() const;
  /**
   * @return The first character in a font.
   */
  char fontFirstChar() const;
  /**
   * @return The current font height in pixels.
   */
  uint8_t fontHeight() const;
  /**
   * @return The number of eight pixel rows required to display a character
   *    in the current font.
   */
  uint8_t fontRows() const;
  /**
   * @return The maximum width of characters in the current font.
   */
  uint8_t fontWidth() const;
  /**
   * @brief Set the cursor position to (0, 0).
   */
  void home() {setCursor(0, 0);}
  /**
   * @brief Initialize the display controller.
   *
   * @param[in] dev A display initialization structure.
   */
  void init(const DevType* dev);
  /**
   * @brief Set pixel mode for for entire display.
   *
   * @param[in] invert Inverted display if true or normal display if false.
   */
  void invertDisplay(bool invert);
  /**
   * @return invert mode.
   */
  bool invertMode() const {return !!m_invertMask;}
  /**
   * @brief Set invert mode for write/print.
   *
   * @param[in] mode Invert pixels if true and use normal mode if false.
   */
  void setInvertMode(bool mode) {m_invertMask = mode ? 0XFF : 0;}
  /**
   * @return letter-spacing in pixels with magnification factor.
   */
  uint8_t letterSpacing() const {return m_magFactor*m_letterSpacing;}
  /**
   * @return The character magnification factor.
   */
  uint8_t magFactor() const {return m_magFactor;}
  /**
   * @return the current row number with eight pixels to a row.
   */
  uint8_t row() const {return m_row;}
  /**
   * @brief Set the character magnification factor to one.
   */
  void set1X() {m_magFactor = 1;}
  /**
   * @brief Set the character magnification factor to two.
   */
  void set2X() {m_magFactor = 2;}
  /**
   * @brief Set the current column number.
   *
   * @param[in] col The desired column number in pixels.
   */
  void setCol(uint8_t col);
  /**
   * @brief Set the display contrast.
   *
   * @param[in] value The contrast level in th range 0 to 255.
   */
  void setContrast(uint8_t value);
  /**
   * @brief Set the cursor position.
   *
   * @param[in] col The column number in pixels.
   * @param[in] row the row number in eight pixel rows.
   */
  void setCursor(uint8_t col, uint8_t row);
  /**
   * @brief Set the current font.
   *
   * @param[in] font Pointer to a font table.
   */
  void setFont(const uint8_t* font);
  /**
   * @brief Set letter-spacing.  setFont() will restore default letter-spacing.
   *
   * @param[in] pixels letter-spacing in pixels before magnification.
   */
  void setLetterSpacing(uint8_t pixels) {m_letterSpacing = pixels;}
  /**
   * @brief Set the current row number.
   *
   * @param[in] row the row number in eight pixel rows.
   */
  void setRow(uint8_t row);
  /**
   * @brief Write a command byte to the display controller.
   *
   * @param[in] c The command byte.
   * @note The byte will immediately be sent to the controller.
   */
  void ssd1306WriteCmd(uint8_t c) {writeDisplay(c, SSD1306_MODE_CMD);}
  /**
   * @brief Write a byte to RAM in the display controller.
   *
   * @param[in] c The data byte.
   * @note The byte will immediately be sent to the controller.
   */
  void ssd1306WriteRam(uint8_t c);
  /**
   * @brief Write a byte to RAM in the display controller.
   *
   * @param[in] c The data byte.
   * @note The byte may be buffered until a call to ssd1306WriteCmd
   *       or ssd1306WriteRam.
   */
  void ssd1306WriteRamBuf(uint8_t c);
  /**
   * @param[in] str The pointer to string.
   * @return the width of the string in pixels.
   */
  size_t strWidth(const char* str) const;
  /**
   * @brief Display a character.
   *
   * @param[in] c The character to display.
   * @return the value one.
   */
  size_t write(uint8_t c);

 protected:
  uint16_t fontSize() const;
  virtual void writeDisplay(uint8_t b, uint8_t mode) = 0;
  uint8_t m_col;            // Cursor column.
  uint8_t m_row;            // Cursor RAM row.
  uint8_t m_displayWidth;   // Display width.
  uint8_t m_displayHeight;  // Display height.
  uint8_t m_colOffset;      // Column offset RAM to SEG.
  uint8_t m_letterSpacing;  // Letter-spacing in pixels.
#if INCLUDE_SCROLLING
  uint8_t m_startLine;      // Top line of display
  uint8_t m_pageOffset;     // Top page of RAM window.
  uint8_t m_scrollMode = INITIAL_SCROLL_MODE;  // Scroll mode for newline.
#endif  // INCLUDE_SCROLLING
  const uint8_t* m_font = nullptr;  // Current font.
  uint8_t m_invertMask = 0;  // font invert mask
  uint8_t m_magFactor = 1;   // Magnification factor.
};
#endif  // SSD1306Ascii_h
