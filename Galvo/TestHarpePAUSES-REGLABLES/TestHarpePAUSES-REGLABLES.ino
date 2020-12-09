// Librairie pour le DAC
#include <MCP4725.h>

// Declarations
MCP4725 dac(SDA, SCL);   // DAC
int nbCordes = 12;       // Nombre de cordes
int laserPin = 52;       // Laser
int stabMoins = 2;       // Bouton stabilisation -
int stabPlus = 3;        // Bouton stabilisation +
int retinMoins = 18;     // Bouton persistence retinienne -
int retinPlus = 19;      // Bouton persistence retinienne +

// Pour les pauses
int retin = 1;
int stab = 1;

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
  pinMode(laserPin, OUTPUT);    // Laser
  pinMode(stabMoins, INPUT_PULLUP);   // Bouton stabilisation -
  pinMode(stabPlus, INPUT_PULLUP);    // Bouton stabilisation +
  pinMode(retinMoins, INPUT_PULLUP);  // Bouton persistence retinienne -
  pinMode(retinPlus, INPUT_PULLUP);   // Bouton persistence retinienne +

  // Attacher les interruptions
  attachInterrupt(digitalPinToInterrupt(stabMoins), diminueStab, LOW);
  attachInterrupt(digitalPinToInterrupt(stabPlus), augmenteStab, LOW);
  attachInterrupt(digitalPinToInterrupt(retinMoins), diminueRetin, LOW);
  attachInterrupt(digitalPinToInterrupt(retinPlus), augmenteRetin, LOW);
  
  // Moniteur
  Serial.println("Config. pins et interruptions : OK");

  // S'assurer que le laser est bien eteint
  digitalWrite(laserPin, LOW);

  // Placer le scanner au milieu
  // (2048 est la moitie de 4096 => entre 0 et 5v : 2.5V => entre -5 et +5 : 0v
  dac.setValue(2048);

  // Moniteur
  Serial.println("Laser éteint et scanner au centre : OK");
}

// ********
// * Loop *  (Programme principal (boucle))
// ********
void loop() {
  // Variales de travail
  int cordeCourante=0;
  
  // Balayage de gauche a droite
  while (cordeCourante < nbCordes) {
    // Corde suivante
    cordeCourante = cordeCourante + 1;

    // Positionner le scanner
    dac.setValue(cordeCourante*(4096/nbCordes));

    // Stabilistation
    delay(stab);

    // Allumer le laser
    digitalWrite(laserPin, HIGH);

    // Persistence retinienne
    delay(retin);

    // Etindre le laser
    digitalWrite(laserPin, LOW);  
  }

  // Le balayage de gauche a droite est termine : balayage de droite a gauche    
  while (cordeCourante > 0) {
    // Corde precedente
    cordeCourante = cordeCourante - 1;

    // Positionner le scanner
    dac.setValue(cordeCourante*(4096/nbCordes));

    // Stabilistation
    delay(stab);

    // Allumer le laser
    digitalWrite(laserPin, HIGH);

    // Persistence retinienne
    delay(retin);

    // Eteindre le laser
    digitalWrite(laserPin, LOW);  
  }
}

// *****************************
// * Diminuer la stabilisation *
// *****************************
void diminueStab() {
  // Si la stabilisation est > 1
  if (stab > 1) {
    // Diminuer la stabilisation
    stab -=1;

    // Informer l'utilisateur
    Serial.println("Stab - : " + stab);
  }
}

// ******************************
// * Augmenter la stabilisation *
// ******************************
void augmenteStab() {
  // Si la stabilisation est < 100
  if (stab < 100) {
    // Diminuer la stabilisation
    stab +=1;

    // Informer l'utilisateur
    Serial.println("Stab + : " + stab);
  }
}

// **************************************
// * Diminuer la persistence retinienne *
// **************************************
void diminueRetin() {
  // Si la stabilisation est > 1
  if (retin > 1) {
    // Diminuer la stabilisation
    retin -=1;

    // Informer l'utilisateur
    Serial.println("Retin - : " + retin);
  }
}

// ***************************************
// * Augmenter la persistence retinienne *
// ***************************************
void augmenteRetin() {
  // Si la stabilisation est < 100
  if (retin < 100) {
    // Diminuer la stabilisation
    retin +=1;

    // Informer l'utilisateur
    Serial.println("Retin + : " + retin);
  }
}
