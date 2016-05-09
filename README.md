# painperdu-connected-object

### arduino-app

Branchement à effectuer sur l'Arduino Uno:
  - *Accéléromètre*: analogique --> x: 3, y: 4, z: 5
  - *Accéléromètre*: numérique --> Sleep (SL): 3, Self test (ST): 12, Zero G (0G): 8, G Select (GS): 13
  - *Bouton 1*: numérique --> 4
  - *Bouton 2*: numérique --> 5
  - *Bouton 3*: numérique --> 6
  - *Bouton 4*: numérique --> 7
  - *Module RFID*: numérique --> 2
  - *LED RGB*: numérique --> R: 9, G: 10, B: 11
  - *Potentiomètre*: analogique --> 0


### raspberry-app

Librairies python à installer:
  - [socketIO_client](https://pypi.python.org/pypi/socketIO-client)
  - [PyAudio](https://pypi.python.org/pypi/PyAudio)
