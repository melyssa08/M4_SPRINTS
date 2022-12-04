#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


const char* ssid = "SHARE-RESIDENTE";
const char* password = "Share@residente";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://10.254.18.129:3001/posta/resultadoESP";

int auxiliar = 0;

String sensorReadings;
float sensorReadingsArr[1];

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(serverName);
  
  http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<200> doc;
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();


  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();


    deserializeJson(doc, payload);
    
    String  jogadorVencedor = doc[1]["playerWin"];
    String  quantidadeLinhasNoBanco = doc[0];
    lcd.print(jogadorVencedor);
    delay(2000);
    lcd.clear();
    Serial.println(quantidadeLinhasNoBanco);
    
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

void setup() {
  Serial.begin(115200);

  Wire.begin(17, 18);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
    // Turn off the blinking cursor:
  lcd.setBacklight(HIGH);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  //Send an HTTP POST request every 10 minutes
    //Check WiFi connection status

    HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(serverName);
  
  http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<200> doc;
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();


  String payload = "{}"; 
  
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();


    deserializeJson(doc, payload);
    
    String  jogadorVencedor = doc[1]["playerWin"];
    int  quantidadeLinhasNoBanco = doc[0];

    if (quantidadeLinhasNoBanco == auxiliar) {
      Serial.println("Tá sempre printando");
      Serial.println(auxiliar);
    if(WiFi.status()== WL_CONNECTED){
              
      sensorReadings = httpGETRequest(serverName);
      Serial.println(sensorReadings);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
    auxiliar = quantidadeLinhasNoBanco + 1;
 //   Serial.println(quantidadeLinhasNoBanco);
    
  // Free resources
  http.end();
    

 }
