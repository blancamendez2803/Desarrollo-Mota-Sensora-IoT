// Autora: Blanca Mendez Lopez
// Codigo para realizar el experimento del nodo Wi-Fi: seccion 5.3 del TFG 

// Importacion de librerias
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <ThingSpeak.h>
#include <esp_sleep.h>

// Configuraciones del sensor DS18B20
#define SENSOR_PIN  27 // Se define el pin al que esta conectado el sensor
OneWire oneWire(SENSOR_PIN); // Se crea el objeto OneWire asociado al pin SENSOR_PIN para establecer la conexion fisica con el sensor
DallasTemperature DS18B20(&oneWire);  // Se inicializa el objeto DallasTemperature para permitir la comunicacion con el sensor
float tempC; 


// Configuraciones del sensor SEN0308
const int AirValue = 3200; // Valor de referencia del sensor en suelo seco
const int WaterValue  = 0; // Valor de referencia del sensor en agua
//int intervals = (AirValue - WaterValue) / 3; // para establecer 3 rango de lectura de humedad: muy humedo, humedo, seco
int soilMoistureValue, humidity, humiditys = 0; 

// Configuracion para la conexion a la red Wi-Fi
const char* ssid = ""; // Reemplaza con el nombre de la red Wi-Fi a la que se conectara el ESP32
const char* password = ""; // Reemplaza con la clave de de la red Wi-Fi a la que se conectara el ESP32

// Configuracion para enviar los datos al canal de ThingSpeak
const char* WriteAPIKey = "3TYKQRC9AYI0959T"; // Reemplaza con tu clave API de ThingSpeak en caso de que quieras probar la ejecucion
const int channelID = 2365798; // Reemplaza con el ID de tu canal en ThingSpeak en caso de que quieras probar la ejecucion
WiFiClient client; // Se crea un objeto para gestionar la conexion Wi-Fi del dispositivo

// Se declaran las variables que gestionan la frecuencia del envio de los datos a ThingSpeak
unsigned long previousMillis = 0;
const unsigned long interval = 900000; // Intervalo de envio (en milisegundos)

// Configuraciones iniciales
void setup()
{ 
 
  //Serial.begin(115200);

  // Inicializacion del sensor DS18B20
  DS18B20.begin();    

  WiFi.begin(ssid, password); // Se inicia el proceso de la conexion Wi-Fi del ESP32 
  while (WiFi.status() != WL_CONNECTED) 
  {
    //Serial.println("...conectando a la wifi...");
    //Serial.println(WiFi.status()); // Devuelve el estado de la conexion Wi-Fi
    delay(10000); // Espera de 10000 milisegundos antes de reintentar conectarse a la red 
  }

  //Serial.println("...CONECTADO A LA WIFI...");
  ThingSpeak.begin(client); // Inicializa la conexion con ThingSpeak y configura el cliente para enviar datos

}

// Bucle principal
void loop(){

  MedirEnviar();
  Dormir();

}

// Funcion para medir la temperatura y humedad del suelo y enviarlas a ThingSpeak
void MedirEnviar()
{
  unsigned long currentMillis = millis(); // Se obtiene el tiempo actual en milisegundos
  
  if (currentMillis - previousMillis >= interval) { // Se verifica si ha pasado el intervalo de tiempo definido desde el ultimo envio de datos a ThingSpeak
    previousMillis = currentMillis; // Se actualiza el tiempo de referencia

    // Medida de temperatura con el sensor DS18B20 
    DS18B20.requestTemperatures(); // Se solicitan las temperaturas al DS18B20
    tempC = DS18B20.getTempCByIndex(0); // Se obtiene la temperatura en grados Celsius
  
    // Medida de humedad del suelo con el sensor SEN0308
    soilMoistureValue = analogRead(34); // Se lee el valor analogico del pin 34 (al que esta conectado el sensor al ESP32 fisicamente)
    humidity = map(soilMoistureValue, WaterValue, AirValue, 0, 100); // Se realiza un mapeado del valor leido para convertirlo en un rango de 0 a 100 
    humiditys = 100 - humidity; // Se calcula el porcentaje de humedad del suelo, que es inversamente proporcional al valor mapeado leido del sensor
    
    //Serial.println(tempC);
    //Serial.println(humiditys);
    ThingSpeak.setField(1, humiditys); // Se establece el campo 1 del canal de ThingSpeak para la humedad del suelo
    ThingSpeak.setField(2, tempC); // Se establece el campo 2 del canal de ThingSpeak para la temperatura del suelo
    ThingSpeak.writeFields(channelID,WriteAPIKey); // Se envian los datos al canal de ThingSpeak
  }
}

// Funcion que pone el ESP32 en modo de bajo consumo
void Dormir() 
{
  esp_sleep_enable_timer_wakeup(interval * 1000); // Se configura el temporizador de despertar en microsegundos
  esp_deep_sleep_start(); // El ESP32 entra en modo de bajo consumo
}