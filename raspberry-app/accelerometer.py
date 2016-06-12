#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import math
import re
import sys
from time import time

this = sys.modules[__name__]

def init():
    this.x = 0
    this.y = 0
    this.z = 0
    this.oldtimeACCELEROMETER = int(time()) - 60


# Définir si la porte du frigo
# est en train d'être ouverte
def listener(value, socketIO):
    data = re.search('(.*),(.*),(.*)', value, re.M|re.I)
    x = int(data.group(1).strip())
    y = int(data.group(2).strip())
    z = int(data.group(3).strip())

    if (math.fabs(x - this.x) > 10 and
        math.fabs(y - this.y) > 10 and
        math.fabs(z - this.z) > 10 and
        this.oldtimeACCELEROMETER + 60 < int(time())):
        this.oldtimeACCELEROMETER = int(time())
        socketIO.emit("accelerometer")

    # enregistrer les valeurs x,y,z
    this.x = x
    this.y = y
    this.z = z


# Main
def main():
    print "".join([
        "\033[93m", "Component: ",
        "\033[94m", "ACCELEROMETER",
        "\033[0m"
        ])

if __name__ == '__main__':
    main()
