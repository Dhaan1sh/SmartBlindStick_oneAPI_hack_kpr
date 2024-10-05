#include <Arduino.h>
#include <TinyGPS++.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

#define GPS_RX 16
#define GPS_TX 17

#define WIFI_SSID "realme 9 Pro 5G"
#define WIFI_PASSWORD "Sebas@132"


#define FIREBASE_HOST "locate-6001f.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyBXGTosicOjuZHpAY4WTW5JDyBKpyJtkHs" 

HardwareSerial gpsSerial(1);
TinyGPSPlus gps;

FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  firebaseConfig.database_url = FIREBASE_HOST;
  firebaseAuth.signer.credential = &firebaseAuth; 

  Firebase.begin(&firebaseConfig, &firebaseAuth);
  Serial.println("Firebase initialized");
}

void loop() {
  while (gpsSerial.available()) {
    char c = gpsSerial.read();
    gps.encode(c);
    firebaseAuth.user.email = "raghulraj9840@gamil.com";
    firebaseAuth.user.password = "Raghulraj@24";
    Firebase.begin(&firebaseConfig, &firebaseAuth);
    if (gps.location.isValid()) {
      float latitude = gps.location.lat();
      float longitude = gps.location.lng();
      Serial.print("Latitude: ");
      Serial.print(latitude, 6);
      Serial.print(" Longitude: ");
      Serial.println(longitude, 6);


      if (Firebase.setFloat(firebaseData, "location/latitude", latitude)) {
        Serial.println("Latitude updated successfully");
      } else {
        Serial.print("Error updating latitude: ");
        Serial.println(firebaseData.errorReason()); 
      }
  
      if (Firebase.setFloat(firebaseData, "location/longitude", longitude)) {
        Serial.println("Longitude updated successfully");
      } else {
        Serial.print("Error updating longitude: ");
        Serial.println(firebaseData.errorReason()); 
      }
      delay(1000);
    } 
    else {
      Serial.println("Location data not valid");
    }  
  }
  delay(1000);
}