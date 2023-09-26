//#include <hd44780.h>
//#include <TimerSingl.h>
// #include <Button.h>
// #include <LiquidCrystal_I2C.h>
//#include "EepromMemory.h"

#define MODE_BTN 12
#define DECR_BTN 11
#define INCR_BTN 10

#define LED_PIN 9
#define BUZZER_PIN 3

#include "Settings.h"

Button modeButton(MODE_BTN);
Button decrButton (DECR_BTN);
Button incrButton (INCR_BTN);

LiquidCrystal_I2C lcd(0x27, 16, 2);

//Settings setOption(10,10,10,10,LED_PIN);
Settings setOption(modeButton,decrButton,incrButton,lcd,LED_PIN,BUZZER_PIN);

//LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  pinMode(MODE_BTN, INPUT_PULLUP);
  pinMode(DECR_BTN, INPUT_PULLUP);
  pinMode(INCR_BTN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
 setOption.begin();
}

void loop() {
  setOption.checkEdit();
 //Serial.println("Button Mode pressed");
}

// void ledShine() {
//   //int msTime = getShiningPeriod();
//   int msTime = eMemory.getShiningPeriod();
//   if(msTime == -1){
//      msTime = defShinePeriod;
//   }
//   digitalWrite(LED_PIN,ledSwitcher.revercer(msTime));
// }

// void signal(int pin, byte toneNumber, int timer){
//   analogWrite(pin, toneNumber);
//   delay(timer);
//   analogWrite(pin, 0);
//   delay(timer);
// }