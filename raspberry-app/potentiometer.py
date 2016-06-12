#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import sys
import led as LED
import sound as SOUND

this = sys.modules[__name__]

def init():
    this.oldPOTENTIOMETER = 0

# Arrondire les valeurs en dizaine
def roundup(x):
    return int(math.ceil(x / 10.0)) * 10

# Définir une quantité lorsque l'utilisateur
# actionne le potentiomètre
def listener(value, socketIO):
    value = int(value) / 100 + 1

    if (value != this.oldPOTENTIOMETER):
        SOUND.play("quantity")
        socketIO.emit("potentiometer", value)

    this.oldPOTENTIOMETER = value


# Main
def main():
    print "".join([
        "\033[93m", "Component: ",
        "\033[94m", "POTENTIOMETER",
        "\033[0m"
        ])

if __name__ == '__main__':
    main()
