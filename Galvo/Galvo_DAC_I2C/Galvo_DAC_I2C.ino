#include <MCP4725.h>

// Declarations
MCP4725 dac(SDA, SCL);
int nbCordes = 9;
int laserPin = 4;

// Configuration avant programme principal
void setup() {
  // Initialisation du DAC
  dac.begin();

  // Iitialisation des pins
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, HIGH);
   dac.setValue(2030);
   digitalWrite(laserPin, HIGH);
   delay(4000);
}

// Programme principal (boucle)
void loop() {
  // Variables de travail
  int laCorde = 0;
  
  // Boucler sur les cordes
  for (laCorde=0 ; laCorde<4095 ; laCorde = laCorde + (4096/nbCordes)) {
    // Valeur du dac
    dac.setValue(laCorde);

    // Pause stabilisation galvo
    delay(1);

    // Laser On
    digitalWrite(laserPin, HIGH);

    // Pause persistence retinienne
    delay (1);

    // Laser Off
    digitalWrite(laserPin, LOW);
  }
}
