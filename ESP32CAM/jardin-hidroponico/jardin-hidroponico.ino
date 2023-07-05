/*

Creado por: Hugo Escalpelo
Fecha: 20230628

Este es el programa general que controla todos los sensores y actuadores del
Jardín Hidropónico: Sensor de humedad de tierra, sensor de nivel de agua, sensor
de flujo de agua, servomotor para administracion de sales y bomba de agua.

Este programa reporta los valores de los sensores via serial de la siguiente forma
[sensor de humedad de tierra, sensor de nivel de agua, sensor de flujo de agua]
Los tipos de dato son los siguientes [int, int, float]

Este programa puede recibir una cadena con salto de linea via serial para controlar
los motores de la siguiente forma [servo, bomba]. Los tipos de dato son los siguientes
[bool, bool]

Este circuito se conecta via USB a la Raspberr Pi para tener conectividad a WiFi
debido a que una limitación del ESP32CAM es que no se puede usar el convertidor
analógico digital mientras se usa el WiFi. La raspberry Pi deberá correr un flow 
en NodeRed que se comunique via mqtt con el servidor principal. El servidor principal
tendrá un flow que graficará y administrará el funcionamiento del jardín hidropónico.

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

ESP32CAM    Sensor de nivel de agua
5v----------5v
GND---------GND
GPIO14------Signal/A0

ESP32CAM    Sensor de flujo de agua
5v----------5v
GND---------GND
GPIO13------Signal

ESP32CAM    Servo
5v----------5v
GND---------GND
GPIO15------Signal

ESP32CAM    BC548     Bomba de agua
5v----------Colector
GPIO12------Base
            Emisor----Positivo
GND-------------------Negativo

*/

#include <ESP32Servo.h>

#define HUMIDITY_SENSOR 2 // Sensor de humedad en el pin GPIO2
#define WATER_LEVEL 14 // Sensor de nivel de agua en el pin GPIO14
#define FLOW_SENSOR 13 // Sensor de flujo de agua en el pin GPIO13
#define WATER_PUMP 12 // Bomba de agua en el pin GPIO12
#define SERVO_PIN 15 // Servomotor en el pin GPIO15

Servo servo; // Crea un objeto Servo

volatile int flowCounter; // Este entero volátil almacena el número de pulsos del sensor de flujo.
float flowRate = 0; // Inicializa el flujo de agua
unsigned long oldTime;
unsigned long msgTime;
int servoCommand = 0; // Variable para controlar la activación del servo
int pumpCommand = 0; // Variable para controlar la activación de la bomba de agua

// Esta es la función de interrupción que se activa cada vez que el sensor de flujo envía un pulso.
void IRAM_ATTR pulseCounter() {
  flowCounter++;
}

void setup() {
  Serial.begin(115200); // Inicia la comunicación serial a 115200 bps
  pinMode(HUMIDITY_SENSOR, INPUT);
  pinMode(WATER_LEVEL, INPUT);
  pinMode(FLOW_SENSOR, INPUT_PULLUP); // Configura el pin del sensor de flujo como entrada
  pinMode(WATER_PUMP, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR), pulseCounter, RISING);  // Asocia la función de interrupción pulseCounter al pin del sensor de flujo

  servo.attach(SERVO_PIN); // Adjunta el servomotor al pin definido
  oldTime = millis();
  msgTime = millis ();
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n'); // Lee la cadena de datos hasta que encuentre una nueva línea
    servoCommand = data.substring(0, data.indexOf(',')).toInt(); // Extrae la instrucción para el servomotor
    pumpCommand = data.substring(data.indexOf(',') + 1).toInt(); // Extrae la instrucción para la bomba de agua

    // Acciona el servomotor si recibe la instrucción correcta
    if (servoCommand == 1) {
      servo.write(90); // Abre la compuerta de sales
      delay(1000); // Espera un segundo
      servo.write(0); // Cierra la compuerta de sales
    }
  }

  // Activa o desactiva la bomba de agua según la instrucción recibida
  if (pumpCommand == 1) {
    digitalWrite(WATER_PUMP, HIGH); // Activa la bomba de agua
    delay(3); // Espera 3 milisegundos
    digitalWrite(WATER_PUMP, LOW); // Desactiva la bomba deagua
    delay(7); // Espera 7 milisegundos
  } else if (pumpCommand == 0) {
    digitalWrite(WATER_PUMP, LOW); // Desactiva la bomba de agua
  }

  // Cada 1 segundo, calcula el caudal de agua en litros por minuto (L/min)
  if (millis() - oldTime >= 1000) {
    oldTime = millis();
    flowRate = (flowCounter / 450.0) * 60.0; // Los sensores de flujo normalmente envían 450 pulsos por litro
    flowCounter = 0; // Resetea el contador de flujo
  }

  // Envía los datos de los sensores cada 5 segundos
  if (millis() - msgTime >= 5000) {
    msgTime = millis();
    int humiditySensor = analogRead(HUMIDITY_SENSOR); // Lee el sensor de humedad
    int waterLevel = analogRead(WATER_LEVEL); // Lee el sensor de nivel de agua
    Serial.println(String(humiditySensor) + "," + String(waterLevel) + "," + String(flowRate)); // Envia los datos
  }
}
