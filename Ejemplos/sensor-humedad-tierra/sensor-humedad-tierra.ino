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


#define HUMIDITY_SENSOR 2 // El sensor está conectado al GPIO2

void setup() {
  Serial.begin(115200); // Inicia la comunicación serial a 115200 bps
  pinMode(HUMIDITY_SENSOR, INPUT); // Configura el pin del sensor de humedad como entrada
}

void loop() {
  int humiditySensor = analogRead(HUMIDITY_SENSOR); // Lee la entrada en el pin analógico 2
  Serial.println(humiditySensor); // Imprime el valor al monitor serial
  delay(1000); // Espera un segundo para que tengamos tiempo de ver el resultado
}





