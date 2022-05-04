#include <WiFi.h>
#include "FirebaseESP32.h"

const char *ssid = "RED - OCAMPO 2.4"; // nombre de la red
const char *password = "SantajuanadearcO";

const char *FIREBASE_HOST = "esp32-c6845-default-rtdb.firebaseio.com";
const char *FIREBASE_AUTH = "lsDTNsl7T1gsF7rGUMNjlr7tEDynComVQ2avyqE6";

FirebaseData firebaseData;
String nodo = "/proyecto";
bool iterar = true;

void setup() {
  
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(27,OUTPUT);
  
  WiFi.begin(ssid, password);
  Serial.print("[Wi-Fi]...Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Firewall that allows only GET and POST requests
  //Firebase.enableClassicRequest(firebaseData, true);
}

void loop() {
  Firebase.getInt(firebaseData, nodo + "/led");
  Serial.println(firebaseData.intData());
  delay(800);
  if(firebaseData.intData()==0)
  {
    digitalWrite(2,HIGH);
    digitalWrite(27,HIGH);
  }
  else{
    digitalWrite(2,LOW);
    digitalWrite(27,LOW);
  }
 // Firebase.end(firebaseData);
}
