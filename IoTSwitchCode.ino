#include <ArduinoJson.h>

// Imports 
// Main Core WiFi Module
#include <ESP8266WiFi.h>
// HTTP Module
#include <ESP8266HTTPClient.h>

// On Board LED Pin
#define ledPin D4

// ON OF 
const int SWITCH_ON = 1;
const int SWITCH_OFF = 0;

// Wifi Creds
// Enter your wifi creds accordingly 
const char *ssid = "Wifi SSID";
const char *password = "Wifi Password";

// End point URI
char *endPoint = "http address uri";

// Setup WiFi Client
WiFiClient wifiClient;

// Setup HTTP Client
HTTPClient http;




// DoubleBlink to Show Connection
void doDoubleBlink(){
  digitalWrite(ledPin, LOW);
  delay(1000);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
  digitalWrite(ledPin, HIGH);
}

// WiFi Connect Function
void connectToWifi(){
  Serial.println("");
  Serial.println("Trying To Connect To WiFi");
  Serial.println("Connecting To : ");
  Serial.print(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Wifi Connected Successfully");
  doDoubleBlink();
}

// Request API Data using HTTP Requests
void getData(){
  if(WiFi.status() == WL_CONNECTED){
    // Make http Client
    HTTPClient http;
    // Do HTTP Request
    http.begin(endPoint);
    // Do HTTP Get Request
    int code = http.GET();
    // Check Code
    if(code > 0){
      // Get Response String
      String Payload = http.getString();
      flipSwitches(Payload);
    }
    http.end(); 
  }
}

// Flip Switches()
void flipSwitches(String Payload){
  const size_t capacity = JSON_OBJECT_SIZE(8) + 90;
  DynamicJsonBuffer jsonBuffer(capacity);
  
  JsonObject& root = jsonBuffer.parseObject(Payload);

  int switch1 = root["switch1"]; // 1
  int switch2 = root["switch2"]; // 0
  int switch3 = root["switch3"]; // 1
  int switch4 = root["switch4"]; // 0
  int switch5 = root["switch5"]; // 0
  int switch6 = root["switch6"]; // 0
  int switch7 = root["switch7"]; // 0
  int switch8 = root["switch8"]; // 1

  // Start Switch Flip

  // Switch One
  if(switch1 == SWITCH_ON){
    Serial.println("Switch One Is : ON");
    digitalWrite(ledPin, LOW);
  }
  else{
    Serial.println("Switch One Is : OFF");
    digitalWrite(ledPin, HIGH);
  }

  // Switch Two
  if(switch2 == SWITCH_ON){
    Serial.println("Switch Two Is : ON");
  }
  else{
    Serial.println("Switch Two Is : OFF");
  }

  // Switch Three
  if(switch3 == SWITCH_ON){
    Serial.println("Switch Three Is : ON");
  }
  else{
    Serial.println("Switch Three Is : OFF");
  }

  // Switch Four
  if(switch4 == SWITCH_ON){
    Serial.println("Switch Four Is : ON");
  }
  else{
    Serial.println("Switch Four Is : OFF");
  }

  // Switch Five
  if(switch5 == SWITCH_ON){
    Serial.println("Switch Five Is : ON");
  }
  else{
    Serial.println("Switch Five Is : OFF");
  }

  // Switch Six
  if(switch6 == SWITCH_ON){
    Serial.println("Switch Six Is : ON");
  }
  else{
    Serial.println("Switch Six Is : OFF");
  }

  // Switch Six
  if(switch1 == SWITCH_ON){
    Serial.println("Switch One Is : ON");
  }
  else{
    Serial.println("Switch One Is : OFF");
  }

  // Switch Seven
  if(switch7 == SWITCH_ON){
    Serial.println("Switch Seven Is : ON");
  }
  else{
    Serial.println("Switch Seven Is : OFF");
  }

  // Switch Eight
  if(switch8 == SWITCH_ON){
    Serial.println("Switch Eight Is : ON");
  }
  else{
    Serial.println("Switch Eight Is : OFF");
  }
}

void setup() {
  // State Serial OUT Band
  Serial.begin(115200);
  // State Pin Mode For Output LED
  pinMode(ledPin, OUTPUT);

  // Start Connecting To Wifi
  connectToWifi();
}

void loop() {
  
  delay(5000);
  getData();
}
