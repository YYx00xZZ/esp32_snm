/*
  Example from WiFi > WiFiScan
  Complete details at https://RandomNerdTutorials.com/esp32-useful-wi-fi-functions-arduino/
*/

#include "WiFi.h"

// Replace with your network credentials
const char* ssid = "your wifi ssid";
const char* password = "your wifi password";

const char* ssid_ap = "esp32_access_point";
const char* password_ap = "a$1234567890."; // use something more secure :)

void setup() {
  Serial.begin(115200);
  Serial.println("Setup done");
  bool our_network = scanWIFI();
  Serial.println(our_network);
  if (our_network == true) {
    // We found our network, go to sta mode
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(1000);
    }
    Serial.println(WiFi.localIP());
  } else {
    // We did not found our network, going into AP mode
    Serial.println("we did not find our network. :(");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid_ap, password_ap);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

  }
}

void loop() {
  Serial.println("sleeping for 5s");

  // WiFi.scanNetworks will return the number of networks found


  // Wait a bit before scanning again
  delay(5000);
}

bool scanWIFI() {
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("Wifi mode setup done.");
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      if (WiFi.SSID(i) == "your wifi network ssid") { //the one that you'll be searching for
        Serial.println("Found our desired network");
        return true;
      } else {
        return false;
      }
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
}