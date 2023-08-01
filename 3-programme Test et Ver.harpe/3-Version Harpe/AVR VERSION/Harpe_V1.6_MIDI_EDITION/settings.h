//release by M1r3o & Frederic Wauters
//Creative Commons CC-BY-NC-SA 2021
//Harpe_V1.6_MIDI_Edition

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




/*
***********
--OPTION--
************
*/
#include"noteMIDI.h"


//Pour activer ou désactiver une option, saisisez 1 pour activer ou 0 pour desactiver
boolean NOTE_MIDI_REVERSE = 1 ;
boolean VIBRATION_CORDE = 1 ;
int EffetMain = 0 ; // 0 = désactivé 1 = Modwheel 2 = aftertouch 3 = pitch bend 
/*
********************************************************
--NE PAS TOUCHER LES VARIABLES ET FONCTION QUI SUIVENT--
--TABLEAU DES NOTES ET VIBRATION--
********************************************************
*/
int Notes[12][5] = {
  {0, note12, note1, 0, 127},
  {0, note11, note2, 0, 127},
  {0, note10, note3, 0, 127},
  {0, note9, note4, 0, 127},
  {0, note8, note5, 0, 127},
  {0, note7, note6, 0, 127},
  {0, note6, note7, 0, 127},
  {0, note5, note8, 0, 127},
  {0, note4, note9, 0, 127},
  {0, note3, note10, 0, 127},
  {0, note2, note11, 0, 127},
  {0, note1, note12, 0, 127}
};
const int FLAGON = 0;
//const int NOTEMIDI_REVERSE = 1; voir au niveau des options
//const int NOTEMIDI_NORMAL = 2 ; voir au niveau des options 
int NOTE_MIDI = 0 ; 
//
const int VIBRATION = 3 ;
const int VARIATION = 4;
int cordeVibration = 0;
//
/*
**************************************
  --variable de travail de la harpe--
**************************************
 */
int minX = 400;
int maxX = 4000;   
int nbCordes = 10;         // Nombre de cordes
bool harpeStatut = false; // Statut (ouverte/fermee)
bool laserStatut = false; // Statut laser (on/off)
int milieu = 2400 ;
/*
 ***********************
  --Pin carte arduino--
 ***********************
 */
 int pinSensor = 10 ;
 int boutonClose = 9; // Bouton ouverture   
 int boutonOpen = 9;// Bouton fermeture 
 int laserPin = 4; 
 int buttonLevelSensor = 5 ; 
 int pinAnalogSensor = A0 ; 
/*
*************************
--Variables de travail--
************************* 
*/
int ecart = 0;
float position_corde = 0 ;
// Pour les pauses : a modifier en fonction de tes propres galvo
int pauseStabilisation = 1;
int pausePersistence = 1;
boolean etat = 0 ;
int variation = 0 ; 
int adresseMIDIeffet = 0 ; 
/*
************
* --OPTION--
************
*/
// 1-REVERSE MODE DES NOTES
void reverse() {
  if (NOTE_MIDI_REVERSE == 0) {
     NOTE_MIDI = 2 ;
  }
  else {
     NOTE_MIDI = 1 ;
  }
}
//2 VIBRATION CORDE
void vibration() {
  if (VIBRATION_CORDE == 0) {
     cordeVibration = 0 ;
  }
  else {
     cordeVibration = 100 ;
  }
}
// 3 EFFET DE LA HAUTEUR DE LA MAIN

void HauteurMain() {
  if (EffetMain == 0) { //desactivé
    adresseMIDIeffet = 0;
  }
  else if (EffetMain == 1) { // modwheel
    adresseMIDIeffet = 0xB0 ;
  }
  else if (EffetMain == 2) { // aftertouch
    adresseMIDIeffet = 0xA0 ;
  }
  else if (EffetMain == 3) { // pitch bend
    adresseMIDIeffet = 0xE0 ;
  }
}
//////////////////////////////////////////////
