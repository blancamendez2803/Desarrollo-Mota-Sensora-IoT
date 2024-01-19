// Autora: Blanca Mendez Lopez
// Codigo para realizar el segundo experimento del nodo LoRa: seccion 3.3.2 del TFG 

// Importacion de librerias
#include <MKRWAN.h>
#include "Adafruit_SHTC3.h"

// Instancia de objetos
Adafruit_SHTC3 shtc3 = Adafruit_SHTC3(); // Permite la interaccion con el sensor SHTC3
LoRaModem LoRa; // Permite la configuracion y el control de la comunicacion LoRa

// Configuracion de los parametros de LoRa en The Things Network (TTN)
String appEui = "0000000000000000"; // EUI de la aplicacion en TTN
String appKey = "4A25DC5E841C169C262934B9FF12DE4C"; // Key de la aplicacion en TTN

// Variables para almacenar las medidas de humedad y temperatura captadas por el sensor
sensors_event_t humidity, temp;

// Constate para el pin Done del temporizador de alimentacion que al activarse le indica que la tarea se ha realizado con exito y ya puede cortar la alimentacion del nodo
const byte pinDone = 0;


// Configuracion inicial
void setup() {

  pinMode(pinDone, OUTPUT); // Se configura el pin como una salida digital
  pinMode(pinDone, LOW); // Se establece en un estado desactivado

  // Configuracion e inicializacion del modulo LoRa en la region EU868 (UE)
  if (!LoRa.begin(EU868)) {
    while (1); // Si la inicializacion no fue exitosa entra en un bucle infinito y se detiene la ejecucion del programa
  }

  // Union a TTN utilizando OTAA
  if (!LoRa.joinOTAA(appEui, appKey)) {
    while (1); // Si la inicializacion no fue exitosa entra en un bucle infinito y se detiene la ejecucion del programa
  }

  LoRa.setPort(3); // Se configura el puerto LoRa en 3

  // Inicializacion del sensor SHTC3
  if (!shtc3.begin()) {
    while (1); // Si la inicializacion no fue exitosa entra en un bucle infinito y se detiene la ejecucion del programa
  }
}

// Bucle principal
void loop() {
  SenseAndSend();
  GoToSleep();
}

// Funcion que mide la temperatura y humedad y envia el mensaje a traves de LoRa
void SenseAndSend() {
  shtc3.getEvent(&humidity, &temp); // Se realizan las medidas de temperatura y humedad
  // Se construye una cadena de mensaje que contiene las medidas
  String message = "Temperatura: " + String(temp.temperature) + ", Humedad relativa: " + String(humidity.relative_humidity);
  // Proceso de envio del mensaje
  LoRa.beginPacket(); // Inicializacion de un paquete LoRa
  LoRa.print(message); // Se imprime la cadena de mensaje en el paquete creado
  LoRa.endPacket(); // Se finaliza el paquete
  delay(8500); // Espera de 8.5s antes de cortar la alimentacion del nodo para que a TTN le de tiempo a recibir y procesar el paquete
}

// Funcion que controla el pin Done del temporizador de alimentacion para que corte la alimentacion y la vuelva a activar
void GoToSleep() {
  
  digitalWrite(pinDone, HIGH); // Se activa el pin Done por lo que se corta la alimentacion durante el tiempo establecido
                              // por la resistencia conectada al pin Delay del temporizador de alimentacion
  delay(1);
  digitalWrite(pinDone, LOW); // Pasado el tiempo establecido, se desactiva el pin Done y activa la alimentacion del nodo
  delay(1);
}