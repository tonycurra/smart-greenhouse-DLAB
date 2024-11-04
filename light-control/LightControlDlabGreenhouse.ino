#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Replace with your network credentials
const char *ssid = "DemonstratorLab";
const char *password = "10000ways";

// Define NTP client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000); // UTC timezone, sync every 60 seconds

// Define pin for relay
const int relayPin = 4;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize the relay pin as an output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Start with relay off

  // Initialize NTP client
  timeClient.begin();
}

void loop() {
  timeClient.update();

  // Get current hour in 24-hour format
  int currentHour = timeClient.getHours();

  // Turn relay on at 8 AM and off at 9 PM
  if (currentHour >= 8 && currentHour < 21) {  // From 8 AM to before 9 PM
    digitalWrite(relayPin, HIGH);  // Relay ON
    Serial.println("Relay is ON");
  } else {
    digitalWrite(relayPin, LOW);   // Relay OFF
    Serial.println("Relay is OFF");
  }

  delay(10000);  // Update every 10 seconds
}
