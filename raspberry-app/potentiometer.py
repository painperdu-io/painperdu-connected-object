#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import led as LED

# Définir une quantité lorsque l'utilisateur
# actionne le potentiomètre
def listener(value):
    LED.playAnimation(4)
    value = int(value) / 100 + 1
    print "EMMIT --> ID OBJECT POTENTIOMETER %i" % value


# Main
def main():
    print "".join([
        "\033[93m", "Component: ",
        "\033[94m", "POTENTIOMETER",
        "\033[0m"
        ])

if __name__ == '__main__':
    main()
