#include <WiFi.h>
#include <ThingSpeak.h>
#include <Adafruit_SSD1306.h>

// PROGRAM FOR RECEIVER ESP32 MODULE - RX
// author: @anvaymayekar


// OLED constants
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  // Initializes 128x64 OLED via I2C using Wire

// WiFi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// ThingSpeak details
const char* read_api = "YOUR_API_KEY"; // (eg: KFXY0T9XExxxxxxx)
unsigned long ch_no = 9999999; // numeric (eg: 299xxxx)

// Credentials for testing only — use secure methods (e.g., header file) in production.

// GPIO pins
const int LED = 2;
const int BUZZER = 4;

// general constants
const int size = 5;

WiFiClient client;  // WiFi-based TCP client for network communication

// helper function prototypes
String stringify(float number);
String formatUTCtoIST(String utcTime);

void setup() {

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Initialize the OLED display with I2C address 0x3C
  // If initialization fails, print error and halt the program
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)  // Infinite loop to stop execution
      ;
  }

  // Wait for WiFi
  Serial.print("Connecting to WiFi");
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Connecting to WiFi...");
  display.display();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.println(WiFi.localIP());
  Serial.println();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Connected to Wifi!");
  display.println(WiFi.localIP());
  display.display();
  digitalWrite(LED, HIGH);

  // Start ThingSpeak
  ThingSpeak.begin(client);
  delay(1000);
}

void loop() {
  int status;
  String value;
  String time;
  String text;

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  status = ThingSpeak.readMultipleFields(ch_no, read_api);

  if (status == 200) {

    time = formatUTCtoIST(ThingSpeak.getCreatedAt());

    display.println(time);
    display.println();
    Serial.print(time);
    Serial.print(" | Status Code: ");
    Serial.println(status);
    for (int i = 0; i < size; i++) {
      value = stringify(ThingSpeak.getFieldAsFloat(i + 1));
      String text = "Input" + String(i + 1) + ": " + value;
      Serial.println(text);
      display.println(text);
    }
  } else {
    Serial.print("ThingSpeak Read Error. HTTP code: ");
    Serial.println(status);
    display.println("Error reading data!");
  }

  Serial.println();
  display.display();
  digitalWrite(BUZZER, HIGH);
  delay(1000);
  digitalWrite(BUZZER, LOW);
  delay(14000);
}

// helper functions

String stringify(float number) {
  String output = String(number, 2);

  if (number < 10) {
    output = "0" + output;
  }
  return output;
}

String formatUTCtoIST(String utcTime) {
  // Initial check
  if (utcTime.length() == 0) return "No data yet!";

  // Parse parts from "YYYY-MM-DD HH:MM:SS"
  int year = utcTime.substring(0, 4).toInt();
  int month = utcTime.substring(5, 7).toInt();
  int day = utcTime.substring(8, 10).toInt();
  int hour = utcTime.substring(11, 13).toInt();
  int minute = utcTime.substring(14, 16).toInt();

  // Add IST offset (+5:30)
  hour += 5;
  minute += 30;

  if (minute >= 60) {
    minute -= 60;
    hour += 1;
  }

  if (hour >= 24) {
    hour -= 24;
    day += 1;
    // Very basic date increment — no month-end handling
  }

  // Format day
  String dayStr = (day < 10) ? "0" + String(day) : String(day);
  String hourStr = (hour < 10) ? "0" + String(hour) : String(hour);
  String minStr = (minute < 10) ? "0" + String(minute) : String(minute);

  // Month name lookup
  String months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                      "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

  String formatted = dayStr + "-" + months[month - 1] + " " + hourStr + ":" + minStr + " IST";
  return formatted;
}
