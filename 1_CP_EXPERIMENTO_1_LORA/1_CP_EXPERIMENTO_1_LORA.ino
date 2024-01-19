// Autora: Blanca Mendez Lopez
// Codigo para realizar el primer experimento del nodo LoRa: seccion 3.3.1 del TFG  

// Importacion de librerias
#include <MKRWAN.h>
#include "Adafruit_SHTC3.h"
#include "ArduinoLowPower.h"

// Instancia de objetos 
Adafruit_SHTC3 shtc3 = Adafruit_SHTC3(); // Permite la interaccion con el sensor SHTC3
LoRaModem LoRa; // Permite la configuracion y el control de la comunicacion LoRa

// Configuracion de los parametros de LoRa en The Things Network (TTN)
String appEui = "0000000000000000"; // EUI de la aplicacion en TTN
String appKey = "4A25DC5E841C169C262934B9FF12DE4C"; // Key de la aplicacion en TTN

// Constante que representa el intervalo de tiempo antes de realizar nuevo envio de datos, en milisegundos
const unsigned long interval = 900000; // 15 minutos

// Variables para almacenar las medidas de humedad y temperatura captadas por el sensor
sensors_event_t humidity, temp; 


// Configuracion inicial
void setup() {
  
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
  LoRa.sleep(); // Se pone el modulo LoRa en modo de bajo consumo
}

// Funcion que pone al Arduino MKR WAN 1300 en modo de bajo consumo (suspension profunda)
void GoToSleep(){
  LowPower.deepSleep(interval); // Esta en este modo durante el tiempo interval
}

