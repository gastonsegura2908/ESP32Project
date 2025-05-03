#include <ArduinoJson.h>
#include "temperatureUtils.h"

/**
 * @brief Genera una carga JSON con un valor de temperatura aleatorio.
 * @return String con el objeto JSON.
 */
String generateTemperaturePayload() {
    JsonDocument jsonDoc;  // ✅ Se evita el uso explícito de StaticJsonDocument
    float temperature = random(200, 300) / 10.0;  // Entre 20.0 y 30.0
    jsonDoc["temperatura"] = temperature;

    String payload;
    serializeJson(jsonDoc, payload);
    return payload;
}