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
   /*Pone el amplificador de nivel al mínimo valor posible. Determina la fuerza con la que la señal es transmitida
    por lo tanto significa que estamos poniendo al mínimo el nivel de potencia de la transmisión pero también consume menos energía.
    FIXIT:  Cuando tengamos una versión final del submarino tendrémos que cambiar este valor para poder manejarlo desde mas distancia.
  */
  radio.setPALevel(RF24_PA_MIN);
   /*Pone la transmisión de datos a 250 Kb/s, determina la velocidad con la que se pueden enviar datos. También es importante porque como 
    se ha comentado antes aunque pueda ir a mas velocidad, capando ese límite podemos asegurarnos de que el envío sea mas seguro 

  */
  radio.setDataRate(RF24_250KBPS);
  /*Determina la dirección de recepción de datos.*/
  radio.openReadingPipe(0, address);
  //Significa que empieza a escuchar datos.
  radio.startListening();
}

void loop() {

  //Comprueba en el momento de ejecución de la instrucción si hay información disponible en el buffer de lectura. 
  if (radio.available()) {
    //Selecciona un tamaño máximo de lectura de datos, en este caso 32 caracteres.
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println("Mensaje recibido: ");
    Serial.println(text);
  }
}
