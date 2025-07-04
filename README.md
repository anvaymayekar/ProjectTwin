
# 🚀 ProjectTwin: ESP32 TX/RX IoT System with OLED and ThingSpeak Integration

<br>

A complete dual-node ESP32-based 🌐 Internet of Things system for cloud-connected data exchange. The project implements one ESP32 as a **transmitter** (TX) that periodically sends 5 string-based values to a ThingSpeak channel, and another ESP32 as a **receiver** (RX) that fetches this data, validates network and peripheral status, and displays results on both the Serial Monitor and a 128x64 OLED screen. <br>

> 🔧 This project was developed as part of a practical exercise during the **AICTE SAKEC IDEALAB Summer Internship Program 2025**, reflecting core concepts of embedded systems and IoT communication.

---

## 📌 Note

> ⚠️ This implementation uses only the official `ThingSpeak` library and `WiFi.h`. No `ArduinoJson` or external data parsing is used.
> 🖥️ Ensure the receiver OLED is properly connected via I2C (typically SDA to GPIO 21, SCL to GPIO 22 on ESP32).
> 🕒 A 15-second delay is maintained as per ThingSpeak rate limits.
> 💡 Internal blue LED on each ESP32 acts as a WiFi connection indicator.
> 🔔 On the RX node, a buzzer on GPIO 4 gives a 1s beep each time new data is received.

---

## 📁 File Structure

```
- root
    > TX_Node
        > TX_Node.ino        // 🔼 Transmitter ESP32 code
    > RX_Node
        > RX_Node.ino        // 🔽 Receiver ESP32 code
    > README.md              // 📘 This file
    > images
        > (Optional circuit diagrams / OLED previews)
```

---

## 🧠 System Overview

### ✉️ Transmitter (TX Node)

* Sends 5 randomly generated string values
  (e.g., `https://api.thingspeak.com/update?api_key=...`)
* Uses `ThingSpeak.writeField()` to push data 📤
* Implements digit formatting, floating point control, and padding
* Enforces a 15-second delay between transmissions ⏳
* Illuminates onboard blue LED 🔵 when connected to WiFi

---

### 📰 Receiver (RX Node)

* Connects to WiFi, prints IP and connection status 📶
* Retrieves 5 values using `ThingSpeak.readStringField()`
* Checks OLED initialization and displays fallback errors ❌
* Shows current time, data values, and status on Serial & OLED
* Activates buzzer 🔔 on pin 4 for 1 second upon each successful retrieval

---

## 🛠️ Tools & Technologies

![ESP32](https://img.shields.io/badge/ESP32-323232.svg?style=for-the-badge\&logo=espressif\&logoColor=white)
![Arduino IDE](https://img.shields.io/badge/Arduino_IDE-00979D.svg?style=for-the-badge\&logo=arduino\&logoColor=white)
![ThingSpeak](https://img.shields.io/badge/ThingSpeak-003366.svg?style=for-the-badge\&logo=mathworks\&logoColor=white)
![OLED 128x64](https://img.shields.io/badge/OLED-128x64-blue?style=for-the-badge)
![Adafruit](https://img.shields.io/badge/Adafruit-Supported-blue?style=for-the-badge\&logo=adafruit\&logoColor=white)

---

## ⚙️ Hardware Requirements

🔌 **2× ESP32 Dev Boards** (DOIT / NodeMCU)
🖥️ **1× 128x64 I2C OLED Display (SSD1306)**
🔔 **1× Buzzer connected to GPIO 4** (Receiver only)
🔗 Jumper wires, USB cable, breadboard
📶 WiFi Network Access (2.4 GHz)
🔋 *(Optional)* 3.7V Li-ion battery for portability

---

## 🧾 ESP32 Configuration

* **Board:** ESP32 Dev Module
* **WiFi Band:** 2.4 GHz only
* **I2C Pins:** SDA (GPIO 21), SCL (GPIO 22)
* **Buzzer Pin:** GPIO 4 (Receiver)
* **Built-in LED Pin:** GPIO 2
* **Baud Rate:** 115200

---

## 📦 Dependencies

Install via **Arduino Library Manager**:

```plaintext
- ThingSpeak (by MathWorks)
- Adafruit SSD1306
- Adafruit GFX
- WiFi.h (built-in with ESP32 core)
```

---

## ☁️ ThingSpeak Setup

1. Create a ThingSpeak account.
2. Create a new channel with **5 fields**.
3. Note your:

   * 📡 WiFi SSID & Password
   * 🆔 Channel ID
   * 🔐 Write API Key
   * 🔓 Read API Key
4. Update both `.ino` files with these credentials accordingly.

---

## 📤 Output Examples

### TX Node (Serial):

```
Connected to WiFi!
10.10.23.68

Input1: 91.97
Input2: 68.36
Input3: 60.76
Input4: 85.25
Input5: 87.90
Data uploaded successfully with status code 200
...
```

### RX Node (Serial + OLED):

```
Connected to WiFi!
10.10.25.31

02-Jul 03:09 IST | Status Code: 200
Input1: 48.36
Input2: 92.69
Input3: 81.01
Input4: 63.90
Input5: 17.50
...
```

---

## 👨‍💻 Author

> **Anvay Mayekar**
> 🎓 B.Tech in Electronics & Computer Science — SAKEC

[![GitHub](https://img.shields.io/badge/GitHub-181717.svg?style=for-the-badge\&logo=GitHub\&logoColor=white)](https://www.github.com/anvaymayekar)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-0A66C2.svg?style=for-the-badge\&logo=LinkedIn\&logoColor=white)](https://in.linkedin.com/in/anvaymayekar)
[![Instagram](https://img.shields.io/badge/Instagram-%23E4405F.svg?style=for-the-badge\&logo=Instagram\&logoColor=white)](https://www.instagram.com/anvaymayekar/)

---
