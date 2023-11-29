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

void 
callback(char *topic, byte *payload, unsigned int length) {
    Serial.println("Mensaje recibido:");
    Serial.print("Topic: ");
    Serial.println(topic);
    Serial.print("Payload: ");
    for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    }
    Serial.println();

    if(topic == "OperasOriginales") {
        digitalWrite(22, HIGH);
        delay(1000);
        digitalWrite(22, LOW);
    }
    if(topic == "OperasChocolate") {
        digitalWrite(23, HIGH);
        delay(1000);
        digitalWrite(23, LOW);
    }
    if(topic == "OperasFrutilla") {
        digitalWrite(24, HIGH);
        delay(1000);
        digitalWrite(24, LOW);
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

