/*
*******************
--MIDI Function--
*******************
*/
void noteOn(int cmd, int pitch) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(127);
}

void noteOff(int cmd, int pitch) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(0);
}

void Variation(int cmd, int pitch, int velocity){
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
