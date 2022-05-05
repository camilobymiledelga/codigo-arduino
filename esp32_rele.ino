#include <WiFi.h> //se importa las libreria de de wifi
#include "FirebaseESP32.h" //se importa el firebase , el cual es la plataforma que se usa para recibir los datos 

//se reciben los datos : red de wifi y contraseña de esta red 
const char *ssid = "RED - OCAMPO 2.4"; // nombre de la red de wifi
const char *password = "SantajuanadearcO"; //contraseña de la red de wifi

// aqui se reciben los datos del firebase
const char *FIREBASE_HOST = "esp32-c6845-default-rtdb.firebaseio.com"; //
const char *FIREBASE_AUTH = "lsDTNsl7T1gsF7rGUMNjlr7tEDynComVQ2avyqE6";

//se declaran las variables que se usan en el firebase
FirebaseData firebaseData; //esta es la declaracion del objeto de la clase firebase
String nodo = "/proyecto";  
bool iterar = true; 

void setup() {
  
  
  pinMode(2,OUTPUT); //pin 2 , este es el led que se encuentra en sp32
  pinMode(27,OUTPUT); //pin 27, este es el que envia la informacion al rele 5v
  
  WiFi.begin(ssid, password); //se recibe el nombre de la red y contraseña de esta
  Serial.print("[Wi-Fi]...Connecting"); //en esta parte imprime que se esta conectando, 
  while (WiFi.status() != WL_CONNECTED) // wifi.status: devuelve el estado de la conexion 
  {                                           
    Serial.print(".");//no se conecto a la red 
    delay(300); // delay(retardoMilisegundos) ;
  }
  Serial.println();
  Serial.print("Connected with IP: "); //aqui solo se imprimi la direccion ip y que se conecto a la red
  Serial.println(WiFi.localIP()); //wifi.localIp(): Obtiene la dirección IP del escudo WiFi y la imprime
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); //ahora es el firebase es el que recibe los datos , como el wifi.begin()
  Firebase.reconnectWiFi(true);

  //Firewall that allows only GET and POST requests
  //Firebase.enableClassicRequest(firebaseData, true);
}

void loop() {
  Firebase.getInt(firebaseData, nodo + "/led"); //aqui el firebase tiene un nodo  el cual es la varible que desde el firebase se cambia 
                                                //a un 0 o un 1
  Serial.println(firebaseData.intData());
  delay(800);
  if(firebaseData.intData()==1)
  {
    digitalWrite(2,HIGH); //si desde el firebase se recibe un 1 , entonces las luces se encenderan
    digitalWrite(27,HIGH); // y el digital write  permite escribir valores lógicos digitales en un pin de Salida en la tarjeta de Arduino.
  }
  else{
    digitalWrite(2,LOW); //si desde el firebase se recibe un 0, entonces las luces se apagaran
    digitalWrite(27,LOW);
  }
 
}
