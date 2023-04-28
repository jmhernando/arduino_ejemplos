#include <Wire.h>

#define OV7670_ADDR_WRITE 0x42  // Dirección de escritura del módulo de cámara OV7670
#define OV7670_ADDR_READ 0x43   // Dirección de lectura del módulo de cámara OV7670
#define OV7670_CLK_PIN 3        // Pin utilizado para la señal de reloj SCL
#define OV7670_DATA_PIN 2       // Pin utilizado para la señal de datos SDA

void setup() {
  Wire.begin();               // Inicia la librería Wire para la comunicación I2C
  pinMode(OV7670_CLK_PIN, OUTPUT);
  pinMode(OV7670_DATA_PIN, OUTPUT);
  digitalWrite(OV7670_CLK_PIN, HIGH);
  digitalWrite(OV7670_DATA_PIN, HIGH);

  Serial.begin(115200);       // Inicia la comunicación serial con el ordenador
}

void loop() {
  // Establece el registro de control para obtener una imagen en escala de grises
  OV7670_write_reg(0x12, 0x80);
  OV7670_write_reg(0x11, 0x01);
  OV7670_write_reg(0x3a, 0x04);

  // Inicia la captura de imagen
  OV7670_write_reg(0x0e, 0x01);

  // Espera a que la captura de imagen se complete (aproximadamente 200ms)
  delay(200);

  // Lee la imagen desde el módulo de cámara y la envía por el puerto serial
  for (int i = 0; i < 160 * 120; i++) {
    uint8_t data = OV7670_read_data();
    Serial.write(data);
  }
}

// Función para escribir un valor en un registro específico del módulo de cámara OV7670
void OV7670_write_reg(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(OV7670_ADDR_WRITE);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

// Función para leer un byte de datos desde el módulo de cámara OV7670
uint8_t OV7670_read_data() {
  uint8_t data = 0;
  for (int i = 0; i < 8; i++) {
    digitalWrite(OV7670_CLK_PIN, HIGH);
    data |= digitalRead(OV7670_DATA_PIN) << i;
    digitalWrite(OV7670_CLK_PIN, LOW);
  }
  return data;
}
