#define I2C_ADDRESS 0x3C

#include <Wire.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>

SSD1306AsciiWire oled;

int count;
int len;
int dir;
int lines;
const char* text;

const char down [] = "Hello";
const char up   [] = "Scrworld";

const uint8_t* fontlist[] =
{
  System5x7,
  Wendy3x5,
  Verdana12_italic,
  TimesNewRoman13,
  0
};
int font;

void resetscroll ()
{
  static int state = -1;
  state++;

  if (state & 4)
    oled.set2X();
  else
    oled.set1X();

  if (state == 8)
  {
    if (!fontlist[++font])
      font = 0;
    oled.setFont(fontlist[font]);
    state = 0;
  }

  if (!oled.reasonable())
    Serial.println(F("font too big for scrolling"));

  lines = oled.displayRows() / ((oled.fontHeight() + 7) / 8);
  dir = -dir;
  text = dir > 0 ? down : up;
  len = strlen(text);
  count = 0;
}

void setup ()
{
  Serial.begin(115200);

  Wire.begin();
  Wire.setClock(400000L);

  //oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.begin(&MicroOLED64x48, I2C_ADDRESS);

  oled.setFont(fontlist[font = 0]);
  oled.setScroll(true);
  oled.clear();

  oled.print("Smooth\n\nScrolling\n\ndemo");
  delay(3000);

  dir = -1;
  resetscroll();
}

void loop ()
{
  bool canPrintNow = oled.process(10);

  if (canPrintNow)
  {
    oled.scroll(dir);
    if (count < len)
    {
      oled.write("- ");
      oled.write(text[count]);
      oled.write(" -");
    }
    oled.clearToEOL();

    if (++count == len + lines)
      resetscroll();
  }
}
