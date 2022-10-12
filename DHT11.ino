#include <DHT.h> //import library dht untuk dapat menggunakan sensor dht
int relayKipas = 5; //pin input relay yg dihubungkan ke pin 5 arduino
DHT dht(7, DHT11);  //pin out dht11 yg dihubungkan ke pin 7 arduino, Jenis DHT yg digunakan adalah DHT11

void setup() {
  pinMode(relayKipas, OUTPUT); //setting relayKipas sebagai output
  Serial.begin(9600); //komunikasi pada serial monitor
  dht.begin(); //untuk memulai pembacaan sensor dht
}

void loop() {

  float kelembapan = dht.readHumidity(); //membaca kelembapan
  float suhu = dht.readTemperature(); //membaca suhu

  Serial.print("kelembapan: ");
  Serial.print(kelembapan);
  Serial.print(" ");
  Serial.print("suhu: ");
  Serial.println(suhu);
  
  if(suhu > 30){ //jika suhu lebih dari 30 derajat
    digitalWrite(relayKipas, HIGH); //membuat kipas nyala
    Serial.println("Kipas Nyala");
  }else{ //30 derajat atau dibawah
    digitalWrite(relayKipas, LOW); //membuat kipas mati
    Serial.println("Kipas Mati");
  }
  
}
