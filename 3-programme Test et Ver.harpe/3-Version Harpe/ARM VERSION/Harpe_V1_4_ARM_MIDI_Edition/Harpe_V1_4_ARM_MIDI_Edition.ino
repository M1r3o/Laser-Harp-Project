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


// /!\ to send notes , we have configured serial protocol to 115200 Bytes/seconds
// we used to send MIDI notes : Hairless MIDI Serial (to send MIDI notes from Arduino to Standalone Synthesizer via USB->MIDI converter)
// Enter into setup and choose 115200 bauds rates
// to change option (actually vibration corde and reverse mode for note, go to "settings.h"
// (: enjoy :)

//////////////////////////////
////////dependance///////////
#include "Wire.h"
#include "MCP4725.h"
#include "settings.h"
#include <WiFi.h>
#include <WebServer.h>
// --- CONFIGURATION WIFI ---
const char* ssid = "LASER_HARP_WEB_PANEL";
const char* password = "LASERHARPESP32";

// --- 2. VARIABLES GLOBALES ---
bool VIBRATION_CORDE = true; 
bool NOTE_MIDI_REVERSE = true; // Nouvelle variable booléenne (remplace le nombre de cordes)

// Création du serveur web sur le port 80
WebServer server(80);

// --- 3. PAGE WEB (HTML & CSS) ---
String getHTML() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>Laser Harp Config</title>";
  html += "<style>";
  // Design futuriste
  html += "body { font-family: 'Segoe UI', sans-serif; background-color: #0b0b0b; color: #fff; text-align: center; padding: 20px; }";
  html += "h1 { color: #00ffcc; letter-spacing: 2px; text-shadow: 0 0 15px #00ffcc; }";
  html += ".container { background: #1a1a1a; max-width: 380px; margin: 0 auto; padding: 25px; border-radius: 20px; border: 1px solid #333; box-shadow: 0 10px 30px rgba(0,0,0,0.8); }";
  
  // Layout des lignes
  html += ".row { display: flex; justify-content: space-between; align-items: center; margin-bottom: 30px; }";
  html += ".label-text { font-size: 1.1rem; font-weight: 300; }";

  // Style des interrupteurs
  html += ".switch { position: relative; display: inline-block; width: 55px; height: 28px; }";
  html += ".switch input { opacity: 0; width: 0; height: 0; }";
  html += ".slider { position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0; background-color: #333; transition: .4s; border-radius: 34px; border: 1px solid #444; }";
  html += ".slider:before { position: absolute; content: ''; height: 20px; width: 20px; left: 3px; bottom: 3px; background-color: white; transition: .4s; border-radius: 50%; }";
  html += "input:checked + .slider { background-color: #00ffcc; border-color: #00ffcc; }";
  html += "input:checked + .slider:before { transform: translateX(26px); }";
  
  // Bouton de validation
  html += ".btn { background: none; color: #00ffcc; border: 2px solid #00ffcc; padding: 12px; width: 100%; border-radius: 10px; font-size: 1rem; font-weight: bold; cursor: pointer; transition: 0.3s; }";
  html += ".btn:hover { background: #00ffcc; color: #000; }";
  html += "</style></head><body>";
  
  html += "<h1>HARPE LASER</h1>";
  html += "<div class='container'><form action='/' method='POST'>";
  
  // Interrupteur 1 : VIBRATION_CORDE
  html += "<div class='row'>";
  html += "<span class='label-text'>Vibration Corde</span>";
  html += "<label class='switch'>";
  html += "<input type='checkbox' name='vib_corde' value='true' " + String(VIBRATION_CORDE ? "checked" : "") + ">";
  html += "<span class='slider'></span></label></div>";
  
  // Interrupteur 2 : NOTE_MIDI_REVERSE
  html += "<div class='row'>";
  html += "<span class='label-text'>Inversion MIDI</span>";
  html += "<label class='switch'>";
  html += "<input type='checkbox' name='midi_rev' value='true' " + String(NOTE_MIDI_REVERSE ? "checked" : "") + ">";
  html += "<span class='slider'></span></label></div>";
  
  html += "<button type='submit' class='btn'>SAUVEGARDER</button>";
  html += "</form></div></body></html>";
  return html;
}

// --- 4. TRAITEMENT DES DONNÉES ---
void handleRoot() {
  if (server.method() == HTTP_POST) {
    // Lecture du switch Vibration Corde
    VIBRATION_CORDE = server.hasArg("vib_corde");

    // Lecture du switch MIDI Reverse
    NOTE_MIDI_REVERSE = server.hasArg("midi_rev");
    
    Serial.println("--- NOUVELLE CONFIGURATION ---");
    Serial.printf("Vibration Corde : %s\n", VIBRATION_CORDE ? "ACTIF" : "INACTIF");
    Serial.printf("MIDI Reverse    : %s\n", NOTE_MIDI_REVERSE ? "OUI" : "NON");
  }
  server.send(200, "text/html", getHTML());
}// DAC

MCP4725 dac(0x60);
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
  pinMode(pinSensor, INPUT);
  pinMode(14, OUTPUT);
  Serial.begin(115200);

  digitalWrite(laserPin, HIGH);

  // Initialisation du DAC
  dac.begin();
  dac.setValue(maxX - minX);
  delay(3000);
  Serial.print("idle");
  digitalWrite(laserPin, LOW);

  // Démarrage du Point d'Accès WiFi
  WiFi.softAP(ssid, password);
  Serial.println("Point d'accès démarré.");
  Serial.print("Connectez-vous à : "); Serial.println(ssid);
  Serial.print("IP de l'interface : "); Serial.println(WiFi.softAPIP());
  server.on("/", handleRoot);
  server.begin();

  delay(1000);
}

