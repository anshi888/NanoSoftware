#include <Arduino.h>
#include <ArduinoJson.h> //Libreria para realizar el parseo de datos
#include <Pulse.h>
String cadena="";
bool band=false;
char uart_json[100];
int p =2;
int ton=300;
int toff=100;
int contador=0;
int separacion=0;
int repeticion=1;
int aux=0;
void send_to_all(const char *name, int c)
{
  StaticJsonDocument<200> doc;
  char buf[158];
  if (c) {
    snprintf(buf, sizeof(buf), "%s received: %u\r\n", name, c);
    cadena+=char(c);
    if(c == 10){
   //   Serial.println(cadena);
      cadena.toCharArray(uart_json,cadena.length()+1);
      DeserializationError error = deserializeJson(doc,uart_json);
      if(error){
        Serial.println("Error deserializeJson");
      }
      ton=doc["ton"];
      toff=doc["toff"];
      p= doc["p"];
      separacion=doc["s"];
      repeticion=doc["r"];
      cadena="";
      }
  } else {
    snprintf(buf, sizeof(buf), "%s\r\n", name);
  }
#ifdef USB_DUAL_SERIAL
  SerialUSB1.print(buf);
#endif
#ifdef USB_TRIPLE_SERIAL
  SerialUSB1.print(buf);
#endif
  
}
void setup() {	Serial1.begin(115200);
  delay(800);
  send_to_all("Triple Serial Test", 0);
  pulse_begin();
  Serial.println("inicio");
} 
void loop() {
	if (Serial.available() > 0) {
    send_to_all("Main Serial", Serial.read());
	}
	if (Serial1.available() > 0) {
    send_to_all("Hardware Serial", Serial1.read());

	}
#if defined(USB_DUAL_SERIAL) || defined(USB_TRIPLE_SERIAL)
  if (SerialUSB1.available() > 0) {
    send_to_all("Serial USB1", SerialUSB1.read());
  }
#endif
aux=p;
  if(p== -1){
    //Serial.println("stop");
    ton=0;
    toff=0;
    p=-2;
    //pulse_opto(ton);
    //pulse_condition(ton); 
    //change v.1 con trafo
//  pulse_opto;
}
  if(p>=0){
    //nanoPulse(ton);
    while(contador<=(p-1) || p==0){
    //  pulse_condition(ton); 
    // change v.1 con trafo
      pulse_opto(ton);
      delayMicroseconds(toff);  
      contador++;
  
   Serial.print("Pulse");
  //Serial.println(contador);
      if(contador == aux && repeticion>1){
         repeticion=repeticion-1;
         contador=0;
         delayMicroseconds(separacion);
       // Serial.println("repite");
      }
    }
 // // S
   //contador2++
      contador=0;
      p=-2;
  }else{
   //Serial.println("-not-"); //- Opcional no enviar 
  // Serial.print("Ton:" + String(ton));
  // Serial.print("Toff:" + String(toff));
  // Serial.print(" Pulsos:" + String(p));
  // Serial.print(" Separacion:"+ String(separacion));
  // Serial.println(" Repeticion:" +String(repeticion));
  }
}
