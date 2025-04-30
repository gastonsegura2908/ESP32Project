#include <WiFi.h>
#include <WebServer.h>
#include "secrets.h"

WebServer server(80);  // Puerto 80

// Función que simula lectura del sensor con valor aleatorio
String getTemperatura() {
  float temp = random(200, 300) / 10.0;  // Genera un valor entre 20.0 y 30.0
  return "{\"temperatura\": " + String(temp, 1) + "}";
}

void handleRoot() {
  server.send(200, "text/plain", "API REST ESP32");
}

void handleTemperatura() {
  server.send(200, "application/json", getTemperatura());
}

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));  // Inicializa el generador de números aleatorios

  WiFi.begin(ssid, password);
  Serial.print("Conectando");

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
}
