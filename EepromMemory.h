#include <Arduino.h>
#include <EEPROM.h>

class EepromMemory{
  public:
  void setShiningPeriod(int period);

  int getShiningPeriod();

  private:
  int msTime = 0;
};