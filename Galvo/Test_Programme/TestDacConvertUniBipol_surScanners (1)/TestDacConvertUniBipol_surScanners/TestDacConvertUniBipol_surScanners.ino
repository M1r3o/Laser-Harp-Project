// Librairie pour le DAC
#include <MCP4725.h>

// Declarations
MCP4725 dac(SDA, SCL);   // DAC
int nbCordes = 12;       // Nombre de cordes
int laserPin = 52;       // Laser
int plusPin = 8;         // Bouton Plus
int moinsPin = 9;        // Bouton Moins
float Status=2047;          // Variable de travail

// *********
// * Setup *  (Configuration avant programme principal)
// *********
void setup() {
  // Ouverture du port serie (pour le debuggage dans le moniteur serie)
  Serial.begin(9600);  // Initialisation
  while (!Serial) {    // Attente initialisation ok
  }

  // Moniteur
  Serial.println("Moniteur série : OK");
    
  // Initialisation du DAC
  dac.begin();
  
  // Moniteur
  Serial.println("DAC initialisé : OK");

  // Iitialisation des pins
  
}

// ********
// * Loop *  (Programme principal (boucle))
// ********
void loop() {
  
  dac.setValue(Status);
Serial.println("2047");
delay(10000);
dac.setValue(0);
Serial.println("0");
delay(10000);
dac.setValue(4095);
Serial.println("4095");
delay(10000);
  
}
