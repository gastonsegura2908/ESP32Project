#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "secrets.h"

WebServer server(80);  ///< Servidor HTTP en el puerto 80

unsigned long lastPostTime = 0;
const unsigned long postInterval = 30000;  ///< Intervalo de POST en milisegundos
const int maxRetries = 3;  ///< Número máximo de reintentos si falla el POST

/**
 * @brief Genera una carga JSON con un valor de temperatura aleatorio.
 * @return String con el objeto JSON.
 */
String generateTemperaturePayload() {
  StaticJsonDocument<200> jsonDoc;
  float temperature = random(200, 300) / 10.0;  // Entre 20.0 y 30.0
  jsonDoc["temperatura"] = temperature;

  String payload;
  serializeJson(jsonDoc, payload);
  return payload;
}

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

/**
 * @brief Configura la conexión WiFi y el servidor HTTP.
 */
void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));  // Inicializa generador de números aleatorios

  WiFi.begin(ssid, password);
  Serial.print("Conectando...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado. IP: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

/**
 * @brief Bucle principal que maneja clientes y realiza el POST periódico.
 */
void loop() {
  server.handleClient();

  unsigned long currentMillis = millis();
  if (currentMillis - lastPostTime >= postInterval) {
    lastPostTime = currentMillis;
    postTemperature();
  }
}
