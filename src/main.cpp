#include <WiFi.h>
#include <WebServer.h>
#include "secrets.h"
#include <Arduino.h>
#include <HTTPClient.h> 

WebServer server(80);  // Puerto 80

// Función que simula lectura del sensor con valor aleatorio
String getTemperatura() {
  float temp = random(200, 300) / 10.0;  // Genera un valor entre 20.0 y 30.0
  return "{\"temperatura\": " + String(temp, 1) + "}";
}

void postTemperatura() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(api_url);
    http.addHeader("Content-Type", "application/json");

    String payload = getTemperatura();
    int httpResponseCode = http.POST(payload);

    Serial.print("POST a API: ");
    Serial.println(payload);
    Serial.print("Código de respuesta: ");
    Serial.println(httpResponseCode);

    http.end();
  } else {
    Serial.println("WiFi no conectado");
  }
}

void handleRoot() {
  server.send(200, "text/plain", "API REST ESP32");
}

void handleTemperatura() {
  server.send(200, "application/json", getTemperatura());
}

unsigned long lastPostTime = 0;
const unsigned long interval = 30000;  // 30 segundos

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));  // Inicializa el generador de números aleatorios

  WiFi.begin(ssid, password);
  Serial.print("Conectando...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500); 
    Serial.print("No conectado");
  }

  Serial.println("\nWiFi conectado. IP: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/temperatura", handleTemperatura);

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient();

  unsigned long currentMillis = millis();
  if (currentMillis - lastPostTime >= interval) {
    lastPostTime = currentMillis;
    postTemperatura();
  }
}
