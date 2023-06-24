import serial
import csv
import time

# Définition des paramètres de communication série
port_serie = serial.Serial('/dev/ttyACM0', 9600)  # Remplacez '/dev/ttyACM0' par le port série approprié
baudrate = 9600  # Débit en bauds

# Attente de la connexion
port_serie.isOpen()  # Vérifie si le port série est ouvert

# Envoi de données
data = 'Hello, Arduino!'
port_serie.write(data.encode())  # Envoie les données encodées en bytes

# Pause
# time.sleep(1)  # Pause de 1 seconde

# Lecture des données
while True:
    if port_serie.inWaiting() > 0:  # Vérifie si des données sont disponibles
        received_data = port_serie.readline()  # Lit une ligne de données
        print("Données reçues :", received_data)
        
        # Enregistrement dans un fichier CSV
        with open('donnees.csv', 'w', newline='') as csvfile:
            writer = csv.writer(csvfile)
            writer.writerow(['Voitures nombre', received_data.decode('latin-1').strip()])

# Fermeture de la connexion série
port_serie.close()
