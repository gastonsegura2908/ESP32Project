#ifndef NETWORK_UTILS_H
#define NETWORK_UTILS_H

#include <WebServer.h>

extern WebServer server;  ///< Servidor HTTP global

void setupNetwork();      ///< Configura WiFi y servidor HTTP
void postTemperature();   ///< Envía POST a la API REST
void handleRoot();        ///< Maneja la ruta "/"

#endif
