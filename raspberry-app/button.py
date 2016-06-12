#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import led as LED
import sound as SOUND

# Définir les actions de chaque boutons
# présents sur l'objet connecté
def listener(value, socketIO):
    # bouton 1 (validation)
    if (value == "B1"):
        LED.playAnimation(2)
        SOUND.play("validation")
        socketIO.emit("button", 1)

    # bouton 2 (annulation)
    if (value == "B2"):
        LED.playAnimation(3)
        SOUND.play("cancel")
        socketIO.emit("button", 2)

    # bouton 3 (recherche)
    if (value == "B3"):
        LED.playAnimation(4)
        SOUND.play("search")
        socketIO.emit("button", 3)

    # bouton 4 (alliance validée)
    if (value == "B4"):
        LED.playAnimation(5)
        SOUND.play("alliance")
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
