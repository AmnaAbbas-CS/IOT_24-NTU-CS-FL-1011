#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
    Serial.begin(115200);
    Wire.begin(OLED_SDA, OLED_SCL);

    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("OLED initialization failed!");
        while (true) {
            delay(100);
        }
    }

    display.setTextSize(2);                 // bigger text
    display.setTextColor(SSD1306_WHITE);
}

void loop() {
    const char* msg = "Hello IOT";           // no trailing space

    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(msg, 0, 0, &x1, &y1, &w, &h);  // measure the text

    int x = (SCREEN_WIDTH - w) / 2;          // center horizontally
    int y = (SCREEN_HEIGHT - h) / 2;         // center vertically

    display.clearDisplay();
    display.setCursor(x, y);
    display.println(msg);
    display.display();                       // send to the real screen

    delay(1000);                             // redraw once per second
}
