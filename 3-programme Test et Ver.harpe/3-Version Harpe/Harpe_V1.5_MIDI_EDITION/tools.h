/*
*******************
--MIDI Function--
*******************
*/
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

void Variation(int cmd, int pitch, int velocity){
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
