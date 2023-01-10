//import library
#include <Servo.h>
#include "CTBot.h"
//setting sudut
int angle = 0; 
// defenisikan pin variable
const int trigPin = D6;
const int echoPin = D7;
const int trigPin1 = D8;
const int echoPin1 = D5;
// defenisikan variable
long duration, duration1;
int distance, distance1;
Servo servo;
CTBot myBot;
char ssid[] = "Tempat Sampah";
char pass[] = "sabangsubik23";
char token[] = "5471336517:AAH2N02IxorpiRTf66w9h4xMO7bCoLfCzA0";
const int id = 1240992293;


void setup() {
  Serial.begin(9600);  // Starts the serial communication
  servo.attach(D4);
  servo.write(angle);
  pinMode(trigPin, OUTPUT);   // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);    // Sets the echoPin as an Input
  pinMode(trigPin1, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT);   // Sets the echoPin as an Input
  //koneksikan internet
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);
  //cek koneksi
  if (myBot.testConnection()) {
    Serial.println("Koneksi Bagus");
  } else {
    Serial.println("Koneksi Jelek");
  }  
}
void loop() { 
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  distance1 = duration1 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("\tDistance 1: ");
  Serial.println(distance1);
  //pengecekan kondisi sensor
  if (distance1 < 30 && distance > 5) {
    if (distance1 == 0) {
      return;
    }
    servo.write(angle);
  } else {
    servo.write(190);
    if (distance <= 5) {
      myBot.sendMessage(id, "Tempat Sampah Anda Penuh");
      Serial.println("\tTempat sampah penuh");
    }
  }
}