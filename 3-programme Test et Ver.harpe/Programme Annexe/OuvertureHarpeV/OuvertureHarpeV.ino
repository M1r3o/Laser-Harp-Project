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

// Declarations
MCP4725 dac(SDA, SCL);    // DAC
int laserPin = 4;         // COntrole Laser
int boutonOpen = 22;      // Bouton ouverture
int boutonClose = 23;     // Bouton fermeture
int nbCordes = 11;         // Nombre de cordes
bool harpeStatut = false; // Statut (ouverte/fermee)
bool laserStatut = false; // Statut laser (on/off)

// Pour les pauses : a modifier en fonction de tes propres servos
int pauseStabilisation = 1;
int pausePersistence = 1;

// Pour le debattement de la harpe
int minX = 0;
int maxX = 4096;

// Variables de travail
int ecart=0;

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

  // S'assurer que le laser est eteint
  digitalWrite(laserPin, LOW);

  // Initialisation du DAC
  dac.begin();
}

// ********
// * LOOP *
// ********
void loop() {
  // Le loop est la partie qui est "rejouee" en permanence par l'Arduino.
  // C'est la raison de son nom. Lorsque tou y a ete execute, il recommence.

  // S'assurer que le galvo est au centre
  dac.setValue(2047);
  
  // Attendre qu'on appuie sur open
  while (digitalRead(boutonOpen)==LOW) {
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
  for (int ecart=0; ecart < ((maxX-minX)/(nbCordes-1)); ecart++) {
    // PLACER LE GALVO
    // On boucle sur toutes les cordes pour placer chacune
    for (int cordeCourante=0; cordeCourante < (nbCordes-1); cordeCourante++) {
      // Eteindre le laser
      digitalWrite(laserPin, LOW);
      laserStatut = false;
      
      // Placer le galvo
      dac.setValue((2047-(ecart*(nbCordes-1))+(cordeCourante*ecart)));

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
  while (digitalRead(boutonClose)==LOW) {
    // Ecart
    ecart = (maxX-minX)/(nbCordes-1);
    
    // En attendant qu'on demande la fermeture, on dessine la harpe et ses faisceaux bien sur...
    // On boucle sur toutes les cordes pour placer chacune
    for (int cordeCourante=0; cordeCourante < (nbCordes-1); cordeCourante++) {
      // Eteindre le laser
      digitalWrite(laserPin, LOW);
      laserStatut = false;
      
      // Placer le galvo
      dac.setValue((2047-(ecart*(nbCordes-1))+(cordeCourante*ecart)));

      // Pause de stabilisation
      delay(pauseStabilisation);

      // Allumer le laser
      digitalWrite(laserPin, HIGH);
      laserStatut = true;

      // Pause persistence
      delay(pausePersistence);
    }
  }

  // Si on a quitte la boucle, c'est qu'on a demande la fermeture
  
  // SEQUENCE DE FERMETURE
  // On boucle pour un ecart maximum jusque 0. L'ecart = 4095/(nbCordes-1) 
  for (int ecart=(maxX-minX)/(nbCordes-1); ecart > 0; ecart--) {
    // PLACER LE GALVO
    // On boucle sur toutes les cordes pour placer chacune
    for (int cordeCourante=0; cordeCourante < (nbCordes-1); cordeCourante++) {
      // Eteindre le laser
      digitalWrite(laserPin, LOW);
      laserStatut = false;
      
      // Placer le galvo
      dac.setValue((2047-(ecart*(nbCordes-1))+(cordeCourante*ecart)));

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
