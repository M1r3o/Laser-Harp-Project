//release by M1r3o & Frederic Wauters
//Creative Commons CC-BY-NC-SA 2021
//Harpe_V1.5_MIDI_Edition

// Created by Frederic Wauters and Istchenko de Carvalho Marco under Creative Commons Licence CC-BY-NC
// This code is delivered with no warranties and you use it at your own risks.
// Version 1.0 - 2021-03-04 - F. Wauters Belgium

// PLEASE READ THIS IMPORTANT NOTICE
// SVP LISEZ CETTE NOTE IMPORTANTE
//
// About CC-BY-NC-SA...
// -----------------
// You CAN    : share, copy, redistribute, adapt, remix, transform and build using
//              the code.
//
// You CANNOT : use for commercial purposes.
//
// You CANNOT : apply legal terms or technological measures that legally restrict
//              others from doing anything the license permits.
//
// You MUST   : give appropriate credit, provide a link to the license, and indicate
//              if changes were made. You may do so in any reasonable manner, but not
//              in any way that suggests the licensor endorses you or your use.
//
// Complete informations about CC-BY-NC-SA licence :
//    https://creativecommons.org/licenses/by-nc-sa/2.0/be/deed.en
// Cree par Frederic Wauters et Marco Istchenko de Carvalho sous licence Creative Commons CC-BY-NC
// Ce code est fourni sans aucune garantie et vous l'utilisez a vos risques et perils.
// Version 1.0 - 2021-03-04 - F. Wauters Belgium
//
// A propos de CC-BY-NC-SA
// --------------------
// Vous POUVEZ        : partager, copier, distribuer et communiquer le code par tous
//                      moyens et sous tous formats.
//
// Vous NE POUVEZ PAS : faire un usage commercial de ce code, tout ou partie le composant.
//
// Vous NE POUVEZ PAS : appliquer des conditions legales ou des mesures techniques qui
//                      restreindraient legalement autrui a utiliser le code dans les
//                      conditions decrites par la licence.
//
// Vous DEVEZ         : crediter le code, integrer un lien vers la licence et indiquer si
//                      des modifications ont ete effectuees au code. Vous devez indiquer
//                      ces informations par tous les moyens raisonnables, sans toutefois
//                      suggerer que l'Offrant vous soutient ou soutient la facon dont vous
//                      avez utilise son travail.
//
// Informations complètes concernant la licence CC-BY-NC-SA :
//    https://creativecommons.org/licenses/by-nc-sa/2.0/be/deed.fr


// /!\ to send notes , we have configured serial protocol to 115200 Bytes/seconds
// we used to send MIDI notes : Hairless MIDI Serial (to send MIDI notes from Arduino to Standalone Synthesizer via USB->MIDI converter)
// Enter into setup and choose 115200 bauds rates
// to change option (actually vibration corde and reverse mode for note, go to "settings.h"
// (: enjoy :)

//////////////////////////////
////////dependance///////////
#include <MCP4725.h>
#include "settings.h"
#include "tools.h"
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
      dac.setValue(position_corde + (Notes[cordeCourante][VIBRATION]));
      Notes[cordeCourante][VIBRATION] = -(Notes[cordeCourante][VIBRATION] / 2);
      delay(pauseStabilisation);

      // Allumer le laser
      digitalWrite(laserPin, HIGH);
      laserStatut = true;
     
      if (digitalRead(buttonLevelSensor) == HIGH) { // cette partie la traite de la detection de la hauteur de main avec le TSL 257
        variation = analogRead(A0) ;// detection de la hauteur de 0 a 5V sur un CAN de 10 bit 
        variation = variation/8; //conversion CAN 10 Bits vers 7 Bits
        Notes[cordeCourante][VARIATION] = 0 + variation ; // sur le sustain (intensité de la note) de la note joué, enregistrement et actualisation a chaque balayage du faisceaux
        variationHand(Notes[cordeCourante][NOTE_MIDI], Notes[cordeCourante][VARIATION]);//ModWheel sur la note concerné 
      }
      else {
        Notes[cordeCourante][VARIATION] = 127 ;
      }
      if (digitalRead(pinSensor) == true && Notes[cordeCourante][FLAGON] == 0) {// Si la note etait jusqu'ici Off et que la detection pour la corde desire est faite
        // Il faut jouer la note (MIDI)
        noteOn(Notes[cordeCourante][NOTE_MIDI]);
        // On memorise que cette corde joue , pour ne pas la rejouer(diiiiing,diiiing,diiiiing, (2eme condition If)
        //ont tient la note (allumee), jusqu'a ce qu'on retire la main
        Notes[cordeCourante][FLAGON] = 1;
        Notes[cordeCourante][VIBRATION] = cordeVibration ;
      }
      
      else if (digitalRead(pinSensor) == false && Notes[cordeCourante][FLAGON] == 1 ) {// Si la note etait jusqu'ici ON et que la detection pour la corde desire n'est plus satisfaite
        // Il faut arreter ,ou, ne pas de jouer la note (MIDI)
        //memoriser que cette note n'est plus jouee
        // On memorise que cette corde ne joue pas
        noteOff(Notes[cordeCourante][NOTE_MIDI]); // on envoie une note mais ayant une velocite de 0 , donc elle ne sera pas joue
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
