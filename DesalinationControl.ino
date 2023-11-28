// Code tested for Arduino Mega
#include <math.h>
#include "max6675.h"
#include "temperature_sensor.h"
#include "fuzzy_control.h"
#include "ezo_pmp_control.h"

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  
  initLevelSensors();
  initPumpControl();
  initFuzzyControl();
}

void loop () {
  setFuzzyMemberships();
}
