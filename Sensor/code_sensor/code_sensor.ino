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
      // jouer notes
      notes = true ;
      
    }
  }
  else {
    if (notes == true ){
    //note off ;
    notes = false;
  }
 }
}
