#define SEA_WATER_LEVEL_SENSOR_PIN 5
#define CONDENSED_WATER_LEVEL_SENSOR_PIN 6

#define SEA_WATER_LEVEL_SENSOR_RELAY_PIN 7
#define CONDENSED_WATER_LEVEL_SENSOR_RELAY_PIN 8

void initLevelSensors();
bool isSensorActive(int sensor_pin);
void activateRelay (int relay_pin);
void deactivateRelay (int relay_pin);
