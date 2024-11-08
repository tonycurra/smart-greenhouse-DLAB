#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Replace with your network credentials
const char* ssid = "DemonstratorLab";
const char* password = "10000ways";

// NTP Client settings
const long utcOffsetInSeconds = 0; // UTC timezone
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

// Define pins for relay and motor driver
const int relayPin = 4;
const int IN1 = 1;  // GPIO1 connected to motor driver's IN1
const int IN2 = 2;  // GPIO2 connected to motor driver's IN2

// Motor speed (PWM value)
const int motorSpeed = 160; // PWM speed value (0-255)

// Relay on and off times (24-hour format)
const int relayOnHour = 6;  // Relay ON time (6 AM)
const int relayOffHour = 24; // Relay OFF time (12 AM)

// Variables for internal time tracking
unsigned long lastSyncMillis = 0;
unsigned long currentInternalTime = 0;

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println("\nConnected to WiFi.");
  Serial.print("Connected to SSID: ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void syncTimeFromNTP() {
  if (WiFi.status() == WL_CONNECTED) {
    timeClient.update(); // Attempt to get time from NTP server
    currentInternalTime = timeClient.getEpochTime(); // Set internal time to NTP time
    lastSyncMillis = millis(); // Record the time of synchronization
    Serial.println("Time synchronized from NTP successfully.");
  } else {
    Serial.println("WiFi not connected. Unable to sync time with NTP.");
  }
}

void setup() {
  Serial.begin(115200); // Initialize serial communication for debugging
  Serial.println("Starting Relay and Motor Control...");

  // Initialize WiFi and synchronize time
  initWiFi();
  timeClient.begin();
  timeClient.setUpdateInterval(60000); // Sync every 60 seconds
  syncTimeFromNTP();

  // Set up relay and motor control pins
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Start with relay off
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  Serial.println("Relay and motor pins initialized.");
}

void loop() {
  // Check if 60 seconds have passed since the last sync; if so, attempt to sync again
  if (WiFi.status() == WL_CONNECTED && (millis() - lastSyncMillis > 60000)) {
    Serial.println("Attempting to re-sync time with NTP...");
    syncTimeFromNTP();
  }

  // Update internal time based on elapsed millis when WiFi is not connected
  currentInternalTime += (millis() - lastSyncMillis) / 1000;
  lastSyncMillis = millis();

  // Calculate current hour, minute, and second based on internal time
  unsigned long currentSeconds = currentInternalTime % 86400; // Calculate seconds in a day
  int currentHour = (currentSeconds / 3600) % 24; // Extract current hour
  int currentMinute = (currentSeconds % 3600) / 60; // Extract current minute
  int currentSecond = currentSeconds % 60; // Extract current second

  // Display current time and debug information
  Serial.print("Current Time: ");
  Serial.print(currentHour); Serial.print(":");
  Serial.print(currentMinute); Serial.print(":");
  Serial.println(currentSecond);

  // WiFi and NTP sync status
  Serial.print("WiFi Status: ");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected");
    Serial.print("Time Source: NTP (");
    Serial.print(ssid);
    Serial.println(")");
  } else {
    Serial.println("Disconnected (Using internal clock)");
  }

  // Control relay and motor based on current hour
  if (currentHour >= relayOnHour && currentHour < relayOffHour) {
    digitalWrite(relayPin, HIGH); // Turn relay ON
    Serial.println("Relay is ON - Ventilation is ON");

    // Turn motor ON if relay is active
    analogWrite(IN1, motorSpeed); // Set IN1 to PWM speed
    analogWrite(IN2, 0);  // IN2 LOW for forward rotation
    Serial.println("Motor is ON");

  } else {
    digitalWrite(relayPin, LOW); // Turn relay OFF
    Serial.println("Relay is OFF - Ventilation is OFF");

    // Turn motor OFF if relay is inactive
    analogWrite(IN1, 0);
    analogWrite(IN2, 0);
    Serial.println("Motor is OFF");
  }

  // Delay to reduce the frequency of loop checks, saving resources
  delay(10000); // Check every 10 seconds for debugging
}
