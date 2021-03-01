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

// Library for the DAC
// Librairie pour le DAC 
#include <MCP4725.h>

// Declarations
MCP4725 dac(SDA, SCL);
int plusPin = 9;
int moinsPin = 8;
bool Status=false;

// *******************************************
// *       Setup before main program         *
// * Configuration avant programme principal *
// *******************************************
void setup() {
  // Initializing the DAC
  // Initialisation du DAC
  dac.begin();

  // For testing buttons
  // Pour les boutons tests
  pinMode(plusPin, INPUT);
  pinMode(moinsPin, INPUT);

  // Opening serial port
  // Ouverture du port serie
  Serial.begin(9600);
  while (!Serial) {
  }
}

// ********************************
// *        Main program          *
// * Programme principal (boucle) *
// ********************************
void loop() {
  // If click on the PLUS button
  // Si clic sur le bouton PLUS
  if (digitalRead(plusPin)==HIGH) {
    // If not actually at this state
    // Si on n'etait pas encore dans cet etat
    if (Status !=true) {
      // Change status
      // On a change
      Serial.println("5V");

      // Memorize
      // Memoriser
      Status = true;
    }

    // Go to 5V
    // Monter a 5V
    dac.setValue(4095);
  }

  // If click on the MINUS button
  // Si clic sur le bouton MOINS
  if (digitalRead(moinsPin)==HIGH) {
    // If not actually in this state
    // Si on n'etait pas encore dans cet etat
    if (Status !=false) {
      // Change status
      // On a change
      Serial.println("GND");
 
      // Memorize
      // Memoriser
      Status = false;
    }

    // Go to 0V
    // Descendre a 0V
    dac.setValue(0);
  }  
}
