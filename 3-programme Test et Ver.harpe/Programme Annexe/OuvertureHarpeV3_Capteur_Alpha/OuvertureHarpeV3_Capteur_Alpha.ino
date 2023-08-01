// Petit cours Arduino pour Marco...
// ---------------------------------
// En dehors de tous les coide, on peut faire les déclarations qui servent a toutes les fonctions
// et importer les eventuelles librairies necessaires.
//
// Les lignes de commentaires commencent par "//" et ne sont pas prises en compte
// par le programme ni par le compilateur. Ils ne servent qu'aux developpeurs.
//
// Tous programmes Arduino doit au moins avoir un void setup et un void loop.
// Attention : il faut toujours respecter la casse !
//-------------------------------------------------------------------------------------------------------

// Librairie pour le DAC
#include <MCP4725.h>
#include <MIDIUSB.h>
// Declarations
MCP4725 dac(SDA, SCL);    // DAC
int laserPin = 4;         // COntrole Laser
int boutonOpen = 3;      // Bouton ouverture
int boutonClose = 4;     // Bouton fermeture
int nbCordes = 14;         // Nombre de cordes
bool harpeStatut = false; // Statut (ouverte/fermee)
bool laserStatut = false; // Statut laser (on/off)
int Pin_Sensor_Note = 3 ;
unsigned long Delay_Motor = 2;
int LDR_Sensor_Note = 450;//ce n'est qu'une valeur que j'ai choisie 

// Pour les pauses : a modifier en fonction de tes propres servos
int pauseStabilisation = 1;
int pausePersistence = 1;

// Pour le debattement de la harpe
int minX = 1129;
int maxX = 3237;

// Variables de travail
int ecart = 0;

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

// *********
// * SETUP *
// *********
void setup() {
  // Le Setup sert principalement a configurer et
  // a initialiser le diverses choses qui regissent le projet.
  // Si on y fait tourner autre chose, c'est pour "preparer le terrain", rien d'autre
  Serial.begin(115200);
  // Initialisation des pins
  pinMode(laserPin, OUTPUT);
  pinMode(boutonOpen, INPUT);
  pinMode(boutonClose, INPUT);

  // S'assurer que le laser est eteint
  digitalWrite(laserPin, LOW);

  // Initialisation du DAC
  dac.begin();

  dac.setValue(1129);
  delay(500);
  dac.setValue(2047);
  delay(500);
  dac.setValue(3237);
  delay(500);
  dac.setValue(2047);
  delay(1000);
}

// ****************
// * Lecture Note *
// ****************

void loop() {
  // Le loop est la partie qui est "rejouee" en permanence par l'Arduino.
  // C'est la raison de son nom. Lorsque tou y a ete execute, il recommence.

  dac.setValue(2047);

  // Attendre qu'on appuie sur open
  while (digitalRead(boutonOpen) == LOW) {
    // On ne fait rien, on attend qu'on appuie
    // Cette boucle tourne tant que le bouton open n'est pas enfonce
  }

  // On a appuie, on allume le laser
  digitalWrite(laserPin, HIGH);
  laserStatut = true;                // on retient que le laser est allume

  // On attend un peu pour l'effet... enfin, si on veut
  delay(1000);

  // SEQUENCE D'OUVERTURE
  // On boucle pour un ecart de 0 jusque maximum. L'ecart = 4095/(nbCordes-1)
  for (int ecart = 0; ecart < ((maxX - minX) / (nbCordes - 1)); ecart++) {
    // PLACER LE GALVO
    // On boucle sur toutes les cordes pour placer chacune
    for (int cordeCourante = 0; cordeCourante < (nbCordes - 1); cordeCourante++) {
      // Eteindre le laser
      digitalWrite(laserPin, LOW);
      laserStatut = false;

      // Placer le galvo
      dac.setValue((2047 - (ecart * nbCordes / 2)) + (cordeCourante * ecart));

      // Pause de stabilisation
     delay(pauseStabilisation);

    }

    // Allumer le laser
    digitalWrite(laserPin, HIGH);
    laserStatut = true;

    // Pause persistence
    delay(pausePersistence);

    // La harpe est ouverte, on le retient
    harpeStatut =  true;

    // Attendre qu'on appuie sur open
    while (digitalRead(boutonOpen) == LOW) {
      // Ecart
      ecart = (maxX - minX) / (nbCordes - 1);

      // En attendant qu'on demande la fermeture, on dessine la harpe et ses faisceaux bien sur...
      // On boucle sur toutes les cordes pour placer chacune
      for (int cordeCourante = 0; cordeCourante < (nbCordes - 1); cordeCourante++) {
        // Eteindre le laser
        digitalWrite(laserPin, LOW);
        laserStatut = false;

        // Placer le galvo
        dac.setValue((2047 - (ecart * nbCordes / 2)) + (cordeCourante * ecart));

        // Pause de stabilisation
         while (millis() - temps0 < Delay_Motor) {
        //digitalWrite(PinLaser , HIGH);
        if (analogRead(Pin_Sensor_Note) > LDR_Sensor_Note ) {
          noteOn(0, 48 + cordeCourante, 64);
          MidiUSB.flush();
          delay(250) ;
         


        } else {
          noteOff(0, 48 + cordeCourante, 64); // Channel 0, middle C, normal velocity
          MidiUSB.flush();

        }

      }


        // Allumer le laser
        digitalWrite(laserPin, HIGH);
        laserStatut = true;
        //mettre Note MIDI
        // Pause persistence
        delay(pausePersistence);
      }
    }

    // Si on a quitte la boucle, c'est qu'on a demande la fermeture

    // SEQUENCE DE FERMETURE
    // On boucle pour un ecart maximum jusque 0. L'ecart = 4095/(nbCordes-1)
    for (int ecart = (maxX - minX) / (nbCordes - 1); ecart > 0; ecart--) {
      // PLACER LE GALVO
      // On boucle sur toutes les cordes pour placer chacune
      for (int cordeCourante = 0; cordeCourante < (nbCordes - 1); cordeCourante++) {
        // Eteindre le laser
        digitalWrite(laserPin, LOW);
        laserStatut = false;

        // Placer le galvo
        dac.setValue((2047 - (ecart * nbCordes / 2)) + (cordeCourante * ecart));

        // Pause de stabilisation
        delay(pauseStabilisation);

        // Allumer le laser
        digitalWrite(laserPin, HIGH);
        laserStatut = true;

        // Pause persistence
        delay(pausePersistence);
      }
    }


  }
  // Harpe fermee (et on eteint le laser)
  harpeStatut = false;
  digitalWrite(laserPin, LOW);
  laserStatut = false;                // on retient que le laser est allume

  // On est au bout du LOOP, l'Arduino va recommencer. Il attend donc qu'on appuie a nouveau sur Ouvrir...
}
