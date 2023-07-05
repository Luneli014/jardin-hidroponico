/*

Creado por: Hugo Escalpelo
Fecha: 20230628

Este programa es para probar el sensor de humedad de tierra para el
taller Jardín Hidropónico de Código IoT. Usa un sensor de humedad de
tierra de tres terminales.

Conexiones:

ESP32CAM    FTDI
5v----------VCC
GND---------GND
UoR---------Tx
UoT---------Rx

ESP32CAM    Sensor de humedad
5v----------5v
GND---------GND
GPIO02------Signal/A0

*/


#define SENSOR_PIN 2 // sensor is connected to GPIO2

void setup() {
  Serial.begin(115200); // start serial communication at 9600 bps
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  int humiditySensor = analogRead(SENSOR_PIN); // read the input on analog pin 2
  Serial.println(sensorValue); // print the value to the serial monitor
  delay(1000); // delay for a second so we have time to see the result
}





