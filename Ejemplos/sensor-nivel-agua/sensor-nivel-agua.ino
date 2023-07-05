/*

Creado por: Hugo Escalpelo
Fecha: 20230628

Este programa es para probar el sensor de nivel de agua para el
taller Jardín Hidropónico de Código IoT. Usa un sensor de nivel de
agua de tres terminales.

Conexiones:

ESP32CAM    FTDI
5v----------VCC
GND---------GND
UoR---------Tx
UoT---------Rx

ESP32CAM    Sensor de nivel de agua
5v----------5v
GND---------GND
GPIO14------Signal/A0

*/


#define WATER_LEVEL 14 // El sensor está conectado a GPIO14

void setup() {
  Serial.begin(115200); // Iniciar comunicación serie a 115200 bps
  pinMode(WATER_LEVEL, INPUT); // Definir el pin del sensor como entrada
}

void loop() {
  int waterLevel = analogRead(WATER_LEVEL); // Leer el valor en el pin analógico 14
  Serial.println(waterLevel); // Imprimir el valor en el monitor serie
  delay(1000); // Hacer una pausa de un segundo para poder observar el resultado
}




