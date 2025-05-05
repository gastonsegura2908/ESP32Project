#include <Arduino.h>
#include <unity.h>
#include <ArduinoJson.h>
#include "networkUtils.h"
#include "temperatureUtils.h"

/**
 * @brief Test: Verifica que el JSON generado sea válido y que "temperatura" esté en rango.
 */
void testGenerateTemperaturePayloadValidJson() {
    String payload = generateTemperaturePayload();

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload);

    TEST_ASSERT_FALSE(error);
    TEST_ASSERT_TRUE(doc["temperatura"].is<float>());  

    float temp = doc["temperatura"];
    TEST_ASSERT_TRUE(temp >= 20.0 && temp <= 30.0);
}

//#ifdef UNIT_TEST
// This code only runs when in test mode
void setup() {
    Serial.begin(115200);
    delay(2000); // Give the serial monitor time to open
    UNITY_BEGIN();
    RUN_TEST(testGenerateTemperaturePayloadValidJson);
    UNITY_END();
}

void loop() {
    // Nothing to do here
}
//#endif