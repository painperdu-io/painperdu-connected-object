#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import led as LED
import sound as SOUND

# Définir une quantité lorsque l'utilisateur
# actionne le potentiomètre
def listener(value, socketIO):
    SOUND.play("quantity")
    value = int(value) / 100 + 1
    socketIO.emit("potentiometer", value)


# Main
def main():
    print "".join([
        "\033[93m", "Component: ",
        "\033[94m", "POTENTIOMETER",
        "\033[0m"
        ])

if __name__ == '__main__':
    main()
