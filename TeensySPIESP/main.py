import serial
import pandas as pd

# Configuración del puerto serial
port = 'COM15'  # Reemplaza 'COM15' con el puerto serial correcto
baudrate = 9600

# Crear objeto Serial
ser = serial.Serial(port, baudrate)

# Crear listas para almacenar los datos
time_values = []
ppm_values = []

# Bucle principal
while True:
    # Leer una línea del puerto serial
    line = ser.readline().decode().strip()

    if line == 'g':
        # Crear un DataFrame con los datos
        data = {'Tiempo': time_values, 'Concentración de hidrógeno (ppm)': ppm_values}
        df = pd.DataFrame(data)

        # Guardar los datos en un archivo Excel
        df.to_excel('datos_hidrogeno.xlsx', index=False)

        print('Datos guardados en "datos_hidrogeno.xlsx"')
        break  # Salir del bucle

    try:
        ppm = float(line)  # Convertir la línea a un valor flotante de ppm
        time_values.append(len(time_values) + 1)  # Usar un contador como tiempo
        ppm_values.append(ppm)

    except ValueError:
        print('Valor no válido:', line)

# Cerrar el puerto serial al finalizar
ser.close()
