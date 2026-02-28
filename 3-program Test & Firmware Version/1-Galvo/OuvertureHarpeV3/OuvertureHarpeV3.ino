//release by M1r3o & Frederic Wauters
//Creative Commons CC-BY-SA 2021
//Harpe_V1.5_MIDI_Edition

// Created by Frederic Wauters and Istchenko de Carvalho Marco under Creative Commons Licence CC-BY-NC
// This code is delivered with no warranties and you use it at your own risks.
// Version 1.0 - 2021-03-04 - F. Wauters Belgium

// PLEASE READ THIS IMPORTANT NOTICE
// SVP LISEZ CETTE NOTE IMPORTANTE
//
// About CC-BY-NC...
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
int boutonOpen = 8;      // Bouton ouverture
int boutonClose = 9;     // Bouton fermeture
int nbCordes = 14;         // Nombre de cordes
bool harpeStatut = false; // Statut (ouverte/fermee)
bool laserStatut = false; // Statut laser (on/off)

// Pour les pauses : a modifier en fonction de tes propres servos
int pauseStabilisation = 1;
int pausePersistence = 1;

// Pour le debattement de la harpe
int minX = 1129;
int maxX = 3237;

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
      dac.setValue((2047-(ecart*nbCordes/2))+(cordeCourante*ecart));

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
  while (digitalRead(boutonOpen)==LOW) {
    // Ecart
    ecart = (maxX-minX)/(nbCordes-1);
    
    // En attendant qu'on demande la fermeture, on dessine la harpe et ses faisceaux bien sur...
    // On boucle sur toutes les cordes pour placer chacune
    for (int cordeCourante=0; cordeCourante < (nbCordes-1); cordeCourante++) {
      // Eteindre le laser
      digitalWrite(laserPin, LOW);
      laserStatut = false;
      
      // Placer le galvo
      dac.setValue((2047-(ecart*nbCordes/2))+(cordeCourante*ecart));

      // Pause de stabilisation
      delay(pauseStabilisation);

      // Allumer le laser
      digitalWrite(laserPin, HIGH);
      laserStatut = true;
//mettre Note MIDI 
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
      dac.setValue((2047-(ecart*nbCordes/2))+(cordeCourante*ecart));

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
