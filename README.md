# Proyecto de "Agricultura 4.0: desarrollo de una mota sensora IoT para la automatizacion del sistema de riego de la EPSE", por Blanca Mendez Lopez

[id1]: https://github.com/blancamendez2803/TFG_Blanca_Mendez_Lopez "GitHub"
[id2]: https://nubeusc-my.sharepoint.com/:f:/g/personal/blanca_mendez_rai_usc_es/EgN6YfbQlklHmgcyp4bPgzUBDJ4bfQ6rEn3yRjy1w4zukA?e=P5CcKI "OneDrive"
[id3]: https://github.com/espressif/esp-idf/tree/b3f7e2c8a4d354df8ef8558ea7caddc07283a57b/examples/bluetooth/esp_ble_mesh/directed_forwarding "GitHub Espressif Experimento Retransmision Dirigida"
[id4]: https://github.com/espressif/esp-idf/tree/b3f7e2c8a4d354df8ef8558ea7caddc07283a57b/examples/bluetooth/esp_ble_mesh/sensor_models "GitHub Espressif Cliente-Servidor Sensor"
[id5]: https://www.arduino.cc/en/software "Arduino-IDE"
[id6]: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html "ESP-IDF"

Los códigos empleados para realizar los experimentos del nodo LoRa y Wi-Fi se pueden descargar desde este repositorio de [GitHub][id1] o bien, desde [OneDrive][id2].

Los códigos empleados para realizar el experimento de "Retransmision Dirigida" del nodo BLE, se pueden descargar desde este repositorio de [GitHub Espressif Experimento Retransmision Dirigida][id3]. Sin embargo, se deben sustituir los códigos que se encuentran en './df_client/main.c', './df_client/baoard.c', './df_client/baoard.h', './df_server/main.c', './df_server/board.c'por los que se encuentran en este repositorio de [GitHub][id1] y [OneDrive][id2] en las rutas './4_PROGRAMA_1/df_client/main.c', './4_PROGRAMA_1/df_client/board.c', './4_PROGRAMA_1/df_client/board.h', './4_PROGRAMA_1/df_server/main.c', './4_PROGRAMA_1/df_server/board.c', './4_PROGRAMA_1/df_server/board.h', respectivamente.

Los códigos empleados para realizar el experimento de "Cliente - Servidor sensor" del nodo BLE, se puede descargar desde este repositorio de [GitHub Espressif Cliente-Servidor Sensor][id4].

A continuación se dedica una sección para indicar cómo descargar los entornos que se emplean, y otra, para explicar brevemente el contenido de cada carpeta que compone el proyecto.

# Entornos

## Arduino IDE
Para realizar los experimentos que se desarrollan en Arduino IDE, se debe descargar el entorno desde el siguiente enlace [Arduino-IDE] [id5], versión 2.2.1. Más adelante se explicarán las librerías que se deben descargar para cada código, sin embargo, en el menú de Arduino IDE en: 'Preferencias/Configuración/URLs adicionales de gestor de placas' se deben añadir las siguientes líneas para poder trabajar con los ESP32,

1. http://arduino.esp8266.com/stable/package_esp8266com_index.json
2. https://dl.espressif.com/dl/package_esp32_index.json
4. https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
5. https://resource.heltec.cn/download/package_heltec_esp32_index.json


## ESP-IDF
Para realizar los experimentos que se ejecutan en el entorno de ESP-IDF, se debe descargar el entorno que incluye todos los prerrequisitos y todas las dependencias necearias desde el enlace [ESP-IDF][id6], donde se elige en sistema operativo para el que se descarga (en mi caso, Windows). Una vez descargado, debe seleccionarse la version "v5.2"


# 1_CP_EXPERIMENTO_1_LORA
Este carpeta contiene el código que se ejecuta para realizar el primer experimento del nodo LoRa, sección 3.3.1. 

