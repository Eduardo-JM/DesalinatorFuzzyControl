#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H


// This code was developed for module MAX6675 and thermistor probe USP10981

/* Thermistor constants for Steinhart-hart equation */
#define STEINHART_HART_CONSTANT_A 0.00112866
#define STEINHART_HART_CONSTANT_B 0.00023422
#define STEINHART_HART_CONSTANT_C (8.7159 * pow(10,-8))
#define THERMISTOR_FIXED_RESISTANCE 10000


#define SEA_WATER_TEMPERATURE_SENSOR_PIN A0
#define HEATED_SEA_WATER_TEMPERATURE_SENSOR_PIN A1

#define SOLAR_RECEIVER_TEMPERATURE_SENSOR_PIN_SO 9
#define SOLAR_RECEIVER_TEMPERATURE_SENSOR_PIN_CS 10
#define SOLAR_RECEIVER_TEMPERATURE_SENSOR_PIN_SCK 11

#define MINIMUM_FLOW 0.5

enum TEMPERATURE_SENSOR {
  SEAWATER_TEMPERATURE_SENSOR,
  HEATED_SEAWATER_TEMPERATURE_SENSOR,
  SOLAR_RECEIVER_TEMPERATURE_SENSOR
};

/**
 * This method reads the temperature for the selected sensor
*/
float readTemperature(enum TEMPERATURE_SENSOR);
float readThermistorTemperature(int);
float readThermocoupleTemperature(MAX6675);

#endif
