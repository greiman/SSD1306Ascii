#define I2C_ADDRESS 0x3C

#include <Wire.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>

SSD1306AsciiWire oled;

const char story [] =
  // https://letterpile.com/creative-writing/50-Word-Mini-Stories-Creative-Writing-Exercise
  "- - - - - - - ----- "
  "An aggressive alien creature visited our planet. "
  "It was ugly, with a big nose, pinkish hairy skin, "
  "and feet that smelled. It was frightened of us for "
  "no reason. It resented our differences. It laid claim "
  "to our planet. "
  "This strange alien was an Earth Human. "
  "It called me 'alien'.";

const char* next;

void setup ()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  Wire.begin();
  Wire.setClock(400000L);

  //oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.begin(&MicroOLED64x48, I2C_ADDRESS);

  oled.setFont(System5x7);
  oled.setScroll(true);
  oled.clear();

  if (!oled.reasonable())
    Serial.println(F("font too big for scrolling"));

  next = story;
}

void loop ()
{
  bool canPrintNow = oled.process(75);
  digitalWrite(LED_BUILTIN, !canPrintNow);

  if (canPrintNow)
  {
    if (*next == ' ')
      next++;
    else
    {
      const char* wall = strchr(next, ' ');
      if (!wall)
        wall = next + strlen(next);
      oled.println();
      while (next < wall)
        oled.print(*next++);
      if (*(next - 1) == '.')
        oled.println();
    }
    if (!*next)
      next = story;
  }
}
