/**
 * PAIN PERDU
 * --
 * Gestion de l'objet connecté
 */

// definir les entrées/sorties utilisés
#define PIN_LED_RED   9
#define PIN_LED_GREEN 10
#define PIN_LED_BLUE  11
#define PIN_POTENTIOMETER 0
#define PIN_ACCELEROMETER_X 3
#define PIN_ACCELEROMETER_Y 4
#define PIN_ACCELEROMETER_Z 5
#define PIN_BUTTON_1 4
#define PIN_BUTTON_2 5
#define PIN_BUTTON_3 6
#define PIN_BUTTON_4 7

// SoftwareSerial pour le RFID
#include <SoftwareSerial.h>
SoftwareSerial RFID = SoftwareSerial(2, 3);

// definir les tableaux de couleurs RGB
int RGB_RED[]     = {255, 0, 0};
int RGB_GREEN[]   = {0, 255, 0};
int RGB_BLUE[]    = {0, 0, 255};
int RGB_YELLOW[]  = {255, 255, 0};
int RGB_MAGENTA[] = {255, 0, 255};
int RGB_CYAN[]    = {0, 255, 255};
int RGB_WHITE[]   = {255, 255, 255};

// définir les variations de couleurs primaires
int FROM_RGB_RED_TO_RGB_GREEN[]  = {255, 0, 0, 0, 255, 0};
int FROM_RGB_RED_TO_RGB_BLUE[]   = {255, 0, 0, 0, 0, 255};
int FROM_RGB_GREEN_TO_RGB_RED[]  = {0, 255, 0, 255, 0, 0};
int FROM_RGB_GREEN_TO_RGB_BLUE[] = {0, 255, 0, 0, 0, 255};
int FROM_RGB_BLUE_TO_RGB_RED[]   = {0, 0, 255, 255, 0, 0};
int FROM_RGB_BLUE_TO_RGB_GREEN[] = {0, 0, 255, 0, 255, 0};

// initialisation des variables
String tag;
int potentiometer = 0;
int x = 0;
int y = 0;
int z = 0;
int ledAnimID = 0;


/**
 * -- SETUP --
 */
void setup()
{
  Serial.begin(9600);
  Serial.println("Serial Ready");

  RFID.begin(9600);
  Serial.println("RFID Ready");

  // définir les sorties de la LED
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);

  // définir les entrées des bouttons
  pinMode(PIN_BUTTON_1, INPUT);
  pinMode(PIN_BUTTON_2, INPUT);
  pinMode(PIN_BUTTON_3, INPUT);
  pinMode(PIN_BUTTON_4, INPUT);

  // éteindre la LED
  setRGBColor(0, 0, 0);
}


/**
 * -- VOID --
 */
void loop()
{
  // buttons
  getButtonsState();

  // RFID
  getRFIDModuleValue();

  // potentiometre
  getPotentiometerValue();

  // accelerometre
  getAccelerometreValue();

  // events
  ledEventListener();
}


/**
 * -----------------------------------------------------------------------------
 * -- BOUTTONS
 * -----------------------------------------------------------------------------
 */
void getButtonsState()
{
  // récupérer les valeurs des bouttons
  int button1 = digitalRead(PIN_BUTTON_1);
  int button2 = digitalRead(PIN_BUTTON_2);
  int button3 = digitalRead(PIN_BUTTON_3);
  int button4 = digitalRead(PIN_BUTTON_4);

  // boutton 1
  if (button1 == HIGH) {
    Serial.println("BUTTON --> B1");
  }

  // boutton 2
  if (button2 == HIGH) {
    Serial.println("BUTTON --> B2");
  }

  // boutton 3
  if (button3 == HIGH) {
    Serial.println("BUTTON --> B3");
  }

  // boutton 4
  if (button4 == HIGH) {
    Serial.println("BUTTON --> B4");
  }
}


/**
 * -----------------------------------------------------------------------------
 * -- POTENTIOMETRE
 * -----------------------------------------------------------------------------
 */

/**
 * Retourner la valeur du potentiometre afin qu'elle
 * puisse être traitée par le RaspberryPI
 */
void getPotentiometerValue()
{
  int value;

  // récupére la valeur du potentiometre
  value = analogRead(PIN_POTENTIOMETER);

  // définir une valeur maximale
  if (value > 1000) value = 1000;

  // retourner la valeur du potentiomètre
  // pour la traiter avec le RaspberryPI
  if (potentiometer < value -5 || potentiometer > value + 5) {
    Serial.print("POTENTIOMETER --> ");
    Serial.println(value);
    potentiometer = value;
  }
}


