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

  Serial.write(adresseMIDIeffet);
  Serial.write(pitch);
  Serial.write(velocity);
}
