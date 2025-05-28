void setup() {
  Serial.begin(9600);
}
//Lê os dados da entrada analogica A0
void loop() {
  int leitura = analogRead(A0);
  Serial.println(leitura);
  delay(2000);
}