/**
 * -----------------------------------------------------------------------------
 * -- RFID
 * -----------------------------------------------------------------------------
 */

 /**
  * Retourner l'ID de la puce RFID afin qu'il
  * puisse être traité par le RaspberryPI
  */
void getRFIDModuleValue()
{
  char c;
  while(RFID.available() > 0){
    c=RFID.read();
    tag += c;
  }
  tag=tag.substring(1,13);

  while(tag.length() > 0) {
    Serial.print("RFID --> ");
    Serial.println(tag);
    tag = "";
  }
  delay(500);
}


/**
 * -----------------------------------------------------------------------------
 * -- ACCELEROMETRE
 * -----------------------------------------------------------------------------
 */

/**
 * Retourner la valeur de l'accélèromètre afin
 * qu'elle puisse être traitée par le RaspberryPI
 */
 void getAccelerometreValue()
 {
   // récupérer les valeurs de l'accélèromètre
   x = analogRead(PIN_ACCELEROMETER_X);
   y = analogRead(PIN_ACCELEROMETER_Y);
   z = analogRead(PIN_ACCELEROMETER_Z);

   // retourner la valeur de l'accélèromètre
   // pour la traiter avec le RaspberryPI
   Serial.print("ACCELEROMETER --> ");
   Serial.print(x);
   Serial.print(",");
   Serial.print(y);
   Serial.print(",");
   Serial.println(z);
 }

/**
 * -----------------------------------------------------------------------------
 * -- LED
 * -----------------------------------------------------------------------------
 */

/**
 * Récupérer et analyser les évenements pour la LED 
 * envoyés par le Raspberry
 */
void ledEventListener()
{
  if (Serial.available())  {
    ledAnimID = Serial.read() - '0';

    // définitions des paramètres des animations
    int anim1Params[] = {5};
    int anim2Params[] = {300, 75};
    int anim3Params[] = {300, 75};
    int anim4Params[] = {150, 0};

    // jouer l'animation
    switch (ledAnimID) {
      case 1:
        playLEDAnimation(1, "color", FROM_RGB_BLUE_TO_RGB_GREEN, anim1Params);
        setRGBColor(0, 0, 0);
        break;
        
      case 2: 
        playLEDAnimation(3, "blink", RGB_GREEN, anim2Params);
        break;

      case 3: 
        playLEDAnimation(3, "blink", RGB_RED, anim3Params);
        break;

      case 4: 
        playLEDAnimation(1, "blink", RGB_BLUE, anim4Params);
        break;
    }
  }
}


/**
 * Jouer une animation sur la LED
 *
 * @param integer loop        nombre de fois que l'animation est joué (-1 si infini)
 * @param String  animation   nom de l'animation qui doit être joué
 * @param integer color[]     tableau des 3 couleurs RGB (de 0 à 255)
 * @param integer params[]    tableau de paramètres de l'anomation
 */
void playLEDAnimation(int loop, String animation, int color[], int params[])
{
  int i = 0;
  if (loop == -1) {
    while(true) {
      loadLEDAnimation(animation, color, params);
    }
  }
  else {
    for (i = 0 ; i < loop ; i++) {
      loadLEDAnimation(animation, color, params);
    }
  }
}

/**
 * Charger une animation pour la LED
 *
 * @param String  animation   nom de l'animation qui doit être joué
 * @param integer color[]     tableau des 3 couleurs RGB (de 0 à 255)
 * @param integer params[]    tableau de paramètres de l'anomation
 */
void loadLEDAnimation(String animation, int color[], int params[])
{
  if (animation == "blink") {
    animationBlinkLED(color, params);
  }
  if (animation == "color") {
    animationColorLED(color, params);
  }
  if (animation == "fade") {
    animationFadeLED(color, params);
  }
}

/**
 * Définir la couleur rouge de la LED
 *
 * @param integer red   variation de couleur de 0 à 255
 */
void setRedColor(int red)
{
  analogWrite(PIN_LED_RED, 255 - red);
}

/**
 * Définir la couleur verte de la LED
 *
 * @param integer green   variation de couleur de 0 à 255
 */
void setGreenColor(int green)
{
  analogWrite(PIN_LED_GREEN, 255 - green);
}

/**
 * Définir la couleur bleu de la LED
 *
 * @param integer blue    variation de couleur de 0 à 255
 */
void setBlueColor(int blue)
{
  analogWrite(PIN_LED_BLUE, 255 - blue);
}

