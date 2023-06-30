import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import time
#Abro Excel para guardar los datos
from gspread.models import Worksheet
import gspread

#Puerto serial del arduino
arduinoserial= serial.Serial('COM15',9600);

fig= plt.figure()
ax= fig.add_subplot(1,1,1)
xdatos, ydatos= [],[]

while True:

    #verificoconexion
    if(arduinoserial.inWaiting()>0):
        def animate(i,xdatos,ydatos):
            datos= arduinoserial.readline()
            datos= float(datos)
            xdatos.append(i)
            ydatos.append(datos)
            Hora = time.strftime("%H:%M:%S")
            Dia = time.strftime("%d/%m/%y")
            t=[i,datos,Hora,Dia]
            print(t)
            ax.clear()
            ax.plot(xdatos,ydatos)
            ax.plot(xdatos,ydatos, color= 'green') #marker='o' / '^'
            ax.grid(axis='y', color='gray', linestyle='dashed')
            plt.xlabel("Tiempo[s]")
            plt.ylabel("Concentracion de H2 [ppm]")
            plt.title("Concentración de H2 vs Tiempo")

        ani = animation.FuncAnimation(fig,animate,fargs=(xdatos,ydatos))
        plt.show()


