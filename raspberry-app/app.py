#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import re
import serial
import sys
import time

import accelerometer as ACCELEROMETER
import button as BUTTON
import led as LED
import potentiometer as POTENTIOMETER
import rfid as RFID
#import socket as SOCKET
import sound as SOUND

this = sys.modules[__name__]

# définir le port serial (1: raspberry / 2: mac OS X)
#this.ser = serial.Serial(port="/dev/ttyACM0", baudrate=9600)
this.ser = serial.Serial(port="/dev/cu.usbmodem1411", baudrate=9600)
time.sleep(5)


# Afficher de manière lisible l'évenement qui a été reçu
def printEvent(component, value):
    print "".join([
        "\033[93m", "Event: ",
        "\033[94m", component,
        "\033[0m --> ",
        "\033[92m", value,
        "\033[0m"
        ])


# Lors de la réception d'un évenement, on execute
# la fonction qui est associée à celui-ci
def executeEvent(component, value):
    if (component == "ACCELEROMETER"):
        ACCELEROMETER.listener(value)
    if (component == "BUTTON"):
        BUTTON.listener(value)
    if (component == "POTENTIOMETER"):
        POTENTIOMETER.listener(value)
    if (component == "RFID"):
        RFID.listener(value)


# Lors de la réception d'un évenement, on le parse pour
# connaître le type de capteur et la valeur associée
def parseEvent(event):
    return re.search('(.*) --> (.*)', event, re.M|re.I)


# Écouter tout les evenements de notre objet
# qui sont envoyés à travers le raspberry
def eventListener():
    while 1:
        try:
            event = this.ser.readline()
            datas = parseEvent(event)
            if (datas):
                printEvent(datas.group(1).strip(), datas.group(2).strip())
                executeEvent(datas.group(1).strip(), datas.group(2).strip())
        except KeyboardInterrupt:
            print "\nPainperdu connected object \033[91m[STOPPED]\033[0m\n"
            break


# Démarrer l'objet connecté
def startPainperduConnectedObject():
    print "\nPainperdu connected object \033[92m[STARTED]\033[0m\n"

    # connexion au serveur socket.io
    print "--> Connexion au serveur socket.io"

    # écouter tout les évenements reçus
    eventListener()


# Éxecuter l'application
if __name__ == '__main__':
    startPainperduConnectedObject()
