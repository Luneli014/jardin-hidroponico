/*

Creado por: Hugo Escalpelo
Fecha: 20230628

Este programa muestra la prueba de la bomba de agua. El programa envia una señal
pulsada con un ciclo util del 30% con el objetivo de hace girar la bomba a una
velocidad menor. Se usa un transistor PNP BC548 para realizar la conexión

Conexiones:

ESP32CAM    FTDI
5v----------VCC
GND---------GND
UoR---------Tx
UoT---------Rx

ESP32CAM    BC548     Bomba de agua
5v----------Colector
GPIO12------Base
            Emisor----Positivo
GND-------------------Negativo


*/

#define WATER_PUMP 12 // La bomba de agua está conectada al GPIO13

void setup() {
  Serial.begin(115200); // Inicia la comunicación serial a 115200 bps
  pinMode(WATER_PUMP, OUTPUT); // Configura el pin de la bomba de agua como salida
}

void loop() {
  // Enciende y apaga la bomba de agua con un ciclo de trabajo del 30% durante 3 segundos
  for(int i = 0; i < 300; i++) { // 30 repeticiones, cada una durando 100ms, resultará en un total de 3 segundos.
    digitalWrite(WATER_PUMP, HIGH); // Enciende la bomba de agua. En el modo de drenaje, la bomba se activa cuando el pin está en estado HIGH.
    delay(3); // Mantiene la bomba encendida durante el 30% del tiempo (30ms)
    digitalWrite(WATER_PUMP, LOW); // Apaga la bomba de agua.
    delay(7); // Mantiene la bomba apagada durante el 70% del tiempo (70ms)
  }
  Serial.println("Bomba de agua desactivada por 5 segundos"); // Imprime el estado de la bomba de agua en el monitor serial
  delay(5000); // Apaga la bomba de agua durante 5 segundos
}