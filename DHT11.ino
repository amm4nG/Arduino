#include <DHT.h> //LIBRARY DHT
int relayKipas = 5;
DHT dht(D6, DHT11);  //Pin, Jenis DHT

void setup() {
  pinMode(relayKipas, OUTPUT); //set relayKipas sebagai output
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float kelembaban = dht.readHumidity(); //membaca kelembapan
  float suhu = dht.readTemperature(); //membaca suhu

  Serial.print("kelembaban: ");
  Serial.print(kelembaban);
  Serial.print(" ");
  Serial.print("suhu: ");
  Serial.println(suhu);
  if(suhu > 30){
    digitalWrite(relayKipas, HIGH);
    Serial.println("Nyala");
  }else{
    digitalWrite(relayKipas, LOW);
    Serial.println("Mati");
  }
  delay(1000);
}