/**
 * Définir la couleur RGB de la LED
 *
 * @param integer red     variation de couleur de 0 à 255
 * @param integer green   variation de couleur de 0 à 255
 * @param integer blue    variation de couleur de 0 à 255
 */
void setRGBColor(int red, int green, int blue)
{
  setRedColor(red);
  setGreenColor(green);
  setBlueColor(blue);
}

/**
 * Animation : clignotement de la LED
 *
 * @param integer color[]     tableau des 3 couleurs RGB (de 0 à 255)
 * @param integer params[]    tableau de paramètres pour les timers
 */
void animationBlinkLED(int color[], int params[])
{
  setRGBColor(color[0], color[1], color[2]);
  delay(params[0]);
  setRGBColor(0, 0, 0);
  delay(params[1]);
}

/**
 * Animation : effet de fade in / fade out de la LED
 *
 * @param integer color[]     tableau des 3 couleurs RGB (de 0 à 255)
 * @param integer params[]    tableau de paramètres pour les timers
 */
void animationFadeLED(int color[], int params[])
{
  int i;
  int initRed   = color[0];
  int initGreen = color[1];
  int initBlue  = color[2];
  int incRed    = (color[0] == 0) ? 0 : -1;
  int incGreen  = (color[1] == 0) ? 0 : -1;
  int incBlue   = (color[2] == 0) ? 0 : -1;

  // initialiser et éteindre la LED
  color[0] = 0;
  color[1] = 0;
  color[2] = 0;
  setRGBColor(color[0], color[1], color[2]);

  // réaliser l'effet de fade in / fade out
  for (i = 0 ; i < 510 ; i++) {

    // changer le sens d'incrementation
    if (color[0] == 0 || color[0] == 255) {
      incRed = -incRed;
    }
    if (color[1] == 0 || color[1] == 255) {
      incGreen = -incGreen;
    }
    if (color[2] == 0 || color[2] == 255) {
      incBlue = -incBlue;
    }

    // mettre à jour la couleur
    color[0] += incRed;
    color[1] += incGreen;
    color[2] += incBlue;
    setRGBColor(color[0], color[1], color[2]);

    // effet sur la variation
    delay(params[0]);
  }

  // redéfinir la couleur d'origine
  color[0] = initRed;
  color[1] = initGreen;
  color[2] = initBlue;

  // délai avant une nouvelle animation
  delay(params[1]);
}

/**
 * Animation : Changer la couleur de la LED d'une
 * couleur primaire à une autre avec variation.
 *
 * @param integer color[]     tableau des 6 couleurs RGB (de 0 à 255) --> from(3) et to(3)
 * @param integer params[]    tableau de paramètres pour les timers
 */
void animationColorLED(int colors[], int params[])
{
  int i;
  int red;
  int green;
  int blue;

  // initialiser les couleurs primaires
  red   = (colors[0] == 255 && colors[1] == 0 && colors[2] == 0) ? 255 : 0;
  green = (colors[0] == 0 && colors[1] == 255 && colors[2] == 0) ? 255 : 0;
  blue  = (colors[0] == 0 && colors[1] == 0 && colors[2] == 255) ? 255 : 0;

  // passer d'une couleur primaire à une autre
  for (i = 0; i < 255; i += 1) {

    // color from
    if (colors[0] == 255 && colors[1] == 0 && colors[2] == 0) red -= 1;
    if (colors[0] == 0 && colors[1] == 255 && colors[2] == 0) green -= 1;
    if (colors[0] == 0 && colors[1] == 0 && colors[2] == 255) blue -= 1;

    // color to
    if (colors[3] == 255 && colors[4] == 0 && colors[5] == 0) red += 1;
    if (colors[3] == 0 && colors[4] == 255 && colors[5] == 0) green += 1;
    if (colors[3] == 0 && colors[4] == 0 && colors[5] == 255) blue += 1;

    // varier les couleurs primaires
    if ((colors[0] == 255 && colors[1] == 0 && colors[2] == 0) ||
        (colors[3] == 255 && colors[4] == 0 && colors[5] == 0)) {
      setRedColor(red);
    }
    if ((colors[0] == 0 && colors[1] == 255 && colors[2] == 0) ||
        (colors[3] == 0 && colors[4] == 255 && colors[5] == 0)) {
      setGreenColor(green);
    }
    if ((colors[0] == 0 && colors[1] == 0 && colors[2] == 255) ||
        (colors[3] == 0 && colors[4] == 0 && colors[5] == 255)) {
      setBlueColor(blue);
    }

    // attendre entre chaque variation
    delay(params[0]);
  }
}
