#include <Arduino.h>
#include <ArduinoJson.h> //Libreria para realizar el parseo
#include "Rspi.h" // Recepcion

//Datos para transmission
String rx_tspi;
String json_s="";
char json[100];

//Confirmacion variable

bool stado= false;

//Variables parseo . Tiempo de Ton , Toff , cantidad de pulsos
int ton=0;
int toff=0;
int pulsos=0;

bool parsingdata()
{
    StaticJsonDocument<200> doc;
    rx_tspi = rx_spi();
    if(rx_tspi != NULL){
        //Bus detecta 
        json_s+=rx_tspi;
        return true;
        } else if(rx_tspi==NULL && json_s.length() != 0){
            //Serial.println(json_s);
            json_s.toCharArray(json,json_s.length() + 1);
            DeserializationError error = deserializeJson(doc,json);
            if(error){
                Serial.println("Error deserializeJson");
                return false;
                }
        //Parseo atributos
        int previouston = doc["ton"];
        int previoustoff = doc["toff"];
        pulsos = doc["p"];

        if (previouston == 0 || previoustoff == 0)
        {
            Serial.println(ton);
            Serial.println(toff);
            Serial.println(pulsos);
            json_s = "";
            return false;
        }
        ton = previouston;
        toff = previoustoff;


        //Vacion el json
        json_s = "";
        stado = true;
    }else if(rx_tspi == NULL){
        //Bus vacio
        //Serial.println("No hay data");
        stado=false;
    }
    return false;
}