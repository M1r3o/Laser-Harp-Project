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
/
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
