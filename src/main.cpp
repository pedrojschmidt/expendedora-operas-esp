/*
 *  Project 41-mqtt_00 - Austral - EAM
 *
 *      File main.cpp
 */

#include <Arduino.h>

#include "wifi_ruts.h"
#include "mqtt.h"

void
addStock(void)
{
    do_publish("addStock", "50");
}

void
setup(void)
{


    Serial.begin(BAUD);

    connect_wifi();

    init_mqtt(1);

    addStock();
}

void
loop(void)
{

    //Serial.println("Hola");
    //do_publish("ESP32/Saludo", "Hola, Mundo");
    
    //digitalWrite(23, HIGH);
    //delay(1000);
    //digitalWrite(23, LOW);
    delay(1000);
    test_mqtt();
}


