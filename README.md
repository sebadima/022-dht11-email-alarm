
### Un programma per leggere temperatura e umidità ambientale e inviare allarmi via email usando le librerie ESP8266WiFi

### per INSTALLARE:

* git clone git@github.com:sebadima/022-dht11-email-alarm.git
* copia il file credentials_sample.h in un nuovo file credentials.h
* aggiorna il file credentials.h con i valori corretti degli account e delle password
* avvia l'IDE di Arduino, carica il file 022-dht11-email-alarm.ino e fai l'upload


Useremo il sensore **DHT11** di cui ti ripresento la **scheda tecnica** riassuntiva: 





|                            | **DHT11**                                                                                                                                                |
| -------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Protocollo di Comunicazione** &nbsp;|  one wire (a filo singolo)                                                                                                                                                 |
| **Alimentazione**     | da 3 a 5.5 V                                                                                                                                               |
| **Temperature misurabili**      | da 0º a 50 ºC +/-2 ºC                                                                                                                                       |
| **Frequenza campionamento**        | 1 secondo                                                                                                                                                 |
<br>                                                                        |
<br>
<br>

### Come partire con un programma di test e Arduino senza modulo wifi 

- Un Arduino Uno,
- Un sensore DHT11,
- Una Breadboard,
- Connettori vari o Jumpers.

<br>

> Per provare il funzionamento di base del prodotto useremo la versione "normale" di Arduino: quando sarai sicuro del funzionamento di base potremo usare il file 022-dht11-email-alarm.ino. 
Per il momento, dunque, installiamo l'hardare e usiamo un programma di prova molto semplificato per testare il funzionamento del sensore.
. 


<br>

![](https://res.cloudinary.com/sebadima/image/upload/v1591736591/001/DHT22_20Design_bb_dfydiv.jpg)

<br><br>
Per iniziare la costruzione segui il semplice schema in figura, collega alimentazione e massa e ricorda che il DHT11 deve fornire il segnale alla porta 7 di Arduino. Dai potenza solo **dopo** avere controllato tutte le connessioni e quindi collega Arduino alla porta USB del PC. A questo punto fai l' upload del programma:



### Codice del lettore di temperatura per DHT11:

<pre  class="prettyprint linenums" style="border:1px solid #d6d4d4;" >
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
</pre>


---

</br>

![](https://res.cloudinary.com/sebadima/image/upload/v1591976320/001/image_uak2rx.png)

</br>


<br> 
Dopo pochi secondi dovresti leggere sul **monitor seriale** dell'IDE le temperature rilevate dal sensore. 
<br> 
A questo punto puoi usare il programma 022-dht11-email-alarm.ino e collegandolo ad un ESP8266 collegato al sensore attraverso il pin #1.
</br>

