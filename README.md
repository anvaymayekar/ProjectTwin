# ProjectTwin: ESP32 TX/RX IoT System with OLED and ThingSpeak Integration
<br>

A complete dual-node ESP32-based Internet of Things system for cloud-connected data exchange. The project implements one ESP32 as a **transmitter** (TX) that periodically sends 5 string-based values to a ThingSpeak channel, and another ESP32 as a **receiver** (RX) that fetches this data, validates network and peripheral status, and displays results on both the Serial Monitor and a 128x64 OLED screen.<br><br>
> This project was developed as part of a practical exercise during the **AICTE SAKEC IDEALAB Summer Internship Program**, reflecting core concepts of embedded systems and IoT communication.

---

## Note

> This implementation uses only the official `ThingSpeak` library and `WiFi.h`. No `ArduinoJson` or external data parsing is used.
> Ensure the receiver OLED is properly connected via I2C (typically SDA to GPIO 21, SCL to GPIO 22 on ESP32).
> A 15-second delay is maintained as per ThingSpeak rate limits.
> Internal blue LED on each ESP32 acts as a subtle WiFi connection indicator. On the RX node, a buzzer on GPIO 4 gives a 1s beep each time new data is received.

---

## File structure

```
- root
    > TX_Node
        > TX_Node.ino (Transmitter ESP32 code)
    > RX_Node
        > RX_Node.ino (Receiver ESP32 code)
    > README.md (this file)
    > images
        > (Optional circuit diagrams / OLED previews)
```

---

## System Overview

### ✉️ Transmitter (TX Node)

* Sends 5 randomly generated string values<br>(e.g., "https://api.thingspeak.com/update?api_key=YOUR_WRITE_API_KEY&field1=25.5&field2=60.3
")<br>to a ThingSpeak channel.
* Uses `ThingSpeak.writeField()` to push string data directly.
* Implements digit formatting, floating point control, and padding.
* Enforces a 15-second delay between transmissions.
* Illuminates onboard blue LED when connected to WiFi.

### 📰 Receiver (RX Node)

* Connects to WiFi, prints connection and IP status.
* Retrieves string values from ThingSpeak using `ThingSpeak.readStringField()`.
* Checks OLED initialization and shows fallback errors.
* Displays current time, all 5 data values, and connection status on both Serial Monitor and 128x64 OLED.
* Activates a buzzer on pin 4 for 1 second upon successful data retrieval as feedback.

---

## Tools & Technologies

![ESP32](https://img.shields.io/badge/ESP32-323232.svg?style=for-the-badge\&logo=espressif\&logoColor=white) ![Arduino IDE](https://img.shields.io/badge/Arduino_IDE-00979D.svg?style=for-the-badge\&logo=arduino\&logoColor=white) ![ThingSpeak](https://img.shields.io/badge/ThingSpeak-003366.svg?style=for-the-badge\&logo=mathworks\&logoColor=white) ![Adafruit OLED](https://img.shields.io/badge/OLED-128x64-blue?style=for-the-badge)![Adafruit](https://img.shields.io/badge/Adafruit-Supported-blue?style=for-the-badge&logo=adafruit&logoColor=white)


---

## Hardware Requirements

`1. 2x ESP32 Dev Boards (DOIT / NodeMCU variants)`

`2. 128x64 I2C OLED Display (SSD1306)`

`3. Buzzer connected to GPIO 4 (Receiver only)`

`4. Jumper wires, USB cable, and breadboard (required only if PCB is unavailable)`

`5. WiFi Network Access`

`6. (Optional) 3.7V Li-ion battery for portability`

---

## ESP32 Specifications & Configuration

* **Board Used:** ESP32 Dev Module (DOIT or similar)
* **WiFi:** 2.4 GHz only (no 5 GHz support)
* **I2C Pins:** SDA (GPIO 21), SCL (GPIO 22)
* **Buzzer Pin:** GPIO 4 (Receiver)
* **Built-in LED Pin:** GPIO 2 (used for WiFi status)
* **Recommended Baud Rate:** 115200

---

## Dependencies

Install via Arduino Library Manager:

```
- ThingSpeak (by MathWorks)
- Adafruit SSD1306
- Adafruit GFX
- WiFi.h (built-in with ESP32 core)
```

---

## ThingSpeak Setup

1. Create a ThingSpeak account.
2. Create a new channel with 5 fields.
3. Note your **WiFi SSID**, **WiFi password**, **channel ID**, **write API key**, and **read API key**.
4. Update the `.ino` files with these credentials accordingly.

---

## Output Example

**TX Serial:**

```
Connected to WiFi!
10.10.23.68

Input1: 91.97
Input2: 68.36
Input3: 60.76
Input4: 85.25
Input5: 87.90
Data uploaded successfully with status code 2
...
```

**RX Serial + OLED:**

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

## Author

> Anvay Mayekar
> B. Tech. in Electronics & Computer Science \~ SAKEC
>
>[![GitHub](https://img.shields.io/badge/GitHub-181717.svg?style=for-the-badge\&logo=GitHub\&logoColor=white)](https://www.github.com/anvaymayekar)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-0A66C2.svg?style=for-the-badge\&logo=LinkedIn\&logoColor=white)](https://in.linkedin.com/in/anvaymayekar)
[![Instagram](https://img.shields.io/badge/Instagram-%23E4405F.svg?style=for-the-badge\&logo=Instagram\&logoColor=white)](https://www.instagram.com/anvaymayekar/)
