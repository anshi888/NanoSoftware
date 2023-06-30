#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
//Headers
#include "CWifi.h"
///credenciales conexion
const char *wifi_network_ssid = "STAMM-311";
const char *wifi_network_password ="Stammnet311";
const char *soft_ap_ssid = "NanoTeensy";
const char *soft_ap_password = "pastelitos97";

String outputString = "";
int ton=100;
int toff=1000;
int pulsos=1;
int separacion=1;
int repeticion=1;
double potencia;

String ton_t="";
String toff_t="";
String pulsos_t="";
String separacion_t="";
String repeticion_t="";

int bandera=0;
char pagechar[2500];
bool estadodatos= false;

///Contador fitisio
int temperatura_1=0;
int temperatura_2=0;
//boleano
AsyncWebServer *server;
IPAddress ip(10,31,110,91);     
IPAddress gateway(10,31,110,1);   
IPAddress subnet(255,255,255,0);  
void wifi(){
    int tiempoespera=0;
    WiFi.mode(WIFI_MODE_APSTA);
    WiFi.softAP(soft_ap_ssid, soft_ap_password);
    WiFi.config(ip, gateway, subnet);

    WiFi.begin(wifi_network_ssid, wifi_network_password);
    while ((WiFi.status() != WL_CONNECTED ) && (tiempoespera<20)) 
    {
      delay(500);
      tiempoespera++; 
    }
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  Serial.print("ESP32 IP as soft AP: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("ESP32  IP on the WiFi network: ");
  Serial.println(WiFi.localIP());
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());

  }

  void updatePage()
{
    String page = (String)mediciones;
    page.replace("tonxx", (String)ton);
    page.replace("toffxx", (String)toff);
    page.replace("pulsosxx", (String)pulsos);
    page.toCharArray(pagechar, 2500);
}

//Variables del formulario para realizar el METODO POST
 void handleFormText(AsyncWebServerRequest *request)
{
    ton_t = request->arg("ton"); 
    ton= ton_t.toInt();
    toff_t = request->arg("toff");
    toff= toff_t.toInt();
    pulsos_t=request->arg("pulsos");
    pulsos= pulsos_t.toInt();
    separacion_t=request->arg("separacion");
    separacion=separacion_t.toInt();
    repeticion_t=request->arg("repeticion");
    repeticion=repeticion_t.toInt();
    bandera = 1;
    outputString="{ton:"+(String)ton+",toff:" +(String)toff+",p:"+(String)pulsos+",r:"+(String)repeticion+",s:"+(String)separacion+"} ";
    estadodatos=true;
    updatePage();
    request->redirect("/");

}
void get_service(){
   updatePage();
   server = new AsyncWebServer(80);
    //---------- GET ------------------------//
      server->on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (ON_STA_FILTER(request)) {
        request->send_P(200, "text/html", pagechar);
      return;
    } else if (ON_AP_FILTER(request)) {
        request->send_P(200, "text/html",  pagechar);
      return;
    }
        request->send_P(200, "text/html",  pagechar);
  });
   server->on("/stop", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (ON_STA_FILTER(request)) {
        request->send(200, "text/html",String("stop"));
      return;
    } else if (ON_AP_FILTER(request)) {
        request->send(200, "text/html",String("stop"));
      return;
    }
  });
  server->on("/status", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (ON_STA_FILTER(request)) {
        request->send(200, "text/html",String("1"));
      return;
    } else if (ON_AP_FILTER(request)) {
        request->send(200, "text/html",String("1"));
      return;
    }
  });
  //--------------POST------------------
  server->on("/changevalue", HTTP_POST, handleFormText);
  server->onNotFound([](AsyncWebServerRequest *request) {
      request->send(400, "text/plain", "Not found");
   });
  server->begin(); //abro el server_
  }

