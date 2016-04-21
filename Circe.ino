//We always have to include the library
#include "LedControl.h"
#include "Wire.h"

#define DS3231_I2C_ADDRESS 0x68
#define MICROPHONE_PIN A0 // select the input pin for the potentiometer
#define _countof( x )  ( sizeof( x ) / sizeof( *x ) )

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

const byte kidsAwoken = 0;
const byte kidsGoingToBed = 1;
const byte kidsSleeping = 2;
const byte kidsWakingUp = 3;

const byte Sunday =1;
const byte Monday = 2;
const byte Tuesday=3;
const byte Wednesday=4;
const byte Thursday=5;
const byte Friday=6;
const byte Saturday=7;


void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
dayOfMonth, byte month, byte year)
{
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
void readDS3231time(byte *second,
byte *minute,
byte *hour,
byte *dayOfWeek,
byte *dayOfMonth,
byte *month,
byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

void setup() {
  Wire.begin();
  Serial.begin(9600);  
  
  // Clock initialization
  // Serial.print("Clock initialization\n");
  // setDS3231time(0, 37, 21, 5, 31, 3, 16);
  logTime();
}

byte decToBcd(byte val)
{
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return( (val/16*10) + (val%16) );
}

void logTime()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month,
  &year);
  // send it to the serial monitor
  Serial.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  Serial.print(":");
  if (minute<10)
  {
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second<10)
  {
    Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print(" ");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  Serial.print(" Day of week: ");
  switch(dayOfWeek){
  case Sunday:
    Serial.println("Sunday");
    break;
  case Monday:
    Serial.println("Monday");
    break;
  case Tuesday:
    Serial.println("Tuesday");
    break;
  case Wednesday:
    Serial.println("Wednesday");
    break;
  case Thursday:
    Serial.println("Thursday");
    break;
  case Friday:
    Serial.println("Friday");
    break;
  case Saturday:
    Serial.println("Saturday");
    break;
  }
}

const byte moon[]={ B00111100,
                    B01111110,
                    B11111111,
                    B11100011,
                    B11000001,
                    B11000001,
                    B01000000,
                    B00100000};

const byte glyphSize = _countof(moon);

byte sun[]={ 
                B10001000,
                B01001001,
                B00101010,
                B10000001,
                B00011000,
                B01111110,
                B11111111,
                B11111111};

byte smiley[]={ 
                B00000000,
                B00110010,
                B01100110,
                B01000010,
                B01000000,
                B01000010,
                B01100110,
                B00110010};

byte smileyLeft[]={ 
                B00000000,
                B00110110,
                B01100010,
                B01000010,
                B01000000,
                B01000110,
                B01100010,
                B00110010};

byte smileyRight[]={ 
                B00000000,
                B00110010,
                B01100010,
                B01000110,
                B01000000,
                B01000010,
                B01100010,
                B00110110};

byte skull1[]={ 
                B00011110,
                B00111111,
                B11100111,
                B01100111,
                B11111111,
                B01100111,
                B11100111,
                B00111110};

byte skull2[]={ 
                B00011110,
                B11100111,
                B01100111,
                B11111111,
                B01100111,
                B11100111,
                B00111111,
                B00111110};

byte ghost1[]={ 
                B10000000,
                B11111100,
                B11111110,
                B11100111,
                B10111111,
                B10111111,
                B10100110,
                B11111100};

byte ghost2[]={ 
                B11111100,
                B10100110,
                B10111111,
                B10111111,
                B11100111,
                B11111110,
                B11111100,
                B10000000};
           
byte blink1[]={ 
                B00010000,
                B00110010,
                B01100110,
                B01000010,
                B01000000,
                B01000010,
                B01100100,
                B00100010};

byte blink2[]={ 
                B00011000,
                B00110010,
                B01100110,
                B01000010,
                B01000000,
                B01000100,
                B01000100,
                B00000100};

typedef struct AnimationStep {
  byte* glyph; // picture to display
  int delay; // display time, in ms
} AnimationStep;

AnimationStep blinkAnimation[] = { { blink1, 100 }, { blink2, 500 }, { blink1, 100 }, { smiley, 1000 } };
AnimationStep ghostAnimation[] = { { ghost1, 800 }, { ghost2, 800 }, { ghost1, 800 }, { ghost2, 800 }, { ghost1, 800 }, { ghost2, 800 } };
AnimationStep skullAnimation[] = { { skull1, 800 }, { skull2, 800 }, { skull1, 800 }, { skull2, 800 }, { skull1, 800 }, { skull2, 800 } };
AnimationStep lookOnSidesAnimation[] = { { smiley, 800 }, { smileyLeft, 800 }, { smiley, 800 }, { smileyRight, 800 }, { smiley, 800 } };

void displayGlyph(const byte* picture, int delayTime = 0) {
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

void playAnimation(struct AnimationStep* steps, byte stepsCount) {
  for (int i = 0; i < stepsCount; ++i) {
    displayGlyph(steps[i].glyph, steps[i].delay);
  }
}

void playWave(int delayMs) {
  byte wavePic[8] = {0, 0, 0, 0 ,0 ,0 ,0 ,0};
  const int DELAY_PER_PIC = 100;

  for (int i = 0, elapsedMs = 0; elapsedMs < delayMs; ++i, elapsedMs += DELAY_PER_PIC) {
    for (int col = 0; col < 8; ++col) {
      wavePic[col] = 1 << (4 + round(3.0 * sin((col + i) * (2*PI) / 8)));
    }
    displayGlyph(wavePic, DELAY_PER_PIC);
  }
}

void playEqualizer(int delayMs) {
  byte equalizerPic[8] = {0, 0, 0, 0 ,0 ,0 ,0 ,0};
  const int DELAY_PER_PIC = 100;

  for (int i = 0, elapsedMs = 0; elapsedMs < delayMs; ++i, elapsedMs += DELAY_PER_PIC) {
    for (int col = 0; col < 8; ++col) {
      equalizerPic[col] = 0xFF << random(1, 8);
    }
    displayGlyph(equalizerPic, DELAY_PER_PIC);
  }
}

void moveDown(const byte* glyph, byte count) {
  byte settingGlyph[count];
  memcpy(settingGlyph, glyph, count);

  for (int i = 0; i < count; ++i) {
    displayGlyph(settingGlyph, 1000);
    // shift one row down
    for (int j = count - 1; j >= 0; --j)
      settingGlyph[j] = glyph[j] << i;
  }
  displayGlyph(settingGlyph, 1000);
}

void moveUp(const byte* glyph, byte rowCount) {
  byte risingGlyph[rowCount];
  memset(risingGlyph, 0, rowCount);

  for (int i = rowCount - 1; i >= 0; --i) {
    displayGlyph(risingGlyph, 1000);
    // shift one row up
    for (int j = 0; j < rowCount; ++j)
      risingGlyph[j] = glyph[j] << i;
  }
  displayGlyph(risingGlyph, 1000);
}

byte getKidsState() {
  // Based on the current day and time, define in which state the kids should be (sleeping, awoken, etc.)
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // Read date and time from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);

  // What's the kids schedule ?
  byte goingToBedHour = 20;
  byte goingToBedMin = 00;
  byte sleepingHour = 20;
  byte sleepingMin = 20;
  
  byte wakingUpHour = 7;
  byte wakingUpMin = 00;
  byte awokenHour = 8;
  byte awokenMin = 00;
  if (dayOfWeek == Saturday || dayOfWeek == Sunday) {
    wakingUpHour = 8;
    wakingUpMin = 0;
    awokenHour = 9;
    awokenMin = 00;
  }
  
  // Assumptions :
  // - kids are asleep at midnight 
  // - kidsWakingUpTime < kidsAwokenTime < kidsGoingToBedTime < kidsSleepingTime
  if (hour > sleepingHour || (hour == sleepingHour && minute > sleepingMin) || (hour < wakingUpHour) || (hour == wakingUpHour && minute < wakingUpMin))
    return kidsSleeping;
    
  if (hour > goingToBedHour || (hour == goingToBedHour && minute > goingToBedMin))
    return kidsGoingToBed;

  if (hour > awokenHour || (hour == awokenHour && minute > awokenMin))
    return kidsAwoken;

  return kidsWakingUp;
}

byte previousKidsState = -1;

typedef struct {
  size_t timeMs;
  int level;
} SoundLevel;


SoundLevel soundLevelHistory[50] = { 0 };
int soundLevelHistoryPos = -1;
int soundLevelHistoryCount = 0;
size_t lastClapDetectionTime = 0;

float soundLevelAverage(size_t from = 0, size_t to = 0xFFFFFFFF) {
  float silenceLevel = 0.0;
  int nbSamples = 0;
  for (int i = 0; i < soundLevelHistoryCount; ++i) {
    if (soundLevelHistory[i].timeMs >= from && soundLevelHistory[i].timeMs <= to) {
      silenceLevel += float(soundLevelHistory[i].level);
      ++nbSamples;
    }
  }

  if (nbSamples == 0)
    return 0;

  silenceLevel /= (float)nbSamples;

  return silenceLevel;
}

float soundLevelMeanAbsoluteDeviation(float avgSoundLevel, size_t from = 0, size_t to = 0xFFFFFFFF) {
  float meanAbsDev = 0.0;
  int nbSamples = 0;
  for (int i = 0; i < soundLevelHistoryCount; ++i) {
    if (soundLevelHistory[i].timeMs >= from && soundLevelHistory[i].timeMs <= to) {
      meanAbsDev += float(soundLevelHistory[i].level) > avgSoundLevel ? float(soundLevelHistory[i].level) - avgSoundLevel : avgSoundLevel - float(soundLevelHistory[i].level);
      ++nbSamples;
    }
  }

  if (nbSamples == 0)
    return 0;

  meanAbsDev /= (float)nbSamples;

  return meanAbsDev;
}



void appendSoundLevel(size_t timeMs, int soundLevel) {
  soundLevelHistoryPos = ++soundLevelHistoryPos % _countof(soundLevelHistory);
  if (soundLevelHistoryCount < _countof(soundLevelHistory))
    ++soundLevelHistoryCount;

  soundLevelHistory[soundLevelHistoryPos].timeMs = timeMs;
  soundLevelHistory[soundLevelHistoryPos].level = soundLevel;
  Serial.print(timeMs);
  Serial.print(";");
  Serial.println(soundLevel);
}

bool hasClapped(size_t previousClapTime = 0) {
  if (soundLevelHistoryCount == 0)
    return false;
  
  const size_t CLAP_DURATION = 200;

  int lastSamplingTime = soundLevelHistory[soundLevelHistoryPos].timeMs;
  if (lastSamplingTime - previousClapTime < (3*CLAP_DURATION))
    return false; // not enough time elapsed since previous clap, ignore

  // A clap lasts 200 ms, we compare the sound level from the latest 200 ms to the previous one
  float avgSoundLevel = soundLevelAverage(0, lastSamplingTime - CLAP_DURATION);
  if (avgSoundLevel == 0)
    return false; 

  float recentDeviationFromAvgSoundLevel = soundLevelMeanAbsoluteDeviation(avgSoundLevel, lastSamplingTime - CLAP_DURATION);

  return recentDeviationFromAvgSoundLevel > 1.0;
}

void loop() { 
  byte kidsState = getKidsState();  
  bool stateChanged = kidsState != previousKidsState;

  switch (kidsState) {
    case kidsAwoken:
      {
        // When a big noise is detected (ex : a clap), play some random animations if the kids are awoken
        int soundLevel = analogRead (MICROPHONE_PIN);
        appendSoundLevel(millis(), soundLevel);
        bool clapped = hasClapped();

        if (clapped) {
          // Clap detected
          lc.shutdown(0,false);
          lc.setIntensity(0,15);
          lc.clearDisplay(0);
          
          switch (random(0, 6)) {
            case 0:
              playAnimation(skullAnimation, _countof(skullAnimation));
              break;          
            case 1:
              playAnimation(ghostAnimation, _countof(ghostAnimation));
              break;          
            case 2:
              playWave(5000);
              break;          
            case 3:
              playEqualizer(5000);
              break;          
            case 4:
              playAnimation(lookOnSidesAnimation, _countof(lookOnSidesAnimation));
              break;          
            default:    
              playAnimation(blinkAnimation, _countof(blinkAnimation));
          }
        } 

        if (clapped || stateChanged) {
          lc.clearDisplay(0);
          lc.shutdown(0,true);
        }
      }
      break;
    case kidsGoingToBed:
      lc.shutdown(0,false);
      lc.setIntensity(0,8);    
      moveUp(moon, glyphSize);
      break;
    case kidsSleeping:
      if (stateChanged) {
        lc.shutdown(0,false);
        lc.setIntensity(0,0);    
        displayGlyph(moon, 100);
      }
      break;
    case kidsWakingUp:
      lc.shutdown(0,false);
      lc.setIntensity(0,8);    
      playAnimation(lookOnSidesAnimation, _countof(lookOnSidesAnimation));
      playAnimation(blinkAnimation, _countof(blinkAnimation));
      break;
  }

  previousKidsState = kidsState;
}
