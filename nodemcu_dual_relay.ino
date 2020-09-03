#include <ESP8266WiFi.h>                                                          // library utk wifi
#include <FirebaseArduino.h>                                                      // library utk firebase


#define WIFI_SSID "isi nama wifi dalam ni"                                          
#define WIFI_PASSWORD "isi password wifi"   

#define relay1Pin D2                                                              // relay no. 1, sambung ke pin D2 kat nodemcu
#define relay2Pin D3                                                              // relay no. 2, sambung ke pin D3 kat nodemcu
#define LED1 D5                                                                   // LED 1, warna hijau, utk wifi
#define LED2 D6                                                                   // LED 2, warna red, utk relay no. 1 (socket no. 1)
#define LED3 D7                                                                   // LED 3, warna red, utk relay no. 2 (socket no. 2)
#define FIREBASE_HOST "isi url drpd firebase projek"                              // address drpd firebase
#define FIREBASE_AUTH "isi secret key dalam nie"                                  // secret key drpd firebase

String relay1Status;
String relay2Status;

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  digitalWrite(LED1, LOW);
  Serial.println();
  Serial.println("Starting...");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      // cuba connect dgn wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {                                    // in case xleh connect, print '.' kat serial monitor
    Serial.print(".");
    digitalWrite(LED1, LOW);
    delay(500);
  }
  delay(2000);
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect ke firebase
  Firebase.setString("RELAY 1", "\"OFF\"");
  Firebase.setString("RELAY 2", "\"OFF\"");   
  digitalWrite(relay1Pin, HIGH);
  digitalWrite(relay2Pin, HIGH);         

}
void loop() {
 relay1Status = Firebase.getString("RELAY 1");                                        // baca status drpd firebase utk relay 1
 relay2Status = Firebase.getString("RELAY 2");                                        // baca status drpd firebase utk relay 1
 relay1();
 relay2();
}

void relay1()
{
   relay1Status = Firebase.getString("RELAY 1");

         if (relay1Status == "\"ON\"") 
        {  
        digitalWrite(D2, LOW);
        digitalWrite(LED2, HIGH);
        }
         else
        { 
        digitalWrite(D2, HIGH);
        digitalWrite(LED2, LOW);
        }
}

void relay2()
{
        if (relay2Status == "\"ON\"") 
        {  
        digitalWrite(D3, LOW);
        digitalWrite(LED3, HIGH);
        }
         else
        { 
        digitalWrite(D3, HIGH);
        digitalWrite(LED3, LOW);
        } 
