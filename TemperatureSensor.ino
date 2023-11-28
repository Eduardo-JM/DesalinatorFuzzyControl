MAX6675 solarReceiverTemp(
  SOLAR_RECEIVER_TEMPERATURE_SENSOR_PIN_SO,
  SOLAR_RECEIVER_TEMPERATURE_SENSOR_PIN_CS,
  SOLAR_RECEIVER_TEMPERATURE_SENSOR_PIN_SCK
);

float readTemperature(enum TEMPERATURE_SENSOR sensor){
  switch (sensor){
    case SEAWATER_TEMPERATURE_SENSOR:
      return readThermistorTemperature(SEA_WATER_TEMPERATURE_SENSOR_PIN);
    case HEATED_SEAWATER_TEMPERATURE_SENSOR:
      return readThermistorTemperature(HEATED_SEA_WATER_TEMPERATURE_SENSOR_PIN);
    case SOLAR_RECEIVER_TEMPERATURE_SENSOR:
      return readThermocoupleTemperature(solarReceiverTemp);
  }
  return -1.0;
}

/**
 * This method reads the temperature of the passed MAX6675 sensor
*/
float readThermocoupleTemperature(MAX6675 sensor) {
  return sensor.readCelsius();
}

float readThermistorTemperature(int pin){
  float Vo = analogRead(pin);
  float R = THERMISTOR_FIXED_RESISTANCE * ((1023.0 / (float) Vo) - (float) 1.0);
  float logr = log(R);

  return (1 / (STEINHART_HART_CONSTANT_A + logr * STEINHART_HART_CONSTANT_B + STEINHART_HART_CONSTANT_C * pow(logr,3))) - 273.15;
}
