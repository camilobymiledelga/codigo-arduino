#include <WiFi.h> //primero se importa las libreria de de wifi
#include "FirebaseESP32.h" //se importa el firebase , el cual es la plataforma que se usa para recibir los datos 

//se reciben los datos : red de wifi y contraseña de esta red 
const char *ssid = "RED - OCAMPO 2.4"; // nombre de la red de wifi
const char *password = "SantajuanadearcO"; //contraseña de la red de wifi

// aqui se reciben los datos del firebase
const char *FIREBASE_HOST = "esp32-c6845-default-rtdb.firebaseio.com"; //
const char *FIREBASE_AUTH = "lsDTNsl7T1gsF7rGUMNjlr7tEDynComVQ2avyqE6";

//se declaran las variables que se estan usando en el firebase
FirebaseData firebaseData; 
String nodo = "/proyecto";  
bool iterar = true; 

void setup() {
  
  Serial.begin(9600);
  pinMode(2,OUTPUT); //pin 2 , este es el led que se encuentra en sp32
  pinMode(27,OUTPUT); //pin 27, este es el que envia la informacion al rele 5v
  
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
