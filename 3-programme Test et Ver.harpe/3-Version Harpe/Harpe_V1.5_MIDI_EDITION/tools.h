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

void Variation(int channel, int pitch, int velocityVariation){
  Serial.write(channel);
  Serial.write(pitch);
  Serial.write(velocityVariation);
}
