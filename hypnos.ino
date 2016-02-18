//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,1);

/* we always wait a bit between updates of the display */
unsigned long delaytime=1000;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
}

void display(const byte* picture, int delayTime) {
  /* now display them one by one with a small delay */
  lc.setRow(0,0,picture[0]);
  lc.setRow(0,1,picture[1]);
  lc.setRow(0,2,picture[2]);
  lc.setRow(0,3,picture[3]);
  lc.setRow(0,4,picture[4]);
  lc.setRow(0,5,picture[5]);
  lc.setRow(0,6,picture[6]);
  lc.setRow(0,7,picture[7]);
  delay(delayTime);
}

const byte moon[]={ B00111100,
                    B01110000,
                    B11100000,
                    B11100000,
                    B11100000,
                    B11110001,
                    B01111110,
                    B00111100};

const byte glyphSize = sizeof(moon) / sizeof(moon[0]);

byte sun[]={ 
                B10001000,
                B01001001,
                B00101010,
                B10000001,
                B00011000,
                B01111110,
                B11111111,
                B11111111};

void moveDown(const byte* glyph, byte count) {
  byte* settingGlyph = new byte[count];
  memcpy(settingGlyph, glyph, count);

  for (int i = 0; i < count; ++i) {
    lc.setIntensity(0,(count - i) * 2 - 1);    
    display(settingGlyph, 1000);
    // shift one row down
    for (int j = count - 1; j > 0; --j)
      settingGlyph[j] = settingGlyph[j-1];
    settingGlyph[0] = 0;      
  }
  display(settingGlyph, 1000);
  free(settingGlyph);
}

void moveUp(const byte* glyph, byte count) {
  byte* risingGlyph = new byte[count];
  memset(risingGlyph, 0, count);

  for (int i = count - 1; i >= 0; --i) {
    lc.setIntensity(0,(count - i) * 2 - 1);    
    display(risingGlyph, 1000);
    // shift one row up
    for (int j = 0; j < count - 1; ++j)
      risingGlyph[j] = risingGlyph[j+1];
    risingGlyph[count - 1]  = glyph[count - i - 1];
  }
  display(risingGlyph, 1000);
  free(risingGlyph);  
}

void loop() { 
  static bool rising = true;
  static bool isMoon = false;
  
  const byte* glyph = isMoon ? moon : sun;
  if (rising) {
    moveUp(glyph, glyphSize);
    display(glyph, 3000);
    rising = false;
  } else {
    moveDown(glyph, glyphSize);  
    rising = true;
    isMoon = !isMoon;
  }
  
/*  display(sleepingFace, 2000);
  display(moon, 2000);
  for (int i = 0; i < 10; i++) {
    display(moonWithStar1, 400);
    display(moonWithStar2, 1000);
  }
  display(moon, 2000);

  display(stars, 2000);
  for (int i = 0; i < 10; i++) {
    display(stars1, 500);
    display(stars2, 500);
  }
  display(stars, 2000);
  display(smilingFace, 2000);*/
  /*writeArduinoOnMatrix();
  rows();
  columns();
  single();*/
}
