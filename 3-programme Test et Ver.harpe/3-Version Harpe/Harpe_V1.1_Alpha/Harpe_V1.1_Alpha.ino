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
#include <MIDI.h>
// Declarations
MCP4725 dac(SDA, SCL);    // DAC
int laserPin = 4;         // COntrole Laser
int boutonOpen = 3;      // Bouton ouverture
int boutonClose = 4;     // Bouton fermeture
int nbCordes = 10;         // Nombre de cordes
bool harpeStatut = false; // Statut (ouverte/fermee)
bool laserStatut = false; // Statut laser (on/off)
int pinSensor = 5 ;

// Pour les pauses : a modifier en fonction de tes propres servos
int pauseStabilisation = 1;
int pausePersistence = 1;

// Pour le debattement de la harpe
int minX = 1129;
int maxX = 3237;

// Variables de travail
int ecart = 0;

int Notes[9][2] = {
  {0, 48},
  {0, 50},
  {0, 52},
  {0, 53},
  {0, 55},
  {0, 57},
  {0, 59},
  {0, 60},
  {0, 62}
};
const int FLAGON = 0;
const int NOTEMIDI = 1;



MIDI_CREATE_DEFAULT_INSTANCE();

// *********
// * SETUP *
// *********
void setup() {
  // Le Setup sert principalement a configurer et
  // a initialiser le diverses choses qui regissent le projet.
  // Si on y fait tourner autre chose, c'est pour "preparer le terrain", rien d'autre
  MIDI.begin(1);
  // Initialisation des pins
  pinMode(laserPin, OUTPUT);
  pinMode(boutonOpen, INPUT);
  pinMode(boutonClose, INPUT);
  pinMode(pinSensor , INPUT);

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

// ********
// * LOOP *
// ********
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
      dac.setValue((2047 - (ecart * nbCordes / 2)) + (cordeCourante * ecart));

      // Pause de stabilisation
      delay(pauseStabilisation);

      // Allumer le laser
      digitalWrite(laserPin, HIGH);
      laserStatut = true;
      if (digitalRead(pinSensor) == true) {
        // Si la note etait jusqu'ici Off
        if (Notes[cordeCourante][FLAGON] == 0) {
          // Il faut jouer la note (MIDI)
          MIDI.sendNoteOn(Notes[cordeCourante][NOTEMIDI], 127, 1);

          // On memorise que cette corde joue , pour ne pas la rejouer (2eme condition If)
          Notes[cordeCourante][FLAGON] = 1;
        }

      }

      else if (digitalRead(pinSensor) == false) {
        // pas de lumiere detectee pour cette corde
        // Il faut arreter , ou , ne pas de jouer la note (MIDI)
        //memoriser que cette note n'est plus jouee
        MIDI.sendNoteOff(Notes[cordeCourante][NOTEMIDI], 0, 1);

        // On memorise que cette corde ne joue pas
        Notes[cordeCourante][FLAGON] = 0;


      }
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

  // Harpe fermee (et on eteint le laser)
  harpeStatut = false;
  digitalWrite(laserPin, LOW);
  laserStatut = false;                // on retient que le laser est allume

  // On est au bout du LOOP, l'Arduino va recommencer. Il attend donc qu'on appuie a nouveau sur Ouvrir...
}