## 1_CP_EXPERIMENTO_1_LORA.INO
Este código se ejecuta en el experimento de la sección 3.3.1. de LoRa para enviar cada 15 minutos una medida de temperatura y humedad a The Things Network y que este se la reenvíe a ThingSpeak.

Tras realizar las conexiones del hardware especificadas en el TFG (sección 3.3.1.), para ejecutar el código se deben descargar las siguientes librerías en el propio entorno de Arduino-IDE, explicadas en la sección 3.2.1 del TFG:

1. "MKRWAN" de Arduino
2. "Adafruit SHTC3 Library" de Adafruit
3. "ArduinoLow Power" de Arduino

Configuraciones del código:
1. En este código es necesario configurar el EUI de la aplicacion de The Things Network y la App Key, para poder conectarse a la "aplicacion" creada en The Things Network. Por defecto se encuentran los empleados para este proyecto.
2. Se debe configurar el intervalo de tiempo que define la frecuencia del envio de medidas (por defecto esta en 900000 milisegundos, que equivalen a 15 minutos).
3. Se debe configurar el modulo LoRa en la región que nos encontremos (por defecto EU868).
4. Se debe definir el puerto LoRa, que por defecto se encuentra en 3.

Para ejecutar el código, se debe conectar la placa al ordenador, seleccionar la placa (en este caso: Arduino MKR WAN 1300) y el puerto donde se conecta la placa en el propio Arduino IDE, se debe verificar el código y se debe cargar en el Arduino MKR WAN 1300 (símbolos flecha hacia la derecha en Arduino IDE).
En caso de que se quiera imprimir algo por el monitor serial, se debe añadir la línea "Serial.begin(115200);" en el setup() y la velocidad del monitor serial se debe configurar a 115200 baudios.


# 2_CP_EXPERIMENTO_2_LORA
Este carpeta contiene el código que se ejecuta para realizar el segundo experimento del nodo LoRa, sección 3.3.2. 

## 2_CP_EXPERIMENTO_2_LORA.INO
Este código se ejecuta en el experimento de la sección 3.3.2. de LoRa para enviar cada 15 minutos una medida de temperatura y humedad a The Things Network y que este se la reenvíe a ThingSpeak, sin embargo la alimentacion del nodo se activa y desactiva  a través del temporizador de alimentacion.

Tras realizar las conexiones del hardware especificadas en el TFG (sección 3.3.1.), para ejecutar el código se deben descargar las siguientes librerías en el propio entorno de Arduino-IDE, explicadas en la sección 3.2.1 del TFG:

1. "MKRWAN" de Arduino
2. "Adafruit SHTC3 Library" de Adafruit

Configuraciones del código:
1. En este código es necesario configurar el EUI de la aplicacion de The Things Network y la App Key, para poder conectarse a la "aplicacion" creada en The Things Network. Por defecto se encuentran los empleados para este proyecto.
2. Se debe configurar el número de pin al que está conectado el pin Done del temporizador de alimentación.
3. Se debe configurar el modulo LoRa en la región que nos encontremos (por defecto EU868).
4. Se debe definir el puerto LoRa, que por defecto se encuentra en 3.
5. Se debe configurar una espera antes de desactivar la alimentación del nodo, por defecto este retardo es de 8.5 segundos.

Para ejecutar el código, se debe conectar la placa al ordenador, seleccionar la placa (en este caso: Arduino MKR WAN 1300) y el puerto donde se conecta la placa en el propio Arduino IDE, se debe verificar el código y se debe cargar en el Arduino MKR WAN 1300 (símbolos flecha hacia la derecha en Arduino IDE).
En caso de que se quiera imprimir algo por el monitor serial, se debe añadir la línea "Serial.begin(115200);" en el setup() y la velocidad del monitor serial se debe configurar a 115200 baudios.


# 3_CP_EXPERIMENTO_WIFI.INO
Este carpeta contiene el código que se ejecuta para realizar el experimento del nodo Wi-Fi, sección 5.3. 

