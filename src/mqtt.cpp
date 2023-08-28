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
}

void
do_publish(const char *ptopic, const char *msg)
{
    client.publish( ptopic, msg );
    Serial.printf( "%s: %s %s\n\r", __FUNCTION__, ptopic, msg );
}



