#!/usr/bin/env python
# -*- coding: UTF-8 -*-

from app import ser

# Envoyer un message à l'Arduino pour
# lancer l'animation de la LED voulu
def playAnimation(animationId):
    ser.write(str(animationId))


# Main
def main():
    print "".join([
        "\033[93m", "Component: ",
        "\033[94m", "LED",
        "\033[0m"
        ])

if __name__ == '__main__':
    main()
