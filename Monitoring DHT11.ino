#define BLYNK_PRINT Serial                         //pendeklarasian Library
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "ckZC7tbq2ufnt3F2JoWvO81Pq8ESlEcQ";  // kode authentication
char ssid[] = "vivo";                              // nama wifi
char pass[] = "Armanumar23";                       // password

#define DHTPIN D5                                  // pemilihan Pin D5 dan pendeklarasian variabel
#define DHTTYPE DHT11                              // pendeklarasian type dht yang digunakan
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

//method untuk mengirim data sensor
void sendSensor() {
  double t = dht.readTemperature();                // pembacaan suhu
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, t);
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}