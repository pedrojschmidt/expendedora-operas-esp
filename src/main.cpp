/*
 *  Project 41-mqtt_00 - Austral - EAM
 *
 *      File main.cpp
 */

#include <Arduino.h>

#include "wifi_ruts.h"
#include "mqtt.h"

const int buttonPin = 4; // Pin del botón
volatile bool buttonPressed = false; // Variable para indicar si el botón ha sido presionado

void
addStock(void)
{
    do_publish("addStock", "50");
}

void IRAM_ATTR buttonISR() { // Rutina de interrupción
    buttonPressed = true;
}

void
setup(void)
{
    pinMode(buttonPin, INPUT_PULLUP); // Configurar el pin del botón como entrada con resistencia pull-up interna
    attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, FALLING); // Configurar la interrupción de hardware

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

    if (buttonPressed) { // Si el botón ha sido presionado
        do_publish("MACHINE_isOpen", "true"); // Llamar a la función do_publish()
        buttonPressed = false; // Reiniciar la variable
    }
}


