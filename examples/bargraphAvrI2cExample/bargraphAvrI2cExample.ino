//Added by jonathanmlang
#include <Arduino.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

SSD1306AsciiAvrI2c oled;
//------------------------------------------------------------------------------

byte barLength =118; //total length of bar excluding ends
byte barVal    =52;  //value of bar
byte barNotch  =10;  //location of notch in bar

byte barXpos   =5;
byte barYcol   =5;

void setup() {

#if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  //oled.begin(&ST7567_128x64, I2C_ADDRESS);
#endif // RST_PIN >= 0


  
}

void drawBar(){

  oled.setFont(bargraph);

  oled.setCursor(barXpos-1,barYcol);

  oled.print('b'); //small bar line to close the front of the bar

  for (byte barPos=0; barPos < barLength; barPos++){
    if (barPos == barNotch){
      oled.print(barPos<barVal ? 'b' : 'e');    //if the bar position equals barNotch, draw the bar thinner to create a notch.
    }
    else{
      oled.print(barPos<barVal ? 'a' : 'd');    //if the bar position is less than bar value, draw filled line else draw empty line
    }
  }
  oled.print('b'); //small bar line to close the end of the bar

}

//------------------------------------------------------------------------------
void loop() {

  oled.setFont(System5x7);
  oled.setCursor(2,1);

  oled.print("Bar value: "); oled.print(barVal); oled.print("   ");

  drawBar();

  barVal<barLength ? barVal++ : barVal=0;

  delay(100);
}
