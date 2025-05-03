#include "networkUtils.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "secrets.h"
#include "temperatureUtils.h"

const int maxRetries = 3;  ///< Número máximo de reintentos si falla el POST

/**
 * @brief Intenta enviar un POST con la temperatura a la API REST.
 * Reintenta en caso de fallo.
 */
void postTemperature() {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi no conectado");
      return;
    }
  
    String payload = generateTemperaturePayload();
    int attempt = 0;
    bool success = false;
  
    while (attempt < maxRetries && !success) {
      HTTPClient http;
      http.begin(api_url);
      http.addHeader("Content-Type", "application/json");
      http.addHeader("Authorization", String("Bearer ") + api_key);
  
      int responseCode = http.POST(payload);
      Serial.print("Intento POST #");
      Serial.println(attempt + 1);
      Serial.print("Payload: ");
      Serial.println(payload);
      Serial.print("Código de respuesta: ");
      Serial.println(responseCode);
  
      success = (responseCode >= 200 && responseCode < 300);
      http.end();
      attempt++;
  
      if (!success) delay(1000);  // Espera antes de reintentar
    }
  
    if (!success) {
      Serial.println("Error: No se pudo enviar el POST después de varios intentos.");
    }
  }
  
  /**
   * @brief Maneja la ruta raíz del servidor.
   */
  void handleRoot() {
    server.send(200, "text/plain", "API REST ESP32");
  }