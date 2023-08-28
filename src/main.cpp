/*
 *  Project 41-mqtt_00 - Austral - EAM
 *
 *      File main.cpp
 */

#include <Arduino.h>

#include "wifi_ruts.h"
#include "mqtt.h"

void
setup(void)
{

    Serial.begin(BAUD);

    connect_wifi();

    init_mqtt(1);
}

void
loop(void)
{
    Serial.println("Hola");
    do_publish("ESP32/Saludo", "Hola, Mundo");
    delay(5000);

}
