boolean notes = false ;
boolean Photo_Trans = true ;
void setup() {
  Serial.begin(9600);
  Serial.println(notes);
  delay (7000);

}

void loop() {
  if (Photo_Trans == true ) {
    if (notes == false) {
      Serial.println("Jouer");
      Serial.println(notes);
      notes = true ;
    }
    else {
      if (notes == true) {
        Serial.println("Ne pas jouer");
         Serial.println(notes);
        notes = true;
      }
    }
  }
  else if (Photo_Trans == false) {
    //note off ;
    notes = false;
  }
  delay(1000);

}
