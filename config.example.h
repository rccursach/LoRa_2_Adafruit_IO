#ifndef CONFIG_H
#define CONFIG_H

/* ----- !!! COPY THIS FILE AS "config.h" !!! ----- */

// IO Connection constants
#define IO_USERNAME "USERNAME"
#define IO_KEY "KEY"
#define WIFI_SSID "SSID"
#define WIFI_PASS "PASSWORD"
#define FEED_NAME "FEED-NAME"

//OLED pins
#define OLED_SDA 4
#define OLED_SCL 15 
#define OLED_RST 16
#define OLED_ADDR 0x3C
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// LoRa constants
#define SS      18
#define RST     14
#define DI0     26
#define BAND    915E6

#endif
