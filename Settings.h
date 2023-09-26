#include <Arduino.h>
#include "EepromMemory.h"
#include <TimerSingl.h>
#include <Button.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


#define STEP_SHINING 500 //increase or decrease step for each press button

class Settings{
public:
  //Settings(int modeButton, int decrButton, int incrButton, int lcd, byte ledPin);
  Settings(Button &modeButton, Button &decrButton, Button &incrButton, LiquidCrystal_I2C &lcd, byte ledPin, byte buzzerPin);
  void checkEdit();
  void edit();
  void begin();

private:
  bool editOn = false;
  byte ledPin;
  byte buzzerPin;

  Button * modeButton;
  Button * decrButton;
  Button * incrButton;
  LiquidCrystal_I2C * lcd;
  int temporaryShinePeriod = 0; //isset only when we correct time perion in Setting Mode
  EepromMemory memory;
  TimerSingl ledSwitcher;
  void ledShine();
  void checkAvailablePeriod();
  void buzzer();
};