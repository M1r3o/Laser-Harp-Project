boolean notes_statue = false;
 boolean pin_note = false;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  if (pin_note == true && notes_statue == false) {
    // jouer note;
    notes_statue = true;
  }
  else if ( pin_note == false && notes_statue == false) {
    //arreter note
    notes_statue = false;
  }
}
