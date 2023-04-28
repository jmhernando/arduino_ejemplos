void setup() {
  pinMode(2, OUTPUT); // Configura la salida digital 13 como salida
}

void loop() {
  digitalWrite(2, HIGH); // Enciende el LED integrado
  delay(1000); // Espera 1 segundo
  digitalWrite(2, LOW); // Apaga el LED integrado
  delay(1000); // Espera 1 segundo
}
