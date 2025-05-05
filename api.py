from flask import Flask, request, jsonify
import csv
from datetime import datetime
from dotenv import load_dotenv
import os

load_dotenv()
API_KEY = os.getenv("API_KEY_PY")
app = Flask(__name__)
dataBuffer = []
csvFilePath = 'temperaturas.csv'

def isAuthorized(request):
    """@brief Verifica si el encabezado Authorization contiene el token correcto."""
    token = request.headers.get("Authorization")
    return token == f"Bearer {API_KEY}"

def createCsvIfNotExists():
    """@brief Crea el archivo CSV con encabezado si no existe."""
    if not os.path.exists(csvFilePath):
        with open(csvFilePath, 'w', newline='') as f:
            writer = csv.writer(f)
            writer.writerow(['timestamp', 'temperatura'])

def saveTemperatureToCsv(timestamp, temperature):
    """@brief Guarda un registro de temperatura en el archivo CSV."""
    with open(csvFilePath, 'a', newline='') as f:
        writer = csv.writer(f)
        writer.writerow([timestamp, temperature])

@app.route('/')
def home():
    """@brief Ruta raíz para verificar si la API está activa."""
    return "API REST funcionando"

@app.route('/temperatura', methods=['POST'])
def receiveTemperature():
    """@brief Recibe datos de temperatura mediante POST y los guarda en memoria y CSV."""
    if not isAuthorized(request):
        return jsonify({"status": "unauthorized"}), 401

    data = request.get_json()

    if not data or 'temperatura' not in data:
        return jsonify({"status": "error", "message": "Falta el valor de 'temperatura'"}), 400

    timestamp = datetime.now().isoformat()
    temperature = data['temperatura']

    dataBuffer.append({'timestamp': timestamp, 'temperatura': temperature})
    saveTemperatureToCsv(timestamp, temperature)

    return jsonify({"status": "ok", "dataReceived": data})

@app.route('/temperatura', methods=['GET'])
def getTemperatures():
    """@brief Devuelve la lista de temperaturas registradas en memoria."""
    if not isAuthorized(request):
        return jsonify({"status": "unauthorized"}), 401

    return jsonify(dataBuffer)

if __name__ == '__main__':
    createCsvIfNotExists()
    app.run(host='0.0.0.0', port=5000)
