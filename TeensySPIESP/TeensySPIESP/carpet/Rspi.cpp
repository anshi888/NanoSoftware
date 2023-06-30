#include <Arduino.h>
#include "SPI.h" //Libreria SPI

//************************************************************************************************//
// Ultima modificacion: 27/06/2022 
// Rspi.cpp <y> Rspi.h tiene como objetivo permitir el guardado de la recepcion de datos proveniente
// del microcontrolador de transmission.
//************************************************************************************************//

const int slaveSelectPin = 10; //Activa el pin del esclavo y selecciona


//************************************************************************************************//
//Funcion configuracion de salida/estado y inicializacion del SPI
void spi_begin(){
    pinMode (slaveSelectPin, OUTPUT);
    digitalWrite(slaveSelectPin, HIGH);
    SPI.begin();
    }
//************************************************************************************************//

//************************************************************************************************//
//Funcion recibe los datos transmitodos por el el microcontrolador ESP32
String rx_spi(){
    //inicia vacio
    String datarx="";
    int rx_ascii=0;
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    //SS en estado en bajo para seleccionar el esclavo;
    digitalWrite(slaveSelectPin, LOW);
    //Recibe el dato en ascii
    rx_ascii=SPI.transfer(0);
    if(rx_ascii != 46 && rx_ascii!=93 && rx_ascii!=NULL && 97>= rx_ascii <= 125 && 46>=rx_ascii<=57){  
        //Serial.println(char(recibido));
        datarx+=char(rx_ascii);
        }
    //SS en estado en alto para deseleccionar esclavo
    
    digitalWrite(slaveSelectPin, HIGH);
    //Liberar control del puerto SPI
    SPI.endTransaction();
    //Retorno datarx
    return datarx;
    }

//****************************************************************************************************//
