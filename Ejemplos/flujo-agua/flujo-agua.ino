/*

Creado por: Hugo Escalpelo
Fecha: 20230628

Este programa es para probar el sensor de flujo de agua, el cual funciona por pulsos. 
El siguiente programa calcula los litros por minuto segun el tiempo entre pulsos detectados.

Conexiones:

ESP32CAM    FTDI
5v----------VCC
GND---------GND
UoR---------Tx
UoT---------Rx

ESP32CAM    Sensor de flujo de agua
5v----------5v
GND---------GND
GPIO13------Signal

*/

#define FLOW_SENSOR 13 // El sensor de flujo de agua está conectado al GPIO4
volatile int flowCounter; // Este entero volátil almacena el número de pulsos del sensor de flujo.

// Esta es la función de interrupción que se activa cada vez que el sensor de flujo envía un pulso.
void IRAM_ATTR pulseCounter() {
  flowCounter++;
}

void setup() {
  Serial.begin(115200); // Inicia la comunicación serial a 115200 bps
  pinMode(FLOW_SENSOR, INPUT_PULLUP); // Configura el pin del sensor de flujo como entrada
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR), pulseCounter, RISING);  // Asocia la función de interrupción pulseCounter al pin del sensor de flujo
}

void loop() {
  flowCounter = 0; // Resetea el contador de flujo al inicio de cada ciclo de lazo.
  delay(1000); // Espera un segundo (durante este tiempo, la función de interrupción estará contando los pulsos del sensor de flujo).

  // Ahora, calcula el caudal de agua en litros por minuto (L/min).
  // Los sensores de flujo normalmente envían entre 450 y 450 pulsos por litro.
  // Este valor puede variar dependiendo del sensor específico que se utilice, consulta la documentación del tuyo para obtener el valor exacto.
  float flowRate = (flowCounter / 450.0) * 60.0;

  Serial.print("Caudal: ");
  Serial.print(flowRate);
  Serial.println(" L/min");
}