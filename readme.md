# ESP32 Temperature Sensor Simulator

Este proyecto implementa una simulación de lectura de temperatura en una ESP32 utilizando PlatformIO y el framework Arduino. El valor de temperatura se genera aleatoriamente, se empaqueta como un objeto JSON y puede ser enviado a una API REST protegida con clave.

## 🔧 Dependencias

Las dependencias se gestionan automáticamente con PlatformIO. En particular:

- [ArduinoJson](https://arduinojson.org/) (por `bblanchon`)

Se incluyen en `platformio.ini`:

```ini
lib_deps = bblanchon/ArduinoJson

🚀 Cómo compilar y cargar
Conectá tu ESP32 por USB.

Asegurate de que el puerto COM en platformio.ini sea correcto.

Ejecutá:
pio run --target upload
Para abrir el monitor serie:
pio device monitor

🧪 Cómo ejecutar los tests
Este proyecto usa Unity Test Framework integrado en PlatformIO.
pio test

🌐 API REST
Los datos generados pueden ser enviados a una API REST. La autenticación se hace mediante una clave secreta (SecretAPIKey) que debe incluirse en los headers.

Ejemplo de uso con curl (en Windows)
curl -H "Authorization: Bearer SecretAPIKey" http://localhost:5000/temperatura

📋 Funcionalidades
📡 Generación aleatoria de temperatura entre 20.0 y 30.0 °C

📦 Empaquetado de datos en formato JSON

🔐 Autenticación con API Key

✅ Tests unitarios para validación del JSON

🧩 Modularización con funciones reutilizables

✅ TODO / Ideas futuras
Enviar automáticamente los datos por WiFi a un servidor remoto

Agregar otros sensores (por ejemplo, humedad)

Almacenamiento local (SPIFFS / LittleFS)

Publicación a un broker MQTT

🧠 Créditos
Desarrollado por Gaston Marcelo Segura como parte de un proyecto con ESP32.