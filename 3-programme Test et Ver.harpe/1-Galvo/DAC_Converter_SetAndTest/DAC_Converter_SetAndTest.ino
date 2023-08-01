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






/*
 * DAC Conerter Set and test
 * -------------------------
 * 
 * EN:
 * This sketch is used to set offset and gain correctly BEFORE connecting to galvanometer controler.
 * Please read documentation associated DAC-ConvertisseurUnipolaire.pdf
 * 
 * FR :
 * Ce programme est utilisé pour régler offset et gain correctement AVANT de connecter au controlleur du galvanometre.
 * Veuillez lire la documentation associée DAC-ConvertisseurUnipolaire.pdf
 * 
 * Code & documentation by F. Wauters. (2019) Licence creative common BY-CC
 */

// Library for the DAC
// Librairie pour le DAC 
#include <MCP4725.h>

// Declarations
MCP4725 dac(SDA, SCL);
int plusPin = 9;
int moinsPin = 8;
bool Status=false;

// *******************************************
// *       Setup before main program         *
// * Configuration avant programme principal *
// *******************************************
void setup() {
  // Initializing the DAC
  // Initialisation du DAC
  dac.begin();

  // For testing buttons
  // Pour les boutons tests
  pinMode(plusPin, INPUT);
  pinMode(moinsPin, INPUT);

  // Opening serial port
  // Ouverture du port serie
  Serial.begin(9600);
  while (!Serial) {
  }
}

// ********************************
// *        Main program          *
// * Programme principal (boucle) *
// ********************************
void loop() {
  // If click on the PLUS button
  // Si clic sur le bouton PLUS
  if (digitalRead(plusPin)==HIGH) {
    // If not actually at this state
    // Si on n'etait pas encore dans cet etat
    if (Status !=true) {
      // Change status
      // On a change
      Serial.println("5V");

      // Memorize
      // Memoriser
      Status = true;
    }

    // Go to 5V
    // Monter a 5V
    dac.setValue(4095);
  }

  // If click on the MINUS button
  // Si clic sur le bouton MOINS
  if (digitalRead(moinsPin)==HIGH) {
    // If not actually in this state
    // Si on n'etait pas encore dans cet etat
    if (Status !=false) {
      // Change status
      // On a change
      Serial.println("GND");
 
      // Memorize
      // Memoriser
      Status = false;
    }

    // Go to 0V
    // Descendre a 0V
    dac.setValue(0);
  }  
}
