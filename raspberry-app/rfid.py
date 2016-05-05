#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import led as LED

# Définir les actions lorsque une
# puce RFID est détectée
def listener(value):
    LED.playAnimation(1)
    print "EMMIT --> RFID %s" % value


# Main
def main():
    print "".join([
        "\033[93m", "Component: ",
        "\033[94m", "RFID",
        "\033[0m"
        ])

if __name__ == '__main__':
    main()
