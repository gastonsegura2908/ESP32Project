#ifndef TEMPERATURE_UTILS_H
#define TEMPERATURE_UTILS_H

#include <Arduino.h>

/**
 * @brief Genera una carga JSON con un valor de temperatura aleatorio.
 * @return String con el objeto JSON.
 */
String generateTemperaturePayload();

#endif  // TEMPERATURE_UTILS_H
