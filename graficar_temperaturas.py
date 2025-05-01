import pandas as pd
import matplotlib.pyplot as plt

# Cargar el archivo CSV (debe estar en el mismo directorio)
df = pd.read_csv('temperaturas.csv')

# Asegurar que 'timestamp' esté en formato datetime
df['timestamp'] = pd.to_datetime(df['timestamp'])

# Graficar
plt.figure(figsize=(10, 5))
plt.plot(df['timestamp'], df['temperatura'], marker='o')
plt.title('Temperaturas registradas')
plt.xlabel('Fecha y hora')
plt.ylabel('Temperatura (°C)')
plt.grid(True)
plt.xticks(rotation=45)
plt.tight_layout()
plt.show()
