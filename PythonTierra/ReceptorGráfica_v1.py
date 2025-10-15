import serial
import matplotlib.pyplot as plt
from collections import deque
import threading
import time
#Inicio parámetros, definiciones y configuraciones iniciales.
#parámetres inicials??
#inicio inicialización Serial
device = 'COM7'
mySerial = serial.Serial(device, 9600, timeout=1)

max_points = 100  # Puntos máximos visibles.
temps = deque([0]*max_points, maxlen=max_points)
hums = deque([0]*max_points, maxlen=max_points)

latest_data = {"temp": 0, "hum": 0}  # variable compartida

#Definimos la función read_serial que se encargara de leer los datos:
def read_serial():
    while True:
        linea = mySerial.readline().decode('utf-8').strip()
        if ":" in linea:
            ht = linea.split(":")
            try:
                temp = float(ht[1]) / 100
                hum = float(ht[0]) / 100
                latest_data["temp"] = temp
                latest_data["hum"] = hum
                print(f"Serial: {temp:.2f} °C, {hum:.2f} %")
            except (ValueError, IndexError):
                # Ignora linees invalides.
                pass
        time.sleep(0.01)  

#Inicar un proceso de segundo plano
threading.Thread(target=read_serial, daemon=True).start()

#Inicio config. grafica
plt.ion()
fig, ax = plt.subplots()
line_temp, = ax.plot(range(max_points), temps, label='Temperature')
line_hum, = ax.plot(range(max_points), hums, label='Humidity')
ax.set_ylim(0, 100)  # adjust to your data range
ax.set_xlabel('Samples')
ax.set_ylabel('Value')
ax.legend()
plt.title("Temperatura i Humitat")
xdata = []
ydata = []
line, = ax.plot([], [], lw=2)
#Fin de configuración de la gráfica

#Fin parámetros, definiciones y configuraciones iniciales.


#Loop de actualización de la gráfica:
while True:
    if not plt.fignum_exists(fig.number):
        break

    temps.append(latest_data["temp"])
    hums.append(latest_data["hum"])

    line_temp.set_ydata(temps)
    line_hum.set_ydata(hums)
    line_temp.set_xdata(range(len(temps)))
    line_hum.set_xdata(range(len(hums)))

    ax.relim()
    ax.autoscale_view()

    plt.draw()
    plt.pause(0.05)
#Fin loop de actualización de la gráfica
