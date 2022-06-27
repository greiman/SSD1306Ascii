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
@mainpage Arduino %SSD1306Ascii Library
<CENTER>Copyright &copy; 2015-2022 by William Greiman
</CENTER>

@section Intro Introduction

The Arduino %SSD1306Ascii Library is designed to display text on small
monochrome OLED displays.  These displays are available on ebay at
very low cost.

The library is being developed using 0.96" and 1.3" displays with SSD1306
controllers.  An initialization sequence for SH1106 controllers is included.

There are many existing full featured graphics libraries for these displays.
The goal for this library is to only display text with minimum use of
RAM and flash.

Here are key design goals:

Small size is the highest priority.  Speed and features are lower priority.

Support multiple fonts.  More than 40 fonts are included with this release.
Fonts are only loaded if you reference them.

Support fixed width and proportional fonts.

Optionally magnify fonts by a factor of two.

Support 128x32 and 128x64 displays with I2C and SPI interfaces.

Use the standard Wire library for I2C.  An optimization option is
available to increase I2C performance.

Use the standard SPI library for hardware SPI.

Provide software SPI so the display can be connected to any digital pins.

A small AVR only I2C driver is available when no other I2C devices are used. 
 
@section Install Installation

SSD1306Ascii can be installed using the library manager.  Newer untagged
versions may be available on GitHub. 

You can manually install the %SSD1306Ascii library by copying the 
%SSD1306Ascii folder from the download package to the Arduino libraries
folder in your sketch folder.

See the Manual installation section of this guide.

http://arduino.cc/en/Guide/Libraries

The library will be added to the Arduino Library Manager soon.

@section Scroll Scroll Mode

Scroll mode causes the display to scroll up when a new line is written to
the display.

Scroll mode is configured by editing SSD1306Ascii.h.

If #INCLUDE_SCROLLING is defined to be zero, new line will not scroll
the display and code for scrolling will not be included.  This option 
will save some code space and several bytes of RAM.

If #INCLUDE_SCROLLING is non-zero, the scroll feature will
be included.

Call SSD1306Ascii::setScrollMode() to change the scrolling mode.
  
The initial scroll mode is define by #INITIAL_SCROLL_MODE in SSD1306Ascii.h

Scroll mode One of the following.

#SCROLL_MODE_OFF - newline will not scroll the display or RAM window.

#SCROLL_MODE_AUTO - newline will scroll both the display and RAM windows.

#SCROLL_MODE_APP - newline scrolls the RAM window. 
The app scrolls the display window.

The SSD1306Ascii::clear() call will erase the display and start at the
top of the display.

See the ScrollSpi and ScrollWire examples.

More advanced scrolling can be implemented using member functions such as
SSD1306Ascii::scrollDisplay(), SSD1306Ascii::scrollMemory(), 
and SSD1306Ascii::scrollIsSynced(). 

Knowledge of the SSD1306 is useful for understanding advanced scrolling. 
See the SSD1306 data sheet.   
  
@section Fonts Fonts

Fonts are defined by .h files in the SSD1306Ascii/src/fonts folder.  The fonts 
folder contains all fonts from openGLCD plus a number of extra fonts.

To select a font, call the SSD1306Ascii::setFont() member function like this.
@code
  // Select the font used in the Adafruit GFX Graphics Library.
  oled.setFont(Adafruit5x7); 
@endcode
Only fonts referenced in your program will be loaded into flash.

Here are symbols for fixed width fonts.
@verbatim
Adafruit5x7
cp437font8x8
fixed_bold10x15
fixednums15x31
fixednums7x15
fixednums8x16
font5x7
font8x8
lcd5x7
lcdnums12x16
lcdnums14x24
newbasic3x5
Stang5x7
System5x7
Wendy3x5
X11fixed7x14
X11fixed7x14B
ZevvPeep8x16  
@endverbatim

Here are symbols for proportional fonts.  Note that Iain5x7 and utf8font10x16
are proportional.
@verbatim
Arial14
Arial_bold_14
CalBlk36
CalLite24
Callibri10
Callibri11
Callibri11_bold
Callibri11_italic
Callibri14
Callibri15
Cooper19
Cooper21
Cooper26
Corsiva_12
Iain5x7
Roosewood22
Roosewood26
TimesNewRoman13
TimesNewRoman13_italic
TimesNewRoman16
TimesNewRoman16_bold
TimesNewRoman16_italic
utf8font10x16
Verdana12
Verdana12_bold
Verdana12_italic
Verdana_digits_24
@endverbatim

See allFonts.h for more information on adding a font.

The SSD1306Ascii::set2X() call doubles the size of characters.  Each pixel
becomes a 2x2 square.  To return to standard size characters call 
SSD1306Ascii::set1X();
@code
  oled.set2X();
  // Display double height and width characters.
  
  ...
  
  // Return to standard size.
  oled.set1X();
@endcode


@section config SSD1306Ascii Configuration

Several configuration options may be changed by editing the SSD1306Ascii.h
file in the SSD1306Ascii/src folder.

These options are at the start of the file.

@code
// Configuration options.
/* Set Scrolling mode for new line.
 *
 * If INCLUDE_SCROLLING is defined to be zero, new line will not scroll
 * the display and code for scrolling will not be included.  This option
 * will save some code space and three bytes of RAM.
 *
 * If INCLUDE_SCROLLING is nonzero, the scroll feature will included.
 */
#define INCLUDE_SCROLLING 1

/* Initial scroll mode, SCROLL_MODE_OFF, SCROLL_MODE_AUTO, or SCROLL_MODE_APP.*/
#define INITIAL_SCROLL_MODE SCROLL_MODE_OFF

/* Use larger faster I2C code. */
#define OPTIMIZE_I2C 1
@endcode

@section Documentation Documentation 

Please see the Classes tab for more information.

For I2C displays using the wire library Wire see the SSD1306AsciiWire class.

For I2C displays using the small AvrI2c class see the SSD1306AsciiAvrI2c class.

For SPI displays connected to the Arduino hardware SPI pins see the
SSD1306AsciiSpi class.

See the SSD1306AsciiSoftSpi class for use of Software SPI.


@section comment Bugs and Comments

If you wish to report bugs or have comments, open an issue on GitHub or 
send email to fat16lib@sbcglobal.net.  If possible, include a simple program
that illustrates the bug or problem.


@section ExampleS Examples

A number of examples are provided in the SSD1306Ascii/examples folder.

To access these examples from the Arduino development environment
go to:  %File -> Examples -> %SSD1306Ascii -> \<program Name\>

Compile and upload to your Arduino  to run the example.


 */
