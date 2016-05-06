#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import led as LED
import sound as SOUND

# Définir les actions de chaque boutons
# présents sur l'objet connecté
def listener(value, socketIO):
    # bouton 1
    if (value == "B1"):
        LED.playAnimation(2)
        socketIO.emit("button", 1)

    # bouton 2
    if (value == "B2"):
        LED.playAnimation(3)
        socketIO.emit("button", 2)

    # bouton 3
    if (value == "B3"):
        SOUND.play("sound1")
        socketIO.emit("button", 3)

    # bouton 4
    if (value == "B4"):
        socketIO.emit("button", 4)


# Main
def main():
    print "".join([
        "\033[93m", "Component: ",
        "\033[94m", "BUTTON",
        "\033[0m"
        ])

if __name__ == '__main__':
    main()
