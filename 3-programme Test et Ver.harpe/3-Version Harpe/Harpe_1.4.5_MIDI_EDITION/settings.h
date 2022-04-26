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
////////////////////////////////////////////////
//////////////////--OPTION--///////////////////
//Pour activer ou désactiver une option, saisisez 1 pour activer ou 0 pour desactiver
boolean NOTE_MIDI_REVERSE = 0 ;
boolean VIBRATION_CORDE = 1 ;
const int nombre_patch = 4 ;
/////////////////////////////////////////////////////////////////////////////////////////////
///////////////////--TABLEAU DES NOTES ET VIBRATION--///////////////////////////////////////
int patch_notes [nombre_patch][13] {
  {9,60, 65,67,68,70,71,72,74,75},
  {9,60, 65,67,68,70,71,72,74,75},
  {9,60, 65,67,68,70,71,72,74,75},
  {9,60, 65,67,68,70,71,72,74,75}, // ajouter une ligne pour ajouter un patch 
  // {nombre_de_corde, note1, note2, etc...}, Mise en forme pour ajouter un patch 
};
/////////////////////////////////////////////////////////////////////////////////////
int cpt = 1 ; // varie n fonction de l'appuie sur les pedale
int nbCordes = patch_notes[cpt][1] + 1; // Nombre de cordes (definit automatiquement)
const int nbNote = nbCordes - 1 ; 
///////////////////////////////////////////////////////////////////////////////////

////////////////////--NE PAS TOUCHER LES VARIABLES ET FONCTION QUI SUIVENT--/////////////////
int Notes[][4] = {
  {0, patch_notes [cpt][nbCordes], patch_notes [cpt][2], 0},
  {0, patch_notes [cpt][nbCordes-1], patch_notes [cpt][3], 0},
  {0, patch_notes [cpt][nbCordes-2], patch_notes [cpt][4], 0},
  {0, patch_notes [cpt][nbCordes-3], patch_notes [cpt][5], 0},
  {0, patch_notes [cpt][nbCordes-4], patch_notes [cpt][6], 0},
  {0, patch_notes [cpt][nbCordes-5], patch_notes [cpt][7], 0},
  {0, patch_notes [cpt][nbCordes-6], patch_notes [cpt][8], 0},
  {0, patch_notes [cpt][nbCordes-7], patch_notes [cpt][9], 0},
  {0, patch_notes [cpt][nbCordes-8], patch_notes [cpt][10], 0},
  {0, patch_notes [cpt][nbCordes-9], patch_notes [cpt][11], 0},
  {0, patch_notes [cpt][nbCordes-10], patch_notes [cpt][12], 0},
  {0, patch_notes [cpt][-nbCordes-11], patch_notes [cpt][13], 0},
};
const int FLAGON = 0;
int NOTE_MIDI = 0 ;
//
const int VIBRATION = 3 ;
int cordeVibration = 0;
//
/*********************************
  variable de travail de la harpe
 ********************************/
int minX = 100;
int maxX = 3700;
int laserPin = 2;         // Controle Laser
int boutonOpen = 9;      // Bouton ouverture
int boutonClose = 9;     // Bouton fermeture
bool harpeStatut = false; // Statut (ouverte/fermee)
bool laserStatut = false; // Statut laser (on/off)
int pinSensor = 10 ;
const char pedale_plus = 7 ; // pedale patch + 
const char pedale_moins = 8 ; // pedale patch  - 

int milieu = maxX - minX ;
///////////////////////////////////////////////////////
////////////--Variables de travail--//////////////////
int ecart = 0;
float position_corde = 0 ;
/////////////////////////////////////////////////////
// Pour les pauses : a modifier en fonction de tes propres galvo
int pauseStabilisation = 2;
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
// 3 pedales

void pedales() { 
  if (digitalRead(pedale_plus) == 1) {
    cpt++ ;
    dac.setVoltage(milieu , false);
    delay(500);
  }
  else if (digitalRead(pedale_moins) == 1) {
    cpt-- ;
    dac.setVoltage(milieu ,false);
    delay(500);
  }
  else if (digitalRead(pedale_plus) == 1 && cpt == nombre_patch) {
    cpt = 1 ;
    dac.setVoltage(milieu , false);
    delay(500);
  }
  else if (digitalRead(pedale_moins) == 1 && cpt== 1) {
    dac.setVoltage(milieu, false);
    delay(500);
  }
}
//////////////////////////////////////////////
