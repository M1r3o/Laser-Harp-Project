// Created by Frederic Wauters and Istchenko de Carvalho Marco under Creative Commons Licence CC-BY-NC
// This code is delivered with no warranties and you use it at your own risks.
// Version 1.0 - 2021-03-04 - F. Wauters Belgium

// PLEASE READ THIS IMPORTANT NOTICE
// SVP LISEZ CETTE NOTE IMPORTANTE
//
// About CC-BY-SA...
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
// Complete informations about CC-BY-NC licence : 
//    https://creativecommons.org/licenses/by-nc/2.0/be/deed.en
// Cree par Frederic Wauters et Marco Istchenko de Carvalho sous licence Creative Commons CC-BY-NC
// Ce code est fourni sans aucune garantie et vous l'utilisez a vos risques et perils.
// Version 1.0 - 2021-03-04 - F. Wauters Belgium
//
// A propos de CC-BY-NC
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
// Informations complètes concernant la licence CC-BY-NC : 
//    https://creativecommons.org/licenses/by-nc/2.0/be/deed.fr


/*
  int Notes[9][3] = {
  {0, 75, 0},
  {0, 74, 0},
  {0, 72, 0},
  {0, 71, 0},
  {0, 70, 0},
  {0, 68, 0},
  {0, 67, 0},
  {0, 65, 0},
  {0, 60, 0}
  };
  ///////////////////-TABLEAU CORDE-////////////////////////
  const int FLAGON = 0;
  const int NOTEMIDI = 1;
  const int VIBRATION = 2 ;
*/

//////////////////--OPTION--///////////////////
//Pour activer ou désactiver une option, saisisez 1 pour activer ou 0 pour desactiver
boolean NOTE_MIDI_REVERSE = 1 ;
boolean VIBRATION_CORDE = 1 ;

////////////////////--NE PAS TOUCHER LES VARIABLES ET FONCTION QUI SUIVENT--/////////////////
///////////////////--TABLEAU DES NOTES ET VIBRATION--///////////////////////////////////////
int Notes[9][4] = {
  {0, 75, 60, 0},
  {0, 74, 65, 0},
  {0, 72, 67, 0},
  {0, 71, 68, 0},
  {0, 70, 70, 0},
  {0, 68, 71, 0},
  {0, 67, 72, 0},
  {0, 65, 74, 0},
  {0, 60, 75, 0}
};
const int FLAGON = 0;
//const int NOTEMIDI_REVERSE = 1;
//const int NOTEMIDI_NORMAL = 2 ;
int NOTE_MIDI = 0 ; 
//
const int VIBRATION = 3 ;
int cordeVibration = 0;
//
/*********************************
  variable de travail de la harpe
 ********************************/
int minX = 400;
int maxX = 4000;
int laserPin = 4;         // Controle Laser
int boutonOpen = 9;      // Bouton ouverture
int boutonClose = 9;     // Bouton fermeture
int nbCordes = 10;         // Nombre de cordes
bool harpeStatut = false; // Statut (ouverte/fermee)
bool laserStatut = false; // Statut laser (on/off)
int pinSensor = 10 ;
int milieu = 2400 ;
///////////////////////////////////////////////////////
////////////--Variables de travail--//////////////////
int ecart = 0;
float position_corde = 0 ;
/////////////////////////////////////////////////////
// Pour les pauses : a modifier en fonction de tes propres galvo
int pauseStabilisation = 1;
int pausePersistence = 1;
boolean etat = 0 ;


////////////////--MIDI Function--////////////////
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
////////////////////////////////////////////////
/////////////////--OPTION--////////////////////
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
//////////////////////////////////////////////
