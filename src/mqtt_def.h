#ifndef __MQTT_DEF_H__
#define __MQTT_DEF_H__

/*
 *  mqtt_def.h
 *
 *      This is not a traditional header file
 *      As a matter of fact, it has all the configurations for MQTT in one file
 *      Please, modify it with caution
 */



/*
 *  C4 -> broker selection
 */

#if (MQTT==0)                                       
    #define BROKER_NAME "192.168.0.141"         //  Mosquitto in local network
    #define BROKER_PORT 1883
    #define BROKER_USER ""
    #define BROKER_PASS ""
#elif (MQTT==1)
    #define BROKER_NAME "54.227.52.201"          //  Mosquitto outside local network
    #define BROKER_PORT 1883
    #define BROKER_USER ""
    #define BROKER_PASS ""
#elif (MQTT==2)
    #define BROKER_NAME "broker.mqtt-dashboard.com"    //  Remote broker by name
    #define BROKER_PORT 1883
    #define BROKER_USER ""
    #define BROKER_PASS ""
#else
    #error "Bad MQTT symbol, broker name out of range"
#endif

#endif      //  ends  __MQTT_DEF_H__

