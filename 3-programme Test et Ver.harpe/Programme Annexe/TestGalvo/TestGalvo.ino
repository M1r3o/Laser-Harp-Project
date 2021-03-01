// Declarations pour les connexions
int Xpin = 3;
int LASERpin = 4;

// Declarations pour le fonctionnement
int nbCordes = 4;  // A changer pour faire plus ou moins de cordes

void setup() {
  // Configuration des pins
  pinMode(Xpin, OUTPUT);
  pinMode(LASERpin, OUTPUT);
}

void loop() {
  // Variables de travail
  int cordeActuelle=0;
  float Interval=0;
  
  // Calcul de l'interval
  Interval = 255/4;
  
  // Boucler sur le nombre de "cordes"
  for (cordeActuelle=0; cordeActuelle < nbCordes; cordeActuelle++) {
    // Eteindre le laser
    digitalWrite(LASERpin, LOW);
    
    // Positionner le galvo
    analogWrite(Xpin, (cordeActuelle*Interval));
    
    // Petite pause
    delay(1);  // A REGLER (Pause 1 : stabilisation du galvo avant allumage laser)
    
    // Allumer le laser
    digitalWrite(LASERpin, HIGH);
    
    // Petite pause
    delay(2);  // A REGLER (Pause 2 : période d'allumage laser pour assurer la visibilite)
  }
}