// ********
// * LOOP *
// ********
void loop() {
  // Le loop est la partie qui est "rejouee" en permanence par l'Arduino.
  // C'est la raison de son nom. Lorsque tout y a ete execute, il recommence.
  //Serial.println(NOTE_MIDI);
  dac.setValue(2060);

  // Attendre qu'on appuie sur open
  while (digitalRead(boutonOpen) == LOW) {
    server.handleClient();
    reverse();
    vibration();
    Serial.println("IDLE LOOP");
    debogRGB(1,0,1);
    // On ne fait rien, on attend qu'on appuie
    // Cette boucle tourne tant que le bouton open n'est pas enfonce
    delay(1);
  }






  // On a appuie, on allume le laser
  digitalWrite(laserPin, HIGH);
  laserStatut = true;  // on retient que le laser est allume

  // On attend un peu pour l'effet... enfin, si on veut
  delay(1000);

  // SEQUENCE D'OUVERTURE
  // On boucle pour un ecart de 0 jusque maximum. L'ecart = 4095/(nbCordes-1)
  for (int ecart = 0; ecart < ((maxX - minX) / (nbCordes - 1)); ecart++) {
    debogRGB(0,1,0);
    // PLACER LE GALVO
    // On boucle sur toutes les cordes pour placer chacune
    for (int cordeCourante = 0; cordeCourante < (nbCordes - 1); cordeCourante++) {
      // Eteindre le laser
      digitalWrite(laserPin, LOW);
      // Placer le galvo
      position_corde = (milieu - (ecart * nbCordes / 2)) + (cordeCourante * ecart);
      dac.setValue(position_corde);
      // Pause de stabilisation
      delay(pauseStabilisation);
      digitalWrite(laserPin, HIGH);
      delay(1);
    }
  }

  // La harpe est ouverte, on le retient
  harpeStatut = true;

  // Attendre qu'on appuie sur open
  while (digitalRead(boutonOpen) == LOW) {
    // Ecart
    ecart = (maxX - minX) / (nbCordes - 1);

    // En attendant qu'on demande la fermeture, on dessine la harpe et ses faisceaux bien sur...
    // On boucle sur toutes les cordes pour placer chacune
    for (int cordeCourante = 0; cordeCourante < (nbCordes - 1); cordeCourante++) {
      debogRGB(0,0,1);
      digitalWrite(laserPin, LOW);
      // Placer le galvo
      position_corde = (milieu - (ecart * nbCordes / 2)) + (cordeCourante * ecart);
      dac.setValue(position_corde + (Notes[cordeCourante][VIBRATION]));
      Notes[cordeCourante][VIBRATION] = -(Notes[cordeCourante][VIBRATION] / 2);
      delay(pauseStabilisation);
      digitalWrite(laserPin, HIGH);
      delay(1);

      if (digitalRead(pinSensor) == true && Notes[cordeCourante][FLAGON] == 0) {  // Si la note etait jusqu'ici Off et que la detection pour la corde desire est faite
        // Il faut jouer la note (MIDI)
        noteOn(0x90, Notes[cordeCourante][NOTE_MIDI], 127);
        // On memorise que cette corde joue , pour ne pas la rejouer(diiiiing,diiiing,diiiiing, (2eme condition If)
        //ont tient la note (allumee), jusqu'a ce qu'on retire la main
        Notes[cordeCourante][FLAGON] = 1;
        Notes[cordeCourante][VIBRATION] = cordeVibration;
      }

      else if (digitalRead(pinSensor) == false && Notes[cordeCourante][FLAGON] == 1) {  // Si la note etait jusqu'ici ON et que la detection pour la corde desire n'est plus satisfaite
        // Il faut arreter ,ou, ne pas de jouer la note (MIDI)
        //memoriser que cette note n'est plus jouee
        // On memorise que cette corde ne joue pas
        noteOn(0x90, Notes[cordeCourante][NOTE_MIDI], 0);  // on envoie une note mais ayant une velocite de 0 , donc elle ne sera pas joue
        Notes[cordeCourante][FLAGON] = 0;
      }
    }
  }


  // Si on a quitte la boucle, c'est qu'on a demande la fermeture

  // SEQUENCE DE FERMETURE
  // On boucle pour un ecart maximum jusque 0. L'ecart = 4095/(nbCordes-1)
  for (int ecart = (maxX - minX) / (nbCordes - 1); ecart > 0; ecart--) {
    debogRGB(1,1,0);
    // PLACER LE GALVO
    // On boucle sur toutes les cordes pour placer chacune
    for (int cordeCourante = 0; cordeCourante < (nbCordes - 1); cordeCourante++) {
      digitalWrite(laserPin, LOW);
      // Placer le galvo
      position_corde = (milieu - (ecart * nbCordes / 2)) + (cordeCourante * ecart);
      dac.setValue(position_corde);
      // Pause de stabilisation
      delay(pauseStabilisation);
      // Pause de stabilisation
      digitalWrite(laserPin, HIGH);
      delay(1);
    }
  }

  // Harpe fermee (et on eteint le laser)
  harpeStatut = false;
  digitalWrite(laserPin, LOW);
  laserStatut = false;  // on retient que le laser est allume

  // On est au bout du LOOP, l'Arduino va recommencer. Il attend donc qu'on appuie a nouveau sur Ouvrir...
}
