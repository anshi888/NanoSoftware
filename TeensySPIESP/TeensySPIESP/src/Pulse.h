#ifndef PULSE_H
#define PULSE_H

void nanoPulse(int Ton);
void pulseTrain(int pinOut, int Ton, int Toff, int pulseCount);
void pulse(int pinOut, int Ton);
void pulse_begin();
void pulse_condition(int ton);

#endif