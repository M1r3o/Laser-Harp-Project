///////M1R3O 2021////////////
/* VCC = 5V
 * GND = 0V
 * Pin A (A pour Analogique ,du capteur) = A0
 * Pin D (D pour digital , du capteur) = 10
 */

int capteur = 0 ; 
int capteur1 = 0;
int delai = 1 ; 

void setup() {
  Serial.begin(115200);// put your setup code here, to run once:
  pinMode(10, INPUT);

}

void loop() {
  capteur=digitalRead(10);
  capteur1=analogRead(A0);
  Serial.println("Statue Capteur Digital (1 ou 0)");
  Serial.println(capteur);// put your main code here, to run repeatedly:
  delay(delai);
  Serial.println("Statue Capteur analogique");
  Serial.println(capteur1);
  delay(delai);
}
