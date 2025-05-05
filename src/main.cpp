#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "secrets.h"
#include "networkUtils.h"
#include "temperatureUtils.h"

WebServer server(80);  ///< Servidor HTTP en el puerto 80

unsigned long lastPostTime = 0;
const unsigned long postInterval = 30000;  ///< Intervalo de POST en milisegundos

#ifndef UNIT_TEST
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

#endif  // UNIT_TEST