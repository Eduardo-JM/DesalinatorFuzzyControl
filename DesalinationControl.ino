// Code tested for Arduino Mega
#include <math.h>
#include <stdarg.h>
#include "max6675.h"
#include "temperature_sensor.h"
#include "fuzzy_control.h"
#include "ezo_pmp_control.h"
#include "utils.h"
#include "water_level_sensor.h"

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  
  //initLevelSensors();
  //initPumpControl();
  //initFuzzyControl();
}

void loop () {
  //fillSeawaterIfNecessary();
  //setFuzzyMemberships();
  //Serial.println(String(readTemperature(SEAWATER_TEMPERATURE_SENSOR)));
  //delay(1000);
}
