# ProjectTwin
ProjectTwin is a dual-node ESP32-based IoT system that utilizes ThingSpeak for cloud-mediated data exchange. The transmitter node generates and uploads five formatted float values at fixed intervals, while the receiver node polls the channel, parses the data, and displays it on a 128x64 I²C OLED along with buzzer and serial feedback.
