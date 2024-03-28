#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>  // Tambahkan pustaka ArduinoJson

const char* ssid = "realme C53";
const char* password = "sabangsubik";

const char* csrfTokenEndpoint = "http://192.168.110.65:8000/csrf-token";  // Ganti dengan URL untuk mendapatkan CSRF token
String csrfToken;

void setup() {

  Serial.begin(115200);
  delay(4000);  //Delay needed before calling the WiFi.begin

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {  //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");
}

void loop() {
  digitalWrite(2, HIGH);
  if (WiFi.status() == WL_CONNECTED) {  //Check WiFi connection status

    HTTPClient http;

    http.begin(csrfTokenEndpoint);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      csrfToken = http.getString();
    } else {
      Serial.print("Error on getting CSRF token: ");
      Serial.println(httpResponseCode);
    }

    http.begin("http://192.168.110.65:8000/post");       //Specify destination for HTTP request
    http.addHeader("Content-Type", "application/json");  // Ganti content-type menjadi
    http.addHeader("X-CSRF-TOKEN", csrfToken);

    // Buat objek JSON
    StaticJsonDocument<200> doc;  // Sesuaikan ukurannya sesuai kebutuhan Anda
    doc["title"] = "Ini adalah data";

    // Serialize JSON ke string
    String jsonString;
    serializeJson(doc, jsonString);

    // Kirim data JSON dalam permintaan POST
    httpResponseCode = http.POST(jsonString);

    if (httpResponseCode > 0) {

      String response = http.getString();  //Get the response to the request
      Serial.print("Status code : ");
      Serial.println(httpResponseCode);  //Print return code
      Serial.println(response);          //Print request answer
    }else{
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();  //Free resources
  } 
  else {
    Serial.println("Error in WiFi connection");
  }
  delay(10000);  //Send a request every 10 seconds
}