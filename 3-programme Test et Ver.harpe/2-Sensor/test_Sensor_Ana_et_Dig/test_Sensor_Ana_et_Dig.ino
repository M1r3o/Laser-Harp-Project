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





///////M1R3O 2021////////////
/* VCC = 5V
 * GND = 0V
 * Pin A (A pour Analogique ,du capteur) = A0
 * Pin D (D pour digital , du capteur) = 10
 */

int capteur = 0 ; 
int capteur1 = 0;

void setup() {
  Serial.begin(9600);// put your setup code here, to run once:
  pinMode(10, INPUT);
}

void loop() {
  capteur=digitalRead(10);
  capteur1=analogRead(A0);
  Serial.println("Statue Capteur Digital (1 ou 0)");
  Serial.println(capteur);
  delay(1);
  Serial.println("Statue Capteur analogique");
  Serial.println(capteur1);
  delay(1);
}
