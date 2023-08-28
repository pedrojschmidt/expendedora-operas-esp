
#       Proyecto 41-mqtt_00

 Austral 2023 - Informatica Electronica - Austral
 EAMartinez

El objetivo de este proyecto es mostrar como una plaqueta realizada con ESP32 y conteniendo 4 LEDs y un pulsador, puede comunicarse con un _broker_ MQTT de manera de informar la opresión del pulsador y recibir las ordenes de prendido y apagado de los 4 LEDs que posee cada placa. De esta manera, a través del _broker_ se permite que esta placa (y hasta un total 4 placas de esta misma caracteristica) puedan formar parte de un conjunto de IoT donde el _broker_ MQTT es el elemento central de comunicación del flujo a través de todo el sistema 

##      Hardware

Para esta práctica no es necesario _hardware_ adicional
##      Conexiones

  Conectar el riel negativo del _protoboard_ (el azul)  dal GND en placa de desarrollo de ESP32.

  Para cada LED externo:  
    * De GND al cátodo del LED
    * Del ánodo del LED al resistor de 220 ohm
    * Del otro extremo del resistor de 220 ohm al GPIO respectivo  

  Conectar a los siguientes GPIOs:  
    * LED rojo a 'LED_RED'  
    * LED amarillo a 'LED_YEL'  
    * LED verde a 'LED_GRN'  


  Desde GPIO 'PUSH' a un extremo del pulsador Tact
  Del otro extremo del pulsador Tact al riel negativo

  Para identifiación de plaqueta usamos dos GPIOs _IB0_ e _IB1_:

  | IB1 | IB0 | board |
  |:---:|:---:|:-----:|
  | GND | GND |  0 |
  | GND |Open |  1 |
  | Open| GND |  2 |
  | Open|Open |  3 |

##      platformio.ini



##      Estructura del programa

  El programa, que se encuentra en el directorio _src_, está estructurado mediante módulos de C de compilación separada, con lo cual posee una estructura jerárquica claramente establecida:

####    main.cpp

  En efecto, el programa principal está realizado en el archivo _main.cpp_ que, como se puede observar tiene una estructura muy sencilla; siendo el programa principal, todas las acciones que realiza están vinculadas a tres objetivos claramente definidos:

  * El acceso a la conexión WiFi.   (_wifi_ruts.h_)
  * La comunicación con el _broker_ MQTT (_mqtt.h_)

  Por ello se incluyen los archivos _.h_ que se mencionan.

  Existen solo dos funciones en dicho programa principal:

  * _setup_: permite la inicialización de los módulos que depende de este programa
  * _loop_: Esta aplicación solamente publica un mensaje "Hola Mundo" en el _topic_ ESP32/Saludo en forma periódica. El objetivo es ejemplificar el mecanismo de publicación/subscripción y servir de base para futuros desarrollos.

####    Manejo de WiFi

  Aparte del archivo de encabezamiento _wifi_ruts.h_ que posee los prototipos de las funciones de manejo de WiFi, se encontrará el archivo _wifi_ruts.cpp_ que justamente tiene la implementación de dichos prototipos.
  También existe un archivo de configuración _wifi_data.h_ donde se pueden colocar la identificación y la clave para el acceso de hasta tres lugares que sean usuales en el trabajo de desarrollo del grupo; cual de esos lugares en definitiva se conectará en el momento de ejecución, depende del símbolo _WIFI_ que se encuentra definido en _plaformio.ini_.

####    Manejo de la comunicación con el _broker_ MQTT

  Los nombres de los archivos vinculados a este ítem  comienzan con _mqtt_, de los cuales pueden destacarse los siguientes:

  _mqtt.cpp_: implementa las funciones principales cuyos prototipos están en _mqtt.h_, archivo que, a su vez, fué incluído dentro de _main.cpp_ como ya se explico más arriba.

  Se dispone de un archivo adicional referido a _mqtt_ cual es _mqtt_def.h_: este archivo, incluído en _mqtt.cpp_, es particularmente importante, ya que sirve para hacer configuraciones en relación con el _broker_.

##      Configuración del proyecto

  El proyecto se configura mendiante tres elementos:

#### Configuración mediante el archivo _mqtt_def.h_

  **Broker selection**: También para comprender que el _broker_ MQTT puede estar ubicado en distintos lugares, existen 3 selecciones del _broker_ en particular a usar, la cual se puede seleccionar mediante el símbolo _MQTT_ que se define en _platformio.ini_. Aquí, en realidad, se debe colocar la forma de acceso y validación de cada uno de los 3 _brokers_ a usar.  

#### Configuración mediante _platformio.ini_

  Esta configuración acompaña las anteriores y ya se explicó como influye en la configuración total.

##  Prueba con broker MQTT mosquitto

Para ejemplificar la prueba realizada, se ha usado un broker _mosquitto_ sobre una computadora con Ubuntu 18.04 que se encontraba en la misma red que los microcontroladores ESP32 utilizados.
Las configuraciones son las que se muestran en el código que esta en _github_ tal cual queda después de clonarse.
El único cambio que deberia hacerse es el número de IP del broker _mosquitto_ 


####    Comandos de los clientes de _mosquitto_

Existen dos clientes distintos de _mosquitto_:

* Uno para publicar novedades, _mosquitto_pub_
* Uno para suscribirse a novedades, _mosquitto_sub_


####    Conexión a WiFi

No olvide cambiar en _mqtt_def.h_ la identificación así como la clave de los puntos de conexión de WiFi donde Ud. desarrolla su actividad (hay hasta tres disponibles) y cambiar concordantemente la definción de cual está usando en _platformio.ini_ mediante el símbolo _WIFI_


##  Tutoriales

### MQTT

  [MQTT: The Standard for IoT Messaging - from mqtt.org](https://mqtt.org/)

  [10 Free Public MQTT Brokers(Private & Public)](https://mntolia.com/10-free-public-private-mqtt-brokers-for-testing-prototyping/)

  [mosquitto download](https://mosquitto.org/download/)

## Videos

###  MQTT

 [Desentrañando MQTT - ¿Cómo funciona?](https://www.youtube.com/watch?v=Tb1t6GKJ0r0)

 [MQTT & ESP32.: (1). Ejemplo sensor de temperatura DHT22](https://www.youtube.com/watch?v=pEv90rO_MD0&list=RDLVx5GML1FqcTQ&index=3)


