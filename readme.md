# ESP32 Temperature Sensor Simulator

Este proyecto implementa una simulación de lectura de temperatura en una ESP32 utilizando PlatformIO y el framework Arduino. El valor de temperatura se genera aleatoriamente, se empaqueta como un objeto JSON y es enviado a una API REST protegida con clave.

## 🚀 Cómo compilar y cargar
- Conectar la ESP32 por USB.
- Asegurarse de que el puerto COM en platformio.ini sea correcto.
- Ejecutá:
pio run -e esp32dev -t upload
- Para abrir el monitor serie:
pio device monitor

## 🧪 Cómo ejecutar los tests
Este proyecto usa Unity Test Framework integrado en PlatformIO.
pio test -e esp32dev_test -vvv

## 🌐 API REST
Los datos generados pueden ser enviados a una API REST. La autenticación se hace mediante una clave secreta que debe incluirse en los headers.

Ejemplo de uso con curl (en Windows)
curl -H "Authorization: Bearer clave_secreta" http://localhost:5000/temperatura

## 📋 Funcionalidades
- 📡 Generación aleatoria de temperatura entre 20.0 y 30.0 °C
- 📦 Empaquetado de datos en formato JSON
- 🔐 Autenticación con API Key
- ✅ Tests unitarios para validación del JSON
- 🧩 Modularización con funciones reutilizables

## ✅ TODO / Ideas futuras
- Docketizar API
- Agregar otros sensores (por ejemplo, humedad)
- Base de datos

## 🧠 Créditos
Desarrollado por Gaston Marcelo Segura como parte de un proyecto con ESP32.