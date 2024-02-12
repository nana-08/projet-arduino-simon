import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import serial 
# installer le module serial au prealable (avec la commande python -m pip install pyserial sur powershell par ex)

# creation d'un fichier csv 
arduino_port = "COM6"
baud = 9600
fileName = "simon_data.csv"
ser = serial.Serial(arduino_port, baud)
file = open(fileName, "w")
print("Debut de l'experience...")

# ecriture des donnees depuis le serial vers le fichier csv
i=0
while (i<11):
    data=ser.readline().decode("utf-8").strip()
    file.write(data+"\n")
    i+=1

# fermeture du fichier
print("...Fin de l'experience")
file.close()

# traitement des donnees
dataCSV = pd.read_csv("simon_data.csv")
x = np.linspace(1, 10, 10)
time = dataCSV['Temps (s)']
print("Temps de reaction moyen : "+str(time.mean())+" s")
plt.plot(x, time, 'bo')
plt.xlabel("Tentative")
plt.ylabel("Temps (s)")
plt.show()