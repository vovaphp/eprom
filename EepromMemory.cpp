#include "EepromMemory.h"

void EepromMemory::setShiningPeriod(int period) {
  EEPROM.put(0, period);
}

int EepromMemory::getShiningPeriod(){
  EEPROM.get(0, this -> msTime);
  return this -> msTime;
}