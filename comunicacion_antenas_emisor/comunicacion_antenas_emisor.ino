/*Sketch que tendrá de funcionalidad la comprensión del funcionamiento del módulo de antenas NRF24L01
  El módulo NRF24L01 es utilizado para comunicaciones inalámbricas con 2,4GHz de potencia, un alcance máximo
  de 100 metros y una velocidad de 2Mbps.
  
  Para hacernos una idea un pdf de tamaño medio (entre 1MB y 128MB) que tiene 20MB tardaría alrededor de 80 segundos.


Explicación de cada pin:

CE (Chip Enable): Este pin habilita el módulo NRF24L01 para transmitir o recibir datos. El pin debe configurarse en alto para habilitar la comunicación y en bajo para deshabilitar la comunicación.

CSN (Chip Select Not): Este pin se utiliza para seleccionar el módulo NRF24L01. Cuando este pin se configura en bajo, el módulo está seleccionado y listo para recibir datos.

SCK (Serial Clock): Este pin proporciona la señal de reloj para la comunicación SPI. El pin es utilizado por el maestro (Arduino) para enviar y recibir datos.

MOSI (Master Out Slave In): Este pin es utilizado por el maestro (Arduino) para enviar datos al módulo NRF24L01.

MISO (Master In Slave Out): Este pin es utilizado por el módulo NRF24L01 para enviar datos al maestro (Arduino).

VCC: Este pin proporciona alimentación al módulo NRF24L01. La tensión de entrada puede ser de 1,9V a 3,6V.

GND: Este pin es la conexión a tierra del módulo NRF24L01.


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

  /*Determina la dirección de envío de los datos. En nuestro caso hemos declarado anteriormente la variable address como un array de x elementos*/
  radio.openWritingPipe(address);
}

void loop() {
  //TODO: Se implementará un sistema parecido al ACK de protocolos de red. No sé si para esta versión se encriptará información o se comprobará que llega
  //el mensaje entero con alguna clave hash pero algo así se intentará.
  const char text[] = "me gustan las papitas";
  //Selecciona el puntero a text y recoge de tamaño toda la longitud del mensaje (envía el mensaje entero.)
  radio.write(&text, sizeof(text));
  //Si el mensaje es enviado. Se escribe por pantalla
  Serial.println("Mensaje enviado: ");
  Serial.println(text);
  delay(1000);
}

