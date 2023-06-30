#include <SPI.h>
const int slaveSelectPin = 10;
String guardar;
String texto;
int contador=0;
void setup() {
  pinMode (slaveSelectPin, OUTPUT);
  digitalWrite(slaveSelectPin, HIGH);
  SPI.begin();
 
}
void loop() {
      texto=envio();
      Serial.print(texto);
      delay(300);
}
String envio() {
  guardar="";
  int recibido= 0;
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  // pone SS bajo para seleccionar esclavo:
  digitalWrite(slaveSelectPin, LOW);
  recibido=SPI.transfer(0);
  printf("%d",recibido);
  //Serial.printf("result = %d \n",recibido);
  if(recibido != 46 && recibido!= NULL){
    //Serial.println(char(recibido));
    guardar+=char(recibido);
  }
  // pin SS alto para deseleccionar esclavo:
  digitalWrite(slaveSelectPin, HIGH);
  // libero control de puerto SPI
  SPI.endTransaction();
  return guardar;
}