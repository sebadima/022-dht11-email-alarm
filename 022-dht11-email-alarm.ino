#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <EMailSender.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include "credentials.h"
const char ssid[]               = WIFI_SSID;
const char password_wifi[]      = WIFI_PASSWD;
const char email_mittente[]     = EMAIL_MITTENTE;
const char password_email[]     = PASSWORD_EMAIL;
const char email_destinatario[] = EMAIL_DESTINATARIO;

#define DHTPIN 5         // corrisponde al Pin #1 dell ESP8266
#define INTERVALLO 360   // 360*10 = 3600 secondi (una ora) tra due allarmi
#define EMAIL_LIMITE 7   // numero massimo di email inviabili
#define TEMP_LIMITE 22   // temperatura limite per fare scattare allarme
#define DHTTYPE    DHT11 // DHT 11
//#define DHTTYPE  DHT22 // DHT 22 (AM2302)
//#define DHTTYPE  DHT21 // DHT 21 (AM2301)

uint8_t  contatore_warning  = 0;
uint8_t  contatore_email    = 0;
uint8_t  connection_state   = 0;
uint16_t reconnect_interval = 10000;

EMailSender emailSend(email_mittente, password_email);
DHT dht(DHTPIN, DHTTYPE);
 

uint8_t WiFiConnect(const char* nSSID = nullptr, const char* nPassword = nullptr)
{
    static uint16_t attempt = 0;
    Serial.print("In collegamento... ");
    if(nSSID) {
        WiFi.begin(nSSID, nPassword);
        Serial.println(nSSID);
    }
 
    uint8_t i = 0;
    while(WiFi.status()!= WL_CONNECTED && i++ < 50)
    {
        delay(200);
        Serial.print(".");
    }
    ++attempt;
    Serial.println("");
    if(i == 51) {
        Serial.print("Connessione: TIMEOUT al tentativo: ");
        Serial.println(attempt);
        if(attempt % 2 == 0)
            Serial.println("Controlla il router wifi, oltre a login e password\r\n");
        return false;
    }

    Serial.println("Connessione: Riuscita!");
    Serial.print("Con questo indirizzo IP: ");
    Serial.println(WiFi.localIP());
    return true;
}

 
void Awaits()
{
    uint32_t ts = millis();
    while(!connection_state)
    {
        delay(50);
        if(millis() > (ts + reconnect_interval) && !connection_state){
            connection_state = WiFiConnect();
            ts = millis();
        }
    }
}
 

float t = 0.0;
float h = 0.0;
unsigned long previousMillis = 0;    // will store last time DHT was updated
const long interval = 10000;  


void setup(){
  
  Serial.begin(115200);
  dht.begin();
   connection_state = WiFiConnect(ssid, password_wifi);

  if(!connection_state) 
      Awaits();        

  if (WiFi.status() == WL_CONNECTED) 
  {
  }

  EMailSender::EMailMessage message;
  message.subject = "Inizio monitoraggio";
  message.message = "Sto controllando la temperatura del locale XXX";
  EMailSender::Response resp = emailSend.send(email_destinatario, message);

  Serial.println("Status invio: ");
  Serial.println(resp.status);
  Serial.println(resp.code);
  Serial.println(resp.desc);
    
  WiFi.begin(ssid, password_wifi);
  Serial.println("In connessione al WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }

  Serial.println(WiFi.localIP());
}

 
void loop(){  

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    float newT = dht.readTemperature();
    if (isnan(newT)) {
      Serial.println("Non riesco a leggere il sensore DHT!");
    }
    else {
      t = newT;
      Serial.println(t);
    }
    float newH = dht.readHumidity();
    if (isnan(newH)) {
      Serial.println("Non riesco a leggere il sensore DHT!");
    }
    else {
      h = newH;
      Serial.println(h);
    }

    
    if (t <= TEMP_LIMITE) {
      contatore_warning++;
      Serial.println(contatore_warning);
      if (contatore_warning % INTERVALLO == 0) {
        if (contatore_email < EMAIL_LIMITE) {
          contatore_email++;
          Serial.println("sto inviando una email di avviso!");
          EMailSender::EMailMessage message;
          message.subject = "Avviso temperatura!";
          message.message = "Rilevata Temperatura di " + String(t) + " gradi, inferiore o uguale alla temperature limite di " + String(TEMP_LIMITE) + " gradi.";
          EMailSender::Response resp = emailSend.send(email_destinatario, message);
        }
      }        
    }
  }
}
