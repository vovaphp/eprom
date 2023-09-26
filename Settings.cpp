#include "Arduino.h"
#include "HardwareSerial.h"
#include "Settings.h"
Settings::Settings(Button &modeButton, Button &decrButton, Button &incrButton, LiquidCrystal_I2C &lcd, byte ledPin, byte buzzerPin) {
  this->modeButton = &modeButton;
  this->decrButton = &decrButton;
  this->incrButton = &incrButton;
  this->lcd = &lcd;
  this->ledPin = ledPin;
  this->buzzerPin = buzzerPin;
}

void Settings::begin() {
  this->lcd->init();
  this->lcd->setCursor(3, 0);
  this->lcd->print("Welcome!!!");
  this->modeButton->begin();
  this->decrButton->begin();
  this->incrButton->begin();
  this->temporaryShinePeriod = this->memory.getShiningPeriod();
  this->checkAvailablePeriod();
}

void Settings::checkEdit() {
  if (this->modeButton->pressed()) {
    if (this->editOn) {  //это означает что кнопка нажата второй раз - поэтому нужно сохранить все данные в память
      this->memory.setShiningPeriod(this->temporaryShinePeriod);
      this->lcd->setCursor(1, 0);
      this->lcd->print("LED is Shining");
      this->buzzer();//TODO create class
    }
    this->editOn = !this->editOn;
    this->buzzer();
  }
  this->edit();
  this->ledShine();
}
void Settings::edit() {
  if (this->editOn) {
    this->lcd->setCursor(1, 0);
    this->lcd->print("Settings Mode:");

    if (!this->temporaryShinePeriod) {
      this->temporaryShinePeriod = this->memory.getShiningPeriod();
    }

    if (this->decrButton->pressed()) {
      Serial.println("decrButton pressed");
      this->temporaryShinePeriod -= STEP_SHINING;
      this->checkAvailablePeriod();
      this->buzzer();
    }
    if (this->incrButton->pressed()) {
      Serial.println("incrButton pressed");
      this->temporaryShinePeriod += STEP_SHINING;
      this->buzzer();
    }

    this->lcd->setCursor(1, 1);
    this->lcd->print("timing: ");
    this->lcd->print(this->temporaryShinePeriod);
    this->lcd->print(" ms");
  }

  digitalWrite(this->ledPin, this->ledSwitcher.revercer(this->temporaryShinePeriod));
}
void Settings::ledShine() {
  digitalWrite(this->ledPin, this->ledSwitcher.revercer(this->temporaryShinePeriod));
  Serial.println(this->temporaryShinePeriod);
}
void Settings::checkAvailablePeriod() {
  if (this->temporaryShinePeriod < 1) {
    this->temporaryShinePeriod = STEP_SHINING;
  }
}
void Settings::buzzer(){
  analogWrite(this->buzzerPin, 100);
  delay(100);
  analogWrite(this->buzzerPin, 0);

}