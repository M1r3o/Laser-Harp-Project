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

void variation(int channel, int velocityVariation){
  Serial.write(channel);
  Serial.write(velocityVariation);
}
