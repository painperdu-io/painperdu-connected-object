#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import sys
from time import time

import led as LED
import sound as SOUND

this = sys.modules[__name__]

def init():
    this.oldtimeRFID = int(time()) - 5

# Définir les actions lorsque une
# puce RFID est détectée
def listener(value, socketIO):

    if (this.oldtimeRFID + 5 < int(time())):
        this.oldtimeRFID = int(time())
        # lire le son RFID
        SOUND.play("rfid")
        LED.playAnimation(1)

        # envoyer les valeurs au serveur
        socketIO.emit("rfid", value)
    else:
        print "EN ATTENTE RFID"


# Main
def main():
    print "".join([
        "\033[93m", "Component: ",
        "\033[94m", "RFID",
        "\033[0m"
        ])

if __name__ == '__main__':
    main()
