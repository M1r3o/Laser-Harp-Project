//release by M1r3o & Frederic Wauters
//Creative Commons CC-BY-NC-SA 2021
//Harpe_V1.5_MIDI_Edition

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


/*
*******************
--MIDI Function--
*******************
*/
void noteOn(int pitch) {
  Serial.write(0x90);
  Serial.write(pitch);
  Serial.write(127);
}

void noteOff(int pitch) {
  Serial.write(0x90);
  Serial.write(pitch);
  Serial.write(0);
}

void variationHand( int pitch, int velocity){
  Serial.write(0xB0);
  Serial.write(pitch);
  Serial.write(velocity);
}
