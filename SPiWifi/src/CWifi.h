#include <ESPAsyncWebServer.h>
#ifndef CWIFI_H
#define CWIFI_H

void wifi();
void get_service(); 
extern const char* wifi_network_ssid;
extern const char* wifi_network_password ;
extern const char *soft_ap_ssid;
extern const char *soft_ap_password;
extern int bandera;
extern int ton;
extern int toff;
extern int pulsos;
extern String ton_t;
extern String toff_t;
extern String pulsos_t;
extern String outputString;
extern char nam[15];
extern bool estadodatos;
extern double potencia;
extern int temperatura_1;
//________WebPage para server______________________________
const char mediciones[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<style>
    body{
        text-align:center;
        background: rgb(182, 225, 205);
        
    }
    h1{
        text-align: center;
    }
    label{
        font-size: 26px;
    }
    input{
        height: 30px;
        text-align:center;
        font-size:20px;
    }
    #enviar{
        width: 150px;
        height: 45px;
        font-size:18px;
    }
    
    
</style>
<body>
<h1> Electroporador Nano Pulse</h1>
<br>
<br>
<form action="/changevalue" method="post">
    <label>Ton[ns]:<input type="text" name="ton" value="tonxx"></label>
    <br>
    <br>
    <label>Toff[us]:<input type="text" name="toff" value="toffxx"></label>
    <br>
    <br>
    <label>Separacion[us]:<input type="text" name="separacion" value=""></label>
    <br>
    <br>
    <label>Repeticiones:<input type="text" name="repeticion" value=""></label>
    <br>
    <br>
    <label>Cantidad de Pulsos:<input type="text" name="pulsos" value="pulsosxx"></label>
    <br><br>
    <input id="enviar" type="submit" value="Enviar">
</form> 
</body>
</html>
)=====";
//________WebPage para server______________________________
#endif