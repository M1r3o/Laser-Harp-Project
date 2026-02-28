int pin_galvo=A0;
int TTL_Laser=3;
int Delay=1; 

void setup() {
pinMode(pin_galvo,OUTPUT);  
pinMode(TTL_Laser,OUTPUT);
delay(1000);
digitalWrite(TTL_Laser,HIGH);
delay(500);
digitalWrite(TTL_Laser,LOW);
delay(200);
digitalWrite(TTL_Laser,HIGH);
delay(200);
digitalWrite(TTL_Laser,LOW);
delay(200);
digitalWrite(TTL_Laser,HIGH);
delay(200);
digitalWrite(TTL_Laser,LOW);
delay(200);
digitalWrite(TTL_Laser,HIGH);
delay(200);
}

void loop() {
digitalWrite(TTL_Laser,LOW);
analogWrite(pin_galvo,0);
digitalWrite(TTL_Laser,HIGH);
delay(Delay);
digitalWrite(TTL_Laser,LOW);
analogWrite(pin_galvo,128);
digitalWrite(TTL_Laser,HIGH);
delay(Delay);
digitalWrite(TTL_Laser,LOW);
analogWrite(pin_galvo,255);
digitalWrite(TTL_Laser,HIGH);
delay(Delay);
}
