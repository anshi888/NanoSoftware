#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "CWifi.h"
#include <EEPROM.h>

String text = "";
char nam[15]="";

char opcion;
int time_=0;
int time_2=0;
int i=0;
int addr=0;

/// Timer cada 10seg

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
 // c_usuario(); //Ingresa por puertoserial el nombre de la mdns
  wifi(); //inicilizacion de WiFi
  get_service(); //Inicio servicios para el html y para el post

}
void loop() {

 if(estadodatos==true){ //Condicional
  Serial.println(outputString);
  estadodatos=false;
  //Serial.println(outputString);
  outputString="";
 }
}

//Toff : 10000
//Ton : 