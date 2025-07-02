#include <WiFi.h>
#include "ThingSpeak.h"

// PROGRAM FOR TRANSMITTER ESP32 MODULE - TX
// author: @anvaymayekar


// WiFi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// ThingSpeak details
const char* read_api = "YOUR_API_KEY"; // (eg: KFXY0T9XExxxxxxx)
unsigned long ch_no = 9999999; // numeric (eg: 299xxxx)

// GPIO pins
const int LED = 2;

// general constants
const int size = 5;

WiFiClient client; // WiFi-based TCP client for network communication

// helper function prototypes
float* genRandom(int size);
String stringify(float number);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(LED, OUTPUT);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
  Serial.println(WiFi.localIP());
  Serial.println();
  digitalWrite(LED, HIGH);
  ThingSpeak.begin(client);
  delay(1000);
}

void loop() {
  String status;
  float* inputs = genRandom(size);
  String data;
  String value;

  for (int i = 0; i < size; i++) {
    value = stringify(inputs[i]);
    data = "Input" + String(i + 1) + ": " + value;
    ThingSpeak.setField(i + 1, value);
    Serial.println(data);
  }

  status = String(ThingSpeak.writeFields(ch_no, write_api));
  if (status == "200") {
    Serial.println("Data uploaded successfully with status code " + status);
  } else {
    Serial.println("Upload failed. HTTP status code: " + status);
  }
  Serial.println();
  delay(15000);
}

// helper functions

float* genRandom(int size) {
  static float array[5];
  for (int i = 0; i < 5; i++) {
    array[i] = float(random(0, 10000)) / 100.0;
  }
  return array;
}

String stringify(float number) {
  String output = String(number, 2);

  if (number < 10) {
    output = "0" + output;
  }
  return output;
}
