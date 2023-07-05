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


#define WATER_LEVEL 14 // sensor is connected to GPIO2

void setup() {
  Serial.begin(115200); // start serial communication at 9600 bps
  pinMode(WATER_LEVEL, INPUT);
}

void loop() {
  int waterLevel = analogRead(WATER_LEVEL); // read the input on analog pin 2
  Serial.println(waterLevel); // print the value to the serial monitor
  delay(1000); // delay for a second so we have time to see the result
}




