#include <Arduino.h>

// ---------- Settings ----------
const int LED1_PIN  = 25;
const int LED2_PIN  = 26;
const int LED1_FREQ = 1000;   // Hz
const int LED2_FREQ = 5000;   // Hz
const int PWM_RES   = 10;     // 10-bit -> duty 0..1023
const int MAX_DUTY  = 1023;

// Old core (2.x) needs channel numbers.
// Channels 0 and 2 are on DIFFERENT timers, so frequencies stay independent.
const int LED1_CH = 0;
const int LED2_CH = 2;

// Current duty values (these are what the OLED will show in Task 2)
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

void setup() {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcAttach(LED1_PIN, LED1_FREQ, PWM_RES);
  ledcAttach(LED2_PIN, LED2_FREQ, PWM_RES);
#else
  ledcSetup(LED1_CH, LED1_FREQ, PWM_RES);
  ledcAttachPin(LED1_PIN, LED1_CH);
  ledcSetup(LED2_CH, LED2_FREQ, PWM_RES);
  ledcAttachPin(LED2_PIN, LED2_CH);
#endif
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

  delay(10);
}