/* 
  Lettore di temperatura con l'utilizzo del sensore DHT11
  
  Robotdazero - https://www.robotdazero.it
    
  Il circuito:
  - pin 1 (Vcc)  del sensore collegato alla alimentazione
  - pin 2 (DATA) del sensore collegato al Pin 7 di Arduino
  - pin 4 (GND)  del sensore collegato alla massa di Arduino
  
  creato     12 Maggio   2018
  modificato 11 Febbraio 2020
  by sebadima 
 
  - This example code is in the public domain.
  - Questo programma viene fornito gratuitamente 
    anche per usi commerciali.
*/
 
#include "DHT.h"
#define  DHTPIN  7
#define  DHTTYPE DHT11   
 
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  //inizializza la porta seriale
  Serial.begin(9600);
  dht.begin();
}
 
void loop() {
  delay(2000);
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println(F("Non riesco a leggere il sensore DHT11!"));
    return;
  }
  Serial.print(F("%  Temperatura: "));
  Serial.print(t,1);
  Serial.print(F("°C \n"));
}
