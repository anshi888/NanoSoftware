#include <Arduino.h>
#include "Parsing.h"
String palabra="";
char command = ' ';

//Funcion leer desde consola

bool readUSBCommand()
{
    if (Serial.available())
    {
        palabra = Serial.readStringUntil('\n');
        command = palabra[0];
        //ton = palabra.substring(2).toInt();
        //Serial.println(ton);
        return true;
    }
    return false;
}

//Menu de opciones - 
void menu(char command){

    switch(command){

        case 'p':
                    Serial.println("seteado");
                    ton=300;
                    toff=10;
                    pulsos=1;
                    break;
        case 't':
                    Serial.println("Opcion2");
                    break;
        case 'c':
                    Serial.println("Opcion3");
                    break;
        default:
                    break;
    }
}