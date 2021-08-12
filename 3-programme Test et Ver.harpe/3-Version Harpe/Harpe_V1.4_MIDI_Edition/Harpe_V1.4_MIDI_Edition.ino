//release by M1r3o & Frederic Wauters
//Creative Commons CC by SA 2021
//Harpe_V1.3.1_MIDI_Edition

// /!\ to send notes , we have configured serial protocol to 115200 Bytes/seconds
// we used to send MIDI notes : Hairless MIDI Serial (to send MIDI notes from Arduino to Standalone Synthesizer via USB->MIDI converter)
// Enter into setup and choose 115200 bauds rates
// to change option (actually vibration corde and reverse mode for note, go to "settings.h"
// (: enjoy :)

//////////////////////////////
////////dependance///////////
#include <MCP4725.h>
#include "settings.h"
MCP4725 dac(SDA, SCL);    // DAC
// *********
// * SETUP *
// *********
void setup() {
  // Le Setup sert principalement a configurer et
  // a initialiser le diverses choses qui regissent le projet.
  // Si on y fait tourner autre chose, c'est pour "preparer le terrain", rien d'autre
  // Initialisation des pins
  pinMode(laserPin, OUTPUT);
  pinMode(boutonOpen, INPUT);
  pinMode(boutonClose, INPUT);
  pinMode(pinSensor , INPUT);
  Serial.begin(115200);

  // S'assurer que le laser est eteint
  digitalWrite(laserPin, LOW);

  // Initialisation du DAC
  dac.begin();
  dac.setValue(maxX - minX);
  delay(1000);
  Serial.print("idle");
}

// ********
// * LOOP *
// ********
void loop() {
  // Le loop est la partie qui est "rejouee" en permanence par l'Arduino.
  // C'est la raison de son nom. Lorsque tout y a ete execute, il recommence.
  reverse();
  vibration();
  //Serial.println(NOTE_MIDI);
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
      position_corde = (milieu - (ecart * nbCordes / 2)) + (cordeCourante * ecart);
      dac.setValue(position_corde);

      // Pause de stabilisation
      delay(pauseStabilisation);

      // Allumer le laser
      digitalWrite(laserPin, HIGH);
      laserStatut = true;

      // Pause persistence
      delay(pausePersistence);
    }
  }

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
      position_corde = (milieu - (ecart * nbCordes / 2)) + (cordeCourante * ecart);
      dac.setValue(position_corde+(Notes[cordeCourante][VIBRATION]));
      Notes[cordeCourante][VIBRATION] =-(Notes[cordeCourante][VIBRATION]/2);
      delay(pauseStabilisation);

      // Allumer le laser
      digitalWrite(laserPin, HIGH);
      laserStatut = true;
      if (digitalRead(pinSensor) == true && Notes[cordeCourante][FLAGON] == 0) {// Si la note etait jusqu'ici Off et que la detection pour la corde desire est faite
        // Il faut jouer la note (MIDI)
        noteOn(0x90, Notes[cordeCourante][NOTE_MIDI], 127);
        // On memorise que cette corde joue , pour ne pas la rejouer(diiiiing,diiiing,diiiiing, (2eme condition If)
        //ont tient la note (allumee), jusqu'a ce qu'on retire la main
        Notes[cordeCourante][FLAGON] = 1;
        Notes[cordeCourante][VIBRATION] = cordeVibration ; 
      }

      else if (digitalRead(pinSensor) == false && Notes[cordeCourante][FLAGON] == 1 ) {// Si la note etait jusqu'ici ON et que la detection pour la corde desire n'est plus satisfaite
        // Il faut arreter ,ou, ne pas de jouer la note (MIDI)
        //memoriser que cette note n'est plus jouee
        // On memorise que cette corde ne joue pas
        noteOn(0x90, Notes[cordeCourante][NOTE_MIDI], 0); // on envoie une note mais ayant une velocite de 0 , donc elle ne sera pas joue
        Notes[cordeCourante][FLAGON] = 0 ;
        



      }

      delay(pausePersistence);

    }
    delay(pausePersistence);
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
      position_corde = (milieu - (ecart * nbCordes / 2)) + (cordeCourante * ecart);
      dac.setValue(position_corde);

      // Pause de stabilisation
      delay(pauseStabilisation);

      // Allumer le laser
      digitalWrite(laserPin, HIGH);
      laserStatut = true;

      // Pause persistence
      delay(pausePersistence);
    }
  }

  // Harpe fermee (et on eteint le laser)
  harpeStatut = false;
  digitalWrite(laserPin, LOW);
  laserStatut = false;                // on retient que le laser est allume

  // On est au bout du LOOP, l'Arduino va recommencer. Il attend donc qu'on appuie a nouveau sur Ouvrir...
}
