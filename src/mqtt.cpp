/*
 *
 *  Project 41-mqtt_00 - Austral - EAM
 *
 *  mqtt.cpp
 *      Manage conversation with MQTT broker
 */

/*
 *  System includes
 */

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

/*
 *  Project includes
 */

#include "mqtt.h"               //  Prototypes of this module public functions      //  Actions to be called in case of subscription topics news
#include "mqtt_def.h"           //  User configuration file

#define LED1 22
#define LED2 16
#define LED3 17

/*
 *  Objects instantiations
 */

WiFiClient espClient;
PubSubClient client(espClient);

/*
 *  Private variables
 */

static char client_id[100];
static char tp_string[100];
static int board_num;
static char sub_header[50];

/*
 *  Private constants
 */

static const char *mqttServer =     BROKER_NAME;
static const int  mqttPort =        BROKER_PORT;
static const char *mqttUser =       BROKER_USER;
static const char *mqttPassword =   BROKER_PASS;

void handleLED(int ledPin) {
    digitalWrite(ledPin, !digitalRead(ledPin));
    
}


void 
callback(char *topic, byte *payload, unsigned int length) {
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
   
    Serial.println("Mensaje recibido:");
    Serial.print("Topic: ");
    Serial.println(topic);
    Serial.print("Payload: ");
    for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    }
    Serial.println();

    if(strcmp(topic, "OperasOriginales") == 0) {
        Serial.print("holis ");
        handleLED(LED1);
        delay(1000);
        handleLED(LED1);
    }
    if(strcmp(topic, "OperasChocolate") == 0) {
         Serial.print("holis 2");
        handleLED(LED2);
        delay(1000);
        handleLED(LED2);
    }
    if(strcmp(topic, "OperasFrutilla") == 0 ) {
         Serial.print("holis 3");
        handleLED(LED3);
        delay(1000);
        handleLED(LED3);
    }
}

/*
 *  Private functions
 */

/*
 *  callback:
 *      Function to asynchronously call when someone
 *      publish in broker a topic that we are subscribed
 */

/*
 *  client_connect:
 *      Connection to broker
 *      Tries until connected
 */

static void
client_connect(void)
{
    Serial.printf("Connecting to MQTT...\n");
    Serial.printf("server = %s\n",mqttServer);

    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
    while (!client.connected())
    {
        if (client.connect("Pepe"))
            Serial.printf( "%s: client %s connected\n", __FUNCTION__, client_id );
        else
        {
            Serial.printf("%s: failed with state = %d\n", __FUNCTION__, client.state());
            delay(2000);
        }
    }
    Serial.printf("Connected to %s\n", mqttServer);
}

static void
subscribe_to( const char *ptopic )
{
    int status;
 
    status = client.subscribe(ptopic);
    Serial.printf("%s -> topic: %s [status = %d]\n", __FUNCTION__, ptopic, status);
}

static void
init_subscriptions(void)
{
    subscribe_to("OperasOriginales");
    subscribe_to("OperasChocolate");
    subscribe_to("OperasFrutilla");
}

/*
 *  Public functions
 */

/*
 *  init_mqtt:
 *      All inializations needed to set variables
 *      connect to broker and initialize subscriptions
 */


void
init_mqtt(int num)
{
    client_connect();
    init_subscriptions();
}

void
do_publish(const char *ptopic, const char *msg)
{
    client.publish( ptopic, msg );
    Serial.printf( "%s: %s %s\n\r", __FUNCTION__, ptopic, msg );
}

void
test_mqtt(void)
{
    client.loop();
}




