# ESP32-Weather-Clock
ESP32 Weather Clock based on LVGL （Arduino）.


Ardunio :
PLATFORM: Espressif 32 (2.0.0) > Espressif ESP32 Dev Module
HARDWARE: ESP32 240MHz, 320KB RAM, 4MB Flash
DEBUG: Current (esp-prog) External (esp-prog, iot-bus-jtag, jlink, minimodule, olimex-arm-usb-ocd, olimex-arm-usb-ocd-h, olimex-arm-usb-tiny-h, olimex-jtag-tiny, tumpa)
PACKAGES:
 - framework-arduinoespressif32 3.10004.200129 (1.0.4)
 - tool-esptoolpy 1.20600.0 (2.6.0)
 - tool-mkspiffs 2.230.0 (2.30)
 - toolchain-xtensa32 2.50200.80 (5.2.0)
LDF: Library Dependency Finder -> http://bit.ly/configure-pio-ldf
LDF Modes: Finder ~ chain, Compatibility ~ soft
Found 31 compatible libraries

Dependency Graph
|-- <FS> 1.0
|-- <SPIFFS> 1.0
|   |-- <FS> 1.0
|-- <lvgl> 7.10.1
|   |-- <ESP32 BLE Arduino> 1.0.1
|-- <TFT_Touch> 0.3.0
|-- <Wire> 1.0.1
|-- <ArduinoJson> 6.17.2
|-- <WiFi> 1.0
|-- <WebServer> 1.0
|   |-- <WiFi> 1.0
|   |-- <FS> 1.0
|-- <DNSServer> 1.1.0
|   |-- <WiFi> 1.0
|-- <Update> 1.0
|-- <WiFiManager> 2.0.4-beta
|   |-- <DNSServer> 1.1.0
|   |   |-- <WiFi> 1.0
|   |-- <ESPmDNS> 1.0
|   |   |-- <WiFi> 1.0
|   |-- <Update> 1.0
|   |-- <WebServer> 1.0
|   |   |-- <WiFi> 1.0
|   |   |-- <FS> 1.0
|   |-- <WiFi> 1.0
|-- <WiFiClientSecure> 1.0
|   |-- <WiFi> 1.0
|-- <SPI> 1.0
|-- <TFT_eSPI> 2.2.20
|   |-- <SPIFFS> 1.0
|   |   |-- <FS> 1.0
|   |-- <FS> 1.0
|   |-- <SPI> 1.0
|-- <HTTPClient> 1.2
|   |-- <WiFi> 1.0
|   |-- <WiFiClientSecure> 1.0
|   |   |-- <WiFi> 1.0
|-- <SD(esp32)> 1.0.5
|   |-- <FS> 1.0
|   |-- <SPI> 1.0
  
  
