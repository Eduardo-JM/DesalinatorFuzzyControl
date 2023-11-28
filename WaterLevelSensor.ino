#define SEA_WATER_LEVEL_SENSOR_PIN 5
#define CONDENSED_WATER_LEVEL_SENSOR_PIN 6

#define SEA_WATER_LEVEL_SENSOR_RELAY_PIN 7
#define CONDENSED_WATER_LEVEL_SENSOR_RELAY_PIN 8

/**
 * This method sets the pin modes' used for the control
 * of water supply to the system
 */
void initLevelSensors() {
  pinMode(SEA_WATER_LEVEL_SENSOR_PIN, INPUT);
  pinMode(CONDENSED_WATER_LEVEL_SENSOR_PIN, INPUT);
  
  pinMode(SEA_WATER_LEVEL_SENSOR_RELAY_PIN, OUTPUT);
  pinMode(CONDENSED_WATER_LEVEL_SENSOR_RELAY_PIN, OUTPUT);
}

/**
 * @returns true if sensor is active
 */
bool isSensorActive(int sensor_pin) {
  return digitalRead(sensor_pin) == HIGH;
}

/**
 * This method activates the relay power
 * the water pump
 */
void activateRelay (int relay_pin) {
  digitalWrite(relay_pin, HIGH);
}

/**
 * This method deactivates the relay to
 * shut down the water pump
 */
void deactivateRelay (int relay_pin) {
  digitalWrite(relay_pin, LOW);
}
