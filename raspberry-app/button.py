#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import led as LED
import sound as SOUND

# Définir les actions de chaque boutons
# présents sur l'objet connecté
def listener(value):
    # bouton 1
    if (value == "B1"):
        LED.playAnimation(2)
        print "EMMIT --> ID OBJECT_:_B1"

    # bouton 2
    if (value == "B2"):
        LED.playAnimation(3)
        print "EMMIT --> ID OBJECT_:_B2"

    # bouton 3
    if (value == "B3"):
        SOUND.play("sound1")
        print "EMMIT --> ID OBJECT_:_B3"

    # bouton 4
    if (value == "B4"):
        print "EMMIT --> ID OBJECT_:_B4"


# Main
def main():
    print "".join([
        "\033[93m", "Component: ",
        "\033[94m", "BUTTON",
        "\033[0m"
        ])

if __name__ == '__main__':
    main()
