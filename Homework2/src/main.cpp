#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------- PWM settings ----------
const int LED1_PIN  = 18;
const int LED2_PIN  = 19;
const int LED1_FREQ = 1000;   // Hz
const int LED2_FREQ = 5000;   // Hz
const int PWM_RES   = 10;     // 10-bit -> duty 0..1023
const int MAX_DUTY  = 1023;

// Old core (2.x): channels 0 and 2 sit on different timers,
// so the two frequencies stay independent.
const int LED1_CH = 0;
const int LED2_CH = 2;

// ---------- OLED settings ----------
const int SDA_PIN = 21;
const int SCL_PIN = 22;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Duty values: the SAME variables drive the LEDs and the OLED
int duty1 = 0;
int duty2 = 0;
int step1 = 4;   // LED1 fade speed
int step2 = 7;   // LED2 fade speed

void pwmWrite(int pin, int ch, int duty) {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcWrite(pin, duty);
#else
  ledcWrite(ch, duty);
#endif
}

void showOLED() {
  int pct1 = (duty1 * 100) / MAX_DUTY;   // duty -> percentage
  int pct2 = (duty2 * 100) / MAX_DUTY;

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("PWM MONITOR");

  display.setCursor(0, 20);
  display.printf("LED1: %d%% F:%dHz", pct1, LED1_FREQ);

  display.setCursor(0, 36);
  display.printf("LED2: %d%% F:%dHz", pct2, LED2_FREQ);

  display.display();
}

void setup() {
  Serial.begin(115200);

#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcAttach(LED1_PIN, LED1_FREQ, PWM_RES);
  ledcAttach(LED2_PIN, LED2_FREQ, PWM_RES);
#else
  ledcSetup(LED1_CH, LED1_FREQ, PWM_RES);
  ledcAttachPin(LED1_PIN, LED1_CH);
  ledcSetup(LED2_CH, LED2_FREQ, PWM_RES);
  ledcAttachPin(LED2_PIN, LED2_CH);
#endif

  Wire.begin(SDA_PIN, SCL_PIN);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {   // OLED address
    Serial.println("OLED not found! Check wiring / address.");
  }
}

void loop() {
  // Fade LED1 up and down
  duty1 += step1;
  if (duty1 >= MAX_DUTY) { duty1 = MAX_DUTY; step1 = -step1; }
  if (duty1 <= 0)        { duty1 = 0;        step1 = -step1; }

  // Fade LED2 up and down
  duty2 += step2;
  if (duty2 >= MAX_DUTY) { duty2 = MAX_DUTY; step2 = -step2; }
  if (duty2 <= 0)        { duty2 = 0;        step2 = -step2; }

  pwmWrite(LED1_PIN, LED1_CH, duty1);
  pwmWrite(LED2_PIN, LED2_CH, duty2);

  showOLED();
  delay(10);
}