#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import led as LED
import sound as SOUND

# Définir les actions lorsque une
# puce RFID est détectée
def listener(value, socketIO):

    # lire le son RFID
    SOUND.play("rfid")
    LED.playAnimation(1)

    # envoyer les valeurs au serveur
    socketIO.emit("rfid", value)


# Main
def main():
    print "".join([
        "\033[93m", "Component: ",
        "\033[94m", "RFID",
        "\033[0m"
        ])

if __name__ == '__main__':
    main()
