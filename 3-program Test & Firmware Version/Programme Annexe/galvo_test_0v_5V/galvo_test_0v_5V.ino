int pin_galvo = 3 ; 
int pin_laser_TTL = 4 ; 
int Delay = 5 ;

void setup () {
  pinMode(pin_galvo, OUTPUT);
  pinMode(pin_laser_TTL, OUTPUT);
  delay(1000);
  digitalWrite(pin_laser_TTL, HIGH);
  delay(100);
  digitalWrite(pin_laser_TTL, LOW);
  delay(100);
  digitalWrite(pin_laser_TTL, HIGH);
  delay(100);
  digitalWrite(pin_laser_TTL, LOW);
  delay(100);
  digitalWrite(pin_laser_TTL, HIGH);
  delay(100);
  digitalWrite(pin_laser_TTL, LOW);
}
void loop () {
  
  digitalWrite(pin_laser_TTL, LOW);
  delay(Delay);
  analogWrite(pin_galvo, 255);
  digitalWrite(pin_laser_TTL, HIGH);
  delay(Delay);
  digitalWrite(pin_laser_TTL, LOW);
  delay(Delay);
  analogWrite(pin_galvo, 0);
  digitalWrite(pin_laser_TTL, HIGH);
  delay(Delay);
  
}

