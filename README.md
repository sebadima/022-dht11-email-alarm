
### A simple  demo to email readings from sensor DHT11 using ESP8266

to INSTALL:

* git clone git@github.com:sebadima/022-dht11-email-alarm.git
* copy credentials_sample.h in a new file credentials.h
* start arduino IDE and load the main source  022-dht11-email-alarm.ino

written using this advice from:

https://arduino.stackexchange.com/questions/40411/hiding-wlan-password-when-pushing-to-github

In un [articolo precedente](https://www.robotdazero.it/blog/018-i-migliori-sensori-di-temperatura-per-il-tuo-robot/) del nostro blog vi abbiamo presentato una rassegna dei più comuni sensori termici per Arduino e in questo post vedremo come utilizzarne uno per realizzare una stazione di monitoraggio semplice e robusta.
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

### I componenti che ci serviranno per la realizzazione:

- Un [Arduino Uno](https://www.amazon.it/s?k=arduino&__mk_it_IT=%C3%85M%C3%85%C5%BD%C3%95%C3%91&ref=nb_sb_noss_1), se non sai quale scegliere leggi [qui](https://www.robotdazero.it/blog/009-la-guida-definitiva-per-scegliere-il-tuo-arduino/),
- Un sensore [DHT11](https://www.amazon.it/s?k=DHT11&__mk_it_IT=%C3%85M%C3%85%C5%BD%C3%95%C3%91&ref=nb_sb_noss_2),
- Una [Breadboard](https://www.amazon.it/s?k=breadboard+arduino&__mk_it_IT=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=1NVTYI16ZUH03&sprefix=brea%2Caps%2C209&ref=nb_sb_ss_i_3_4), per approfondire leggi [qui](https://www.robotdazero.it/blog/008-iniziare-con-le-bredboard/),
- Connettori vari o [Jumpers](https://www.amazon.it/s?k=jumper+arduino&__mk_it_IT=%C3%85M%C3%85%C5%BD%C3%95%C3%91&ref=nb_sb_noss_1).

<br>

> Per questo prototipo potrai usare la versione "normale" di Arduino, ma se vorrai piazzare il prodotto in ambienti "difficili" ti consiglio di proteggere la scheda con un box in plastica. 


<br>
Se vuoi una dritta ti suggerisco di studiare con calma questa [pagina](https://www.robotdazero.it/blog/013-arduino-adesso-in-versione-industriale/) del blog dove mostriamo un Arduino della  [Mouser](https://www.mouser.it/) con un contenitore di sicurezza a Norme Iso, indispensabile in ambienti ostici o lievemente corrosivi.

<br>

![](https://res.cloudinary.com/sebadima/image/upload/v1591736591/001/DHT22_20Design_bb_dfydiv.jpg)

<br><br>
Per iniziare la costruzione segui il semplice schema in figura, collega alimentazione e massa e ricorda che il DHT11 deve fornire il segnale alla porta 7 di Arduino. Dai potenza solo **dopo** avere controllato tutte le connessioni e quindi collega Arduino alla porta USB del PC. A questo punto fai l' [upload](https://www.robotdazero.it/blog/004-come-installare-ide-di-arduino/) del programma:



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

<br> 
Dopo pochi secondi dovresti leggere sul **monitor seriale** dell'IDE le temperature rilevate dal sensore. 
</br>
</br>
![](https://res.cloudinary.com/sebadima/image/upload/v1591976320/001/image_uak2rx.png)
</br>
Come vedi la temperatura resta stabile sui 23°C ma dopo avere tenuto il sensore tra le dita per qualche secondo sale verso i 24~25°C per poi ridiscendere lentamente.
#### Se tutto funziona come previsto hai completato con successo la versione preliminare del circuito. Nel prossimo post vedremo come inviare un report orario delle temperature o un allarme su un normale indirizzo email.

