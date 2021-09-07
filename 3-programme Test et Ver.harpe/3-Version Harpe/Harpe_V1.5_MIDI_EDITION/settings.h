/*
***********
--OPTION--
************
*/
//Pour activer ou désactiver une option, saisisez 1 pour activer ou 0 pour desactiver
boolean NOTE_MIDI_REVERSE = 1 ;
boolean VIBRATION_CORDE = 1 ;
/*
********************************************************
--NE PAS TOUCHER LES VARIABLES ET FONCTION QUI SUIVENT--
--TABLEAU DES NOTES ET VIBRATION--
********************************************************
*/
int Notes[9][5] = {
  {0, 75, 60, 0, 127},
  {0, 74, 65, 0, 127},
  {0, 72, 67, 0, 127},
  {0, 71, 68, 0, 127},
  {0, 70, 70, 0, 127},
  {0, 68, 71, 0, 127},
  {0, 67, 72, 0, 127},
  {0, 65, 74, 0, 127},
  {0, 60, 75, 0, 127}
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
        // Controle Laser
     
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

/*
*******************
--MIDI Function--
*******************
*/
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
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
//////////////////////////////////////////////
