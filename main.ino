// Adafruit IO
#include "AdafruitIO_WiFi.h"

// Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// LoRa
#include <LoRa.h>
#include <SPI.h>

// ArduinoJSON
#include <ArduinoJson.h>

// Config local constants
#include "config.h"


// Adafruit IO
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
AdafruitIO_Feed *feed = io.feed(FEED_NAME);

// Display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

// Count items being sent
int counter = 0;

void setup() {
  // Start serial connection
  Serial.begin(115200);
  while (!Serial);
  
  // Start IO connection
  io.connect();
  while (io.status() < AIO_CONNECTED) { delay(500); }

  // Show IO connection status
  Serial.println(io.statusText());

  // Setup display
  //reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  //initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR, false, false)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("IO Sender");
  display.display();

  // Initialize LoRa
  SPI.begin(5,19,27,18);
  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(BAND)) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("LoRa Initialization failed!");
    display.display();

    Serial.println("LoRa Initialization failed!");
    while (1);  // Don't proceed, loop forever
  }
}

void loop() {
  io.run();
  // if got a LoRa packet
  if (LoRa.parsePacket()) {
    // Parse packet
    String packet = getPacketAsStr();
    int rssi = LoRa.packetRssi();
    float snr = LoRa.packetSnr();
    // Build json
    String json = makeJsonFrom(snr, rssi, packet);
    // Send data to IO feed and update counter
    Serial.println("sending data");
    feed->save("data");
    printCount();
  }
}

String makeJsonFrom(double snr, int rssi, String data) {
    const size_t bufferSize = JSON_OBJECT_SIZE(3);
    DynamicJsonBuffer jsonBuffer(bufferSize);

    JsonObject& root = jsonBuffer.createObject();
    root["rssi"] = rssi;
    root["snr"] = snr;
    root["data"] = data;

    String out;
    root.printTo(out);
    return out;
}

String getPacketAsStr() {
  if (LoRa.available()) {
    String out = "";
    while (LoRa.available()) {
      byte data = LoRa.read();
      out = out + String(data, HEX);
    }
    return out;
  }
  return "\0";
}

void wait_minutes(int minutes) {
  int seconds = minutes * 60;
  for (int i = 0; i < seconds; i++) { delay(1000); }
}

void printCount() {
  counter += 1;
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("IO SENDER");
  display.setCursor(0,20);
  display.setTextSize(1);
  display.print("Data sent.");
  display.setCursor(0,30);
  display.print("Counter:");
  display.setCursor(50,30);
  display.print(counter);
  display.display();
}
