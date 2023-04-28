/*ESQUEMA DE CONEXIONES
  En el Arduino Nano:

Pin CE del módulo NRF24L01 a pin digital 9 del Arduino Nano
Pin CSN del módulo NRF24L01 a pin digital 10 del Arduino Nano
Pin SCK del módulo NRF24L01 a pin digital 13 del Arduino Nano
Pin MOSI del módulo NRF24L01 a pin digital 11 del Arduino Nano
Pin MISO del módulo NRF24L01 a pin digital 12 del Arduino Nano
Pin VCC del módulo NRF24L01 a pin de alimentación de 3.3V o 5V del Arduino Nano (asegurándose de que la fuente de alimentación proporciona suficiente corriente)
Pin GND del módulo NRF24L01 a pin GND del Arduino Nano

*/



#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {

  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println("Mensaje recibido: ");
    Serial.println(text);
  }
}
