/*
 * DAC Conerter Set and test
 * -------------------------
 * 
 * EN:
 * This sketch is used to set offset and gain correctly BEFORE connecting to galvanometer controler.
 * Please read documentation associated DAC-ConvertisseurUnipolaire.pdf
 * 
 * FR :
 * Ce programme est utilisé pour régler offset et gain correctement AVANT de connecter au controlleur du galvanometre.
 * Veuillez lire la documentation associée DAC-ConvertisseurUnipolaire.pdf
 * 
 * Code & documentation by F. Wauters. (2019) Licence creative common BY-CC
 */

// Librairie pour le DAC
#include <MCP4725.h>

// Declarations
MCP4725 dac(SDA, SCL);
int laserPin = 52;
int plusPin = 8;
int moinsPin = 9;
bool Status=false;

// Configuration avant programme principal
void setup() {
  // Initialisation du DAC
  dac.begin();

  // Initialisation des pins
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, HIGH);

  // Pour les boutons tests
  pinMode(plusPin, INPUT);
  pinMode(moinsPin, INPUT);

  // Ouverture du port serie
  Serial.begin(9600);
  while (!Serial) {
  }
}

// Programme principal (boucle)
void loop() {
  // Si Plus
  if (digitalRead(plusPin)==HIGH) {
    // Si on n'etait pas encore dans cet etat
    if (Status !=true) {
      // On a change
      Serial.println("5V");
    }

    // Monter a 5V
    dac.setValue(4095);

    // Memoriser
    Status = true;
  }

  // Si Moins
  if (digitalRead(moinsPin)==HIGH) {
    if (Status !=false) {
      // On a change
      Serial.println("GND");
    }

    // Descendre a 0V
    dac.setValue(0);

    // Memoriser
    Status = false;
  }
}
