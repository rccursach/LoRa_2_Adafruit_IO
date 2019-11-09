# Receive a LoRa packet and send it to Adafruit IO

Tested on board `TTGO LoRa32 OLED`, ESP32 with SX1276, SSD1306.

## Lib Dependencies

* [Adafruit IO Arduino](https://github.com/adafruit/Adafruit_IO_Arduino)
* [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
* [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)
* [Adafruit MQTT](https://github.com/adafruit/Adafruit_MQTT_Library)
* [LoRa](https://github.com/sandeepmistry/arduino-LoRa)
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson)

## Setup

* Copy `config.example.h` as `config.h`.
* Set local constants for ESP32 WiFi and Adafruit IO on `config.h`.
* Compile.
* Upload.
