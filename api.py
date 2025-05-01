from flask import Flask, request, jsonify
import csv
from datetime import datetime

app = Flask(__name__)
datos = []
csv_file = 'temperaturas.csv'

# Crear archivo CSV si no existe y escribir encabezado
try:
    with open(csv_file, 'x', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['timestamp', 'temperatura'])  # Encabezado
except FileExistsError:
    pass  # Si ya existe, no lo sobrescribe

@app.route('/')
def home():
    return "API REST funcionando"

@app.route('/temperatura', methods=['POST'])
def recibir_temperatura():
    data = request.json
    timestamp = datetime.now().isoformat()
    temperatura = data.get('temperatura')

    # Guardar en memoria
    datos.append({'timestamp': timestamp, 'temperatura': temperatura})

    # Guardar en CSV
    with open(csv_file, 'a', newline='') as f:
        writer = csv.writer(f)
        writer.writerow([timestamp, temperatura])

    return jsonify({"status": "ok", "data_recibida": data})

@app.route('/temperatura', methods=['GET'])
def obtener_temperaturas():
    return jsonify(datos)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
