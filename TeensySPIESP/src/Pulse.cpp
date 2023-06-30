#include <Arduino.h>

const int pinRise=2;
const int pinFall=3;
const int pinStand=4;

void pulse_begin(){

    pinMode(pinRise,OUTPUT);
    pinMode(pinFall,OUTPUT);
    pinMode(pinStand,OUTPUT);

}

void pulse(int pinOut, int Ton)
{
    digitalWriteFast(pinOut,HIGH);
    delayNanoseconds(Ton);
    digitalWriteFast(pinOut,LOW);
 //   Serial.println("pulso enviado");
}
void pulse_opto(int Ton){

    digitalWriteFast(pinStand,HIGH);
    delayNanoseconds(Ton);
    digitalWriteFast(pinStand,LOW);
    
//50us bien , mayor mas peor
//25us mejor aun 
//10us no tan bien 

//-- Le cambiamos a utilizar el tranistor de 25 us a 15 us
//70 ° C primero 1000 aumento a 100°C
//mitad 100  a 35 a 45 °C
// 5 
    digitalWriteFast(pinFall,HIGH);
    delayNanoseconds(20);
    digitalWriteFast(pinFall,LOW);


}

void pulseTrain(int pinOut, int Ton, int Toff, int pulseCount)
{
    for (int i = 0; i < pulseCount; i++)
    {
        pulse(pinOut, Ton);
        if (pulseCount > 1)
            delayNanoseconds(Toff);
    }
 //   Serial.println("ok!");
}


void nanoPulse(int Ton)
{
    // digitalWriteFast(trise,HIGH);
    // delayNanoseconds(3);
    // digitalWriteFast(trise,LOW);
    if (Ton > 150)
        digitalWriteFast(pinStand,HIGH);
    // pulseTrain(trise, 3, 40, 6);
    //como los pulsos son anchos lueog del trafo
    // debo usar eso para calibrar la cantidad 
    //del tren de pulsos
    int tx = Ton/30;
    if (tx == 0)
        tx = 1;
    pulseTrain(pinRise, 3, 10, tx);
    
    //delayNanoseconds(150);

    //delayNanoseconds(200);
    digitalWriteFast(pinStand,LOW);
    if (Ton > 150)
        delayNanoseconds(100);
    pulse(pinFall, 10);
    // pulse(pinFall, 15);
    // pulseTrain(tfall, 10, 40, 2);
    // digitalWriteFast(tfall,HIGH);
    // delayNanoseconds(10);
    // digitalWriteFast(tfall,LOW);
    // delayNanoseconds(10);
}

void pulse_condition(int ton){
    int count;
        count =ceil(ton/100); //10ns off + 10ns on
        for (int i = 0; i < count; i++)
        {
            digitalWriteFast(pinRise,HIGH);
            delayNanoseconds(5);
            digitalWriteFast(pinRise,LOW);
            if (count > 1)
                delayNanoseconds(5);
        }
       delayNanoseconds(count-1);
       digitalWriteFast(pinFall,HIGH);
       delayNanoseconds(30);
        //delayNanoseconds(30);
       digitalWriteFast(pinFall,LOW);
      //  Serial.println("Ton >20");
    
}