## 3_CP_EXPERIMENTO_WIFI.INO
Este código se ejecuta en el experimento de la sección 5.3. de WiFi para unirse a la red Wi-Fi que se desea y en enviar cada 15 minutos una medida de la humedad de la tierra de una planta y de la temperatura ambiental al canal destinado para ello en ThingSpeak.

Tras realizar las conexiones del hardware especificadas en el TFG (sección 5.1.), para ejecutar el código se deben descargar las siguientes librerías en el propio entorno de Arduino-IDE, explicadas en la sección 5.2.1 del TFG:

1. "OneWire" de Jim Studt
2. "DallasTemperature" de Miles Burton
3. "WiFi", que ya se ha descargado anteriormente a través del enlace: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
4. "esp_sleep", que ya se ha descargado anteriormente a través del enlace: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
5. "ThingSpeak" de MathWorks

Configuraciones del código:
1. En este código es necesario configurar el pin al que está conectado el sensor DS18B20 (por defecto, el 27).
2. Se debe configurar la conexión a la red Wi-Fi introduciendo las credenciales: ssid y contraseña.
3. Se debe configurar la API Key y el ID del canal de ThingSpeak (por defecto están las empleadas para este proyecto).
4. Se debe configurar el intervalo de tiempo que define la frecuencia del envio de medidas (por defecto esta en 900000 milisegundos, que equivalen a 15 minutos).
5. Se debe configurar el pin al que está conectado el sensor SEN0308 (por defecto, el 34).

Para ejecutar el código, se debe conectar la placa al ordenador, seleccionar la placa (en este caso: DOIT ESP32 DEVKIT V1) y el puerto donde se conecta la placa en el propio Arduino IDE, se debe verificar el código y se debe cargar en el Arduino MKR WAN 1300 (símbolos flecha hacia la derecha en Arduino IDE).
En caso de que se quiera imprimir algo por el monitor serial, se debe descomentar la línea "Serial.begin(115200);" en el setup() y la velocidad del monitor serial se debe configurar a 115200 baudios.

# 4_PROGRAMA_1
Este carpeta contiene los códigos por los que hay que sustituir los del [GitHub Espressif Expermiento Retransmision Dirigida][id3] para realizar el experimento 4.3.1 del nodo BLE, mencionados en la parte superior de este documento.

Una vez se hayan sustituido los códigos del [GitHub Espressif Expermiento Retransmision Dirigida][id3] por los que se encuentran en esta carpeta, se debe compilar el proyecto. Para ello, empleando el Simbolo de Sistema del entorno ESP-ID, nos colocamos en la ruta donde se encuentra el paquete de 'df_client', e.g. 'C:\Espressif\frameworks\esp-idf-v5.2>cd examples\bluetooth\esp_ble_mesh\directed_forwarding\df_client\' y se introduce por terminal el comando 'idf.py build' para compilarlo, seguidamente con el ESP32, que actuará de nodo cliente y conectado al ordenador a través del Micro USB, se carga el código con el comando 'idf.py -p PORT flash monitor', siendo PORT el puerto en el que está el ESP32 (e.g. COM11). Se realizan las mismas acciones para el paquete 'df_server' con los ESP32 que actuarán de nodos servidores.

Configuraciones del código 'df_client/board.h':
1. Configurar el pin al que está conectado el pulsador en la configuración del nodo, por defecto es: 

    #define BUTTON_IO_NUM         GPIO_NUM_4 


#

Para cargar y ejecutar [GitHub Espressif Cliente-Servidor Sensor][id4], se realizan emplean los mismos comandos que en el caso anterior, con la diferencia de que la ruta será donde se encuentren los paquetes de este programa, e.g. 'C:\Espressif\frameworks\esp-idf-v5.2\examples\bluetooth\esp_ble_mesh\sensor_models\'

Configuraciones del código 'sensor_client/board.h':
1. Configurar el pin al que está conectado el pulsador en la configuración del nodo, por defecto es: 

    #define BUTTON_IO_NUM           4

