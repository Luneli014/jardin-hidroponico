/*

Creado por: Hugo Escalpelo
Fecha: 20230628

Este programa es para probar el servomotor que representará la compuerta
de las sales. 

Conexiones:

ESP32CAM    FTDI
5v----------VCC
GND---------GND
UoR---------Tx
UoT---------Rx

ESP32CAM    Servo
5v----------5v
GND---------GND
GPIO15------Signal

*/

#include <ESP32Servo.h>  // Incluimos la biblioteca ESP32Servo

Servo myservo;  // Creamos un objeto servo para controlar nuestro servomotor

void setup() {
  Serial.begin(115200);   // Iniciamos la comunicación serie con una velocidad de 115200 baudios
  myservo.setPeriodHertz(50);    // Establecemos una frecuencia estándar de 50 Hz para el servo
  myservo.attach(15, 500, 2400); // Conectamos el servo al pin 15
}

void loop() {
  for (int posicion = 0; posicion <= 90; posicion += 1) { 
    myservo.write(posicion); // Indicamos al servo que vaya a la posición actual
    if (posicion == 90) {    // Cuando la compuerta está totalmente abierta
      Serial.println("Compuerta de sales abierta");
    }
    delay(20); // Esperamos 20ms para que el servo alcance la posición
  }
  delay(2500);  // Esperamos 2.5 segundos
  
  for (int posicion = 90; posicion >= 0; posicion -= 1) { 
    myservo.write(posicion); // Indicamos al servo que vaya a la posición actual
    if (posicion == 0) {     // Cuando la compuerta está totalmente cerrada
      Serial.println("Compuerta de sales cerrada");
    }
    delay(20); // Esperamos 20ms para que el servo alcance la posición
  }
  delay(2500);  // Esperamos 2.5 segundos
}