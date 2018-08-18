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
#include "SSD1306Ascii.h"
//------------------------------------------------------------------------------
uint8_t SSD1306Ascii::charWidth(uint8_t c) {
  if (!m_font) {
    return 0;
  }
  uint8_t first = readFontByte(m_font + FONT_FIRST_CHAR);
  uint8_t count = readFontByte(m_font + FONT_CHAR_COUNT);
  if (c < first || c >= (first + count)) {
    return 0;
  }
  if (fontSize() > 1) {
    // Proportional font.
    return m_magFactor*readFontByte(m_font + FONT_WIDTH_TABLE + c - first);
  }
  // Fixed width font.
  return m_magFactor*readFontByte(m_font + FONT_WIDTH);
}
//------------------------------------------------------------------------------
void SSD1306Ascii::clear() {
  clear(0, displayWidth() - 1, 0 , displayRows() - 1);
  #if INCLUDE_SCROLLING
  m_scroll = m_scroll ? 1 : 0;
  m_top = 0;
  ssd1306WriteCmd(SSD1306_SETSTARTLINE | 0);
  #endif  //INCLUDE_SCROLLING
}
//------------------------------------------------------------------------------
void SSD1306Ascii::clear(uint8_t c0, uint8_t c1, uint8_t r0, uint8_t r1) {
  if (r1 >= displayRows()) r1 = displayRows() - 1;
  for (uint8_t r = r0; r <= r1; r++) {
    setCursor(c0, r);
    for (uint8_t c = c0; c <= c1; c++) {
      ssd1306WriteRamBuf(0);
    }
  }
  setCursor(c0, r0);
}
//------------------------------------------------------------------------------
void SSD1306Ascii::clearToEOL() {
  clear (m_col, displayWidth() - 1, m_row, m_row + fontRows() - 1);
}
//------------------------------------------------------------------------------
void SSD1306Ascii::clearField(uint8_t col, uint8_t row, uint8_t n) {
  clear(col, col + fieldWidth(n) - 1, row, row + fontRows() - 1);
}
//------------------------------------------------------------------------------
void SSD1306Ascii::displayRemap(bool mode) {
  ssd1306WriteCmd(mode ? SSD1306_SEGREMAP : SSD1306_SEGREMAP | 1);
  ssd1306WriteCmd(mode ? SSD1306_COMSCANINC : SSD1306_COMSCANDEC);
}
//------------------------------------------------------------------------------
size_t SSD1306Ascii::fieldWidth(uint8_t n) {
  return n*(fontWidth() + letterSpacing());
}
//------------------------------------------------------------------------------
uint8_t SSD1306Ascii::fontCharCount() {
  return m_font ? readFontByte(m_font + FONT_CHAR_COUNT) : 0;  
}
//------------------------------------------------------------------------------
char SSD1306Ascii::fontFirstChar() {
  return m_font ? readFontByte(m_font + FONT_FIRST_CHAR) : 0;    
}
//------------------------------------------------------------------------------
uint8_t SSD1306Ascii::fontHeight() {
  return m_font ? m_magFactor*readFontByte(m_font + FONT_HEIGHT) : 0;
}
//------------------------------------------------------------------------------
uint16_t SSD1306Ascii::fontSize() {
  return (readFontByte(m_font) << 8) | readFontByte(m_font + 1);
}
//------------------------------------------------------------------------------
uint8_t SSD1306Ascii::fontWidth() {
  return m_font ? m_magFactor*readFontByte(m_font + FONT_WIDTH) : 0;
}
//------------------------------------------------------------------------------
void SSD1306Ascii::init(const DevType* dev) {
  m_col = 0;
  m_row = 0;
  #ifdef __AVR__
  const uint8_t* table = (const uint8_t*)pgm_read_word(&dev->initcmds);
  #else  // __AVR__
  const uint8_t* table = dev->initcmds;
  #endif  // __AVR
  uint8_t size = readFontByte(&dev->initSize);
  m_displayWidth = readFontByte(&dev->lcdWidth);
  m_displayHeight = readFontByte(&dev->lcdHeight);
  m_colOffset = readFontByte(&dev->colOffset);
  for (uint8_t i = 0; i < size; i++) {
    ssd1306WriteCmd(readFontByte(table + i));
  }
  #if INCLUDE_SCROLLING
  m_scroll = INCLUDE_SCROLLING < 2 ? 0 : 1;
  m_top = 0;
  #endif  //INCLUDE_SCROLLING
  clear();
}
//------------------------------------------------------------------------------
void SSD1306Ascii::setCol(uint8_t col) {
  if (col >= m_displayWidth) return;
  m_col = col;
  col += m_colOffset;
  ssd1306WriteCmd(SSD1306_SETLOWCOLUMN | (col & 0XF));
  ssd1306WriteCmd(SSD1306_SETHIGHCOLUMN | (col >> 4));
}
//------------------------------------------------------------------------------
void SSD1306Ascii::setContrast(uint8_t value) {
  ssd1306WriteCmd(SSD1306_SETCONTRAST);
  ssd1306WriteCmd(value);
}
//------------------------------------------------------------------------------
void SSD1306Ascii::setCursor(uint8_t col, uint8_t row) {
  setCol(col);
  setRow(row);
}
//------------------------------------------------------------------------------
void SSD1306Ascii::setFont(const uint8_t* font) {
  m_font = font;
  if (font && fontSize() == 1) {
     m_letterSpacing = 0;
  } else {
    m_letterSpacing = 1;
  }
}
//------------------------------------------------------------------------------
void SSD1306Ascii::setRow(uint8_t row) {
#if INCLUDE_SCROLLING_SMOOTH
Serial.printf("row=%d - ", row);
  if (row > (m_displayHeight / 8) - m_magFactor)
      row = (m_displayHeight / 8) - m_magFactor;
Serial.printf("%d\n", row);
#else // !INCLUDE_SCROLLING_SMOOTH
  if (row >= m_displayHeight/8) return;
#endif // !INCLUDE_SCROLLING_SMOOTH
  m_row = row;
#if INCLUDE_SCROLLING
  //ssd1306WriteCmd(SSD1306_SETSTARTPAGE | (m_row + m_top));
  ssd1306WriteCmd(SSD1306_SETSTARTPAGE | ((m_row + m_top) % 8));
#else
  ssd1306WriteCmd(SSD1306_SETSTARTPAGE | m_row);
#endif
}
//------------------------------------------------------------------------------
#if INCLUDE_SCROLLING
void SSD1306Ascii::setScroll(bool enable) {
  clear();
  m_scroll = enable ? 1 : 0;
}
#endif   // INCLUDE_SCROLLING
//-----------------------------------------------------------------------------
void SSD1306Ascii::ssd1306WriteRam(uint8_t c) {
  if (m_col >= m_displayWidth) return;
  writeDisplay(c, SSD1306_MODE_RAM);
  m_col++;
}
//-----------------------------------------------------------------------------
void SSD1306Ascii::ssd1306WriteRamBuf(uint8_t c) {
  if (m_col >= m_displayWidth) return;
  writeDisplay(c, SSD1306_MODE_RAM_BUF);
  m_col++;
}
//------------------------------------------------------------------------------
GLCDFONTDECL(scaledNibble) = {
  0X00, 0X03, 0X0C, 0X0F,
  0X30, 0X33, 0X3C, 0X3F,
  0XC0, 0XC3, 0XCC, 0XCF,
  0XF0, 0XF3, 0XFC, 0XFF
};
//------------------------------------------------------------------------------
size_t SSD1306Ascii::strWidth(const char* str) {
  size_t sw = 0;
  while (*str) {
    uint8_t cw = charWidth(*str++);
    if (cw == 0) {
      return 0;
    }
    sw += cw + letterSpacing();
  }
  return sw;
}
//------------------------------------------------------------------------------
#if INCLUDE_SCROLLING
void SSD1306Ascii::down(int8_t n)
{
  m_top = (m_top + n * m_magFactor + 8) % 8; // 8 rows in any case
}
#endif
//------------------------------------------------------------------------------
#if INCLUDE_SCROLLING_SMOOTH
bool SSD1306Ascii::process ()
{
    // need to check everytime whether text (m_top) is updating too fast

    // 64 lines in ram in any case
    uint8_t top8 = (m_top * 8) % 64;

    // compare is near 64 when scrolling down,
    // and near 0 with scrolling up
    // 0 when no scrolling
    uint8_t compare = (m_top_smooth + 64 - top8) % 64;

    if (compare == 0)
    {
        // stay still
        m_too_fast = false;
        return true;
    }

    if (compare >= 8 && compare <= (64-8))
        // tell user to slow down prints otherwise
        // scroll will slide the other way (will however
        // stay correct when top is reached)
        m_too_fast = true;

    uint16_t now = (uint16_t)millis();
    if ((uint16_t)(now - m_millis_last_smooth) > SMOOTH_SCROLL_MS)
    {
        // time to scroll by one line
        m_millis_last_smooth = now;

        // increase or decrease scrolling by one pixel line
        m_top_smooth = (m_top_smooth + ((compare > 32)? 65: 63)) % 64;
        ssd1306WriteCmd(SSD1306_SETSTARTLINE | m_top_smooth);
    }

    return !m_too_fast;
}
#endif // INCLUDE_SCROLLING_SMOOTH
//------------------------------------------------------------------------------
size_t SSD1306Ascii::write(uint8_t ch) {
  if (!m_font) {
    return 0;
  }
  uint8_t w = readFontByte(m_font + FONT_WIDTH);
  uint8_t h = readFontByte(m_font + FONT_HEIGHT);
  uint8_t nr = (h + 7)/8;
  uint8_t first = readFontByte(m_font + FONT_FIRST_CHAR);
  uint8_t count = readFontByte(m_font + FONT_CHAR_COUNT);
  const uint8_t* base = m_font + FONT_WIDTH_TABLE;

  if (ch < first || ch >= (first + count)) {
    if (ch == '\r') {
      setCol(0);
      return 1;
    }
    if (ch == '\n') {
      #if INCLUDE_SCROLLING == 0
      setCursor(0, m_row + m_magFactor*nr);
      #else  // INCLUDE_SCROLLING

      if (m_row == (m_displayHeight/8) - 1) {
        // scroll mode: change screen offset
        down(m_magFactor*nr); // m_top changes
        setCursor(0, m_row); // m_row does not change, but STARTPAGE does
        #if !INCLUDE_SCROLLING_SMOOTH
        // brutal scroll:
        ssd1306WriteCmd(SSD1306_SETSTARTLINE | (m_top * 8));
        #endif // !INCLUDE_SCROLLING_SMOOTH
      }
      else
        setCursor(0, m_row + m_magFactor*nr);
      clearToEOL();

      #endif  // INCLUDE_SCROLLING
      return 1;
    }
    return 0;
  }
  ch -= first;
  uint8_t s = letterSpacing();
  uint8_t thieleShift = 0;
  if (fontSize() < 2) {
    // Fixed width font.
    base += nr*w*ch;
  } else {
    if (h & 7) {
      thieleShift = 8 - (h & 7);
    }
    uint16_t index = 0;
    for (uint8_t i = 0; i < ch; i++) {
      index += readFontByte(base + i);
    }
    w = readFontByte(base + ch);
    base += nr*index + count;
  }
  uint8_t scol = m_col;
  uint8_t srow = m_row;
  for (uint8_t r = 0; r < nr; r++) {
    for (uint8_t m = 0; m < m_magFactor; m++) {
      if (r || m) setCursor(scol, m_row + 1);
      for (uint8_t c = 0; c < w; c++) {
        uint8_t b = readFontByte(base + c + r*w);
        if (thieleShift && (r + 1) == nr) {
          b >>= thieleShift;
        }
        if (m_magFactor == 2) {
           b = m ?  b >> 4 : b & 0XF;
           b = readFontByte(scaledNibble + b);
           ssd1306WriteRamBuf(b);
        }
        ssd1306WriteRamBuf(b);
      }
      for (uint8_t i = 0; i < s; i++) {
        ssd1306WriteRamBuf(0);
      }
    }
  }
  setRow(srow);
  return 1;
}
//------------------------------------------------------------------------------
size_t SSD1306Ascii::write(const char* s) {
  size_t n = strlen(s);
  for (size_t i = 0; i < n; i++) {
    write(s[i]);
  }
  return n;
}
