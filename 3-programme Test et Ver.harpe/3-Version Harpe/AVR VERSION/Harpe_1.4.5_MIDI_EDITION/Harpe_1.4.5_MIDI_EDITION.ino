//release by M1r3o & Frederic Wauters
//Creative Commons CC-BY-NC-SA 2021
//Harpe_V1.4_MIDI_Edition

// Created by Frederic Wauters and Istchenko de Carvalho Marco under Creative Commons Licence CC-BY-NC-SA
// This code is delivered with no warranties and you use it at your own risks.
// Version 1.0 - 2021-03-04 - F. Wauters Belgium - M . istchenko de Carvalho France

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
// Cree par Frederic Wauters et Marco Istchenko de Carvalho sous licence Creative Commons CC-BY-NC-SA
// Ce code est fourni sans aucune garantie et vous l'utilisez a vos risques et perils.
// Version 1.0 - 2021-03-04 - F. Wauters Belgium - M . istchenko de Carvalho France
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
#include <Wire.h>
#include <Adafruit_MCP4725.h>    // DAC
Adafruit_MCP4725 dac;
#include "settings.h"
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
  pinMode(pedale_plus, INPUT);
  pinMode(pedale_moins, INPUT);
  Serial.begin(115200);
  digitalWrite(laserPin, HIGH);
  // Initialisation du DAC
  dac.begin(0x60);
   dac.setVoltage(maxX - minX, false);
  delay(3000);
  Serial.print("idle");
  digitalWrite(laserPin, LOW);
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
  dac.setVoltage(2060, false);

  // Attendre qu'on appuie sur open
  while (digitalRead(pinSensor) == LOW) {
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

      // Placer le galvo
      position_corde = (milieu - (ecart * nbCordes / 2)) + (cordeCourante * ecart);
      dac.setVoltage(position_corde, false);

      // Pause de stabilisation
      delay(pauseStabilisation);
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
      ////////////////////////////////////////////////
      pedales();
      ///////////////////////////////////////////////
      // Placer le galvo
      position_corde = (milieu - (ecart * nbCordes / 2)) + (cordeCourante * ecart);
      dac.setVoltage(position_corde + (Notes[cordeCourante][VIBRATION]), false);
      Notes[cordeCourante][VIBRATION] = -(Notes[cordeCourante][VIBRATION] / 2);
      delay(pauseStabilisation);

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
    }
  }


  // Si on a quitte la boucle, c'est qu'on a demande la fermeture

  // SEQUENCE DE FERMETURE
  // On boucle pour un ecart maximum jusque 0. L'ecart = 4095/(nbCordes-1)
  for (int ecart = (maxX - minX) / (nbCordes - 1); ecart > 0; ecart--) {
    // PLACER LE GALVO
    // On boucle sur toutes les cordes pour placer chacune
    for (int cordeCourante = 0; cordeCourante < (nbCordes - 1); cordeCourante++) {
      // Placer le galvo
      position_corde = (milieu - (ecart * nbCordes / 2)) + (cordeCourante * ecart);
       dac.setVoltage(position_corde, false);
      // Pause de stabilisation
      delay(pauseStabilisation);
    }
  }

  // Harpe fermee (et on eteint le laser)
  harpeStatut = false;
  digitalWrite(laserPin, LOW);
  laserStatut = false;                // on retient que le laser est allume

  // On est au bout du LOOP, l'Arduino va recommencer. Il attend donc qu'on appuie a nouveau sur Ouvrir...
}
