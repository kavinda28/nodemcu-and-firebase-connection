#include <FirebaseArduino.h>
#include <DHT.h>

#include  <ESP8266WiFi.h>

#define FIREBASE_HOST "............."
#define FIREBASE_AUTH "............."
#define WIFI_SSID "............." // Change the name of your WIFI
#define WIFI_PASSWORD "............." // Change the password of your WIFI

#define DHTPIN 14    // Data Pin of DHT 11 , for NodeMCU D5 GPIO no. is 14

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
int c=0,d=0;
float IRout;
void setup() {
Serial.begin(9600);
 pinMode(D7, INPUT);// set pin as input
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   dht.begin();
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
}

void loop() {
  //IR
 int detect = digitalRead(D7);// read obstacle status and store it into "detect"
  if(detect == LOW){
    IRout=1;
   Serial.println("Obastacle on the way"); 
  }else{
    IRout=0;
   Serial.println("All clear");  
  }
 // delay(100);

  
  Firebase.setFloat("COUNT",c);
  Serial.println (c);
  Firebase.setFloat("tance",d);
  Firebase.setFloat("IRsensor/IR1",IRout);

  
  d=d+5;
  c++;
  delay(100);
}
