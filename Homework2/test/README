
Homework 2: Dual-LED PWM Control with OLED Monitoring

Course: Embedded IoT Systems Name: [Your name] | Roll No: [Your roll number] Board: ESP32 DevKit | Framework: Arduino-ESP32 (PlatformIO), core version [check platformio.ini]

1. Project overview

This project controls two LEDs independently using the ESP32 LEDC (PWM) peripheral. Each LED fades smoothly from off to full brightness and back, using a different PWM frequency:

LED 1: 1000 Hz
LED 2: 5000 Hz

An SSD1306 I²C OLED shows the live duty cycle (in %) and the configured frequency of both LEDs while they fade.

The work was done in two stages, in the same project:

Task 1: two LEDs fading with different PWM frequencies
Task 2: OLED added to display the live PWM values
2. Links
Wokwi project: [paste Wokwi link]
GitHub repository: [paste GitHub link]
3. Repository structure
Homework-2/
├── diagram.json
├── wokwi.toml
├── platformio.ini
├── src/
│   └── main.cpp
├── screenshots/
│   ├── wokwi_circuit.png
│   ├── wokwi_running_oled.png
│   ├── hardware_circuit.jpg
│   └── hardware_oled_output.jpg
└── README.md
4. Wiring

Each LED has its own 220 Ω current-limiting resistor, so neither LED can draw too much current and the two LEDs do not affect each other.

Wokwi simulation
Component	ESP32 pin
LED 1 (through 220 Ω)	GPIO 25
LED 2 (through 220 Ω)	GPIO 26
OLED SDA	GPIO 21
OLED SCL	GPIO 22
OLED VCC	3V3
OLED GND and LED cathodes	GND
Physical hardware
Component	ESP32 pin
LED 1 (through 220 Ω)	GPIO 18
LED 2 (through 220 Ω)	GPIO 19
OLED SDA	GPIO [your SDA pin]
OLED SCL	GPIO [your SCL pin]
OLED VCC	3V3
OLED GND and LED cathodes	GND

OLED I²C address: 0x3C [change to 0x3D if your scanner found that].

5. PWM configuration
	LED 1	LED 2
Frequency	1000 Hz	5000 Hz
Resolution	10-bit (0 to 1023)	10-bit (0 to 1023)
LEDC channel (core 2.x)	0	2
Why 10-bit resolution

The LEDC clock is 80 MHz, and the highest usable resolution is about log2(80 MHz ÷ frequency). At 5000 Hz that gives about 13 bits, so 10 bits is safe for both frequencies. It gives 1024 brightness levels, which looks smooth to the eye.

LEDC timer limitation (technical check)

The ESP32 LEDC has several channels, but each timer sets only one frequency and one resolution, and every channel on that timer shares them. So two LEDs can have different frequencies only if they use different timers. If both channels were on the same timer, both LEDs would end up with the same frequency.

In this project, LED 1 uses channel 0 and LED 2 uses channel 2. On Arduino-ESP32 core 2.x, channels are paired onto timers (0 and 1 share a timer, 2 and 3 share another), so these two channels are on different timers and the two frequencies stay independent. On Arduino-ESP32 core 3.x, ledcAttach() assigns the timers automatically. The code supports both versions.

6. How it works
Duty-cycle control (Task 1)

Each LED has its own duty variable, duty1 and duty2, ranging from 0 to 1023. In every pass of loop(), the program adds a small step to each value. When a value reaches 1023, the direction reverses and it counts back down to 0. This makes each LED fade up and down smoothly. The two LEDs use different step sizes, so they fade at different speeds and are clearly independent. The values are written to the LEDs with ledcWrite(). They are kept as global variables so the OLED can read them.

OLED display (Task 2)

The function showOLED() reads the same duty1 and duty2 variables and converts each to a percentage:

percentage = duty × 100 / 1023

It then prints the percentage and the frequency constant (LED1_FREQ or LED2_FREQ) on the screen. showOLED() is called inside loop() right after the duty values are updated, so the display refreshes about every 10 ms.

Why the displayed values are correct

The OLED does not use separate or fake numbers. It reads exactly the same variables that drive the PWM output, and the frequencies come from the same constants used to set up the LEDC channels. So what the screen shows always matches what the program is really doing.

How duty cycle affects brightness

Duty cycle is the percentage of each PWM period for which the pin is HIGH. The LED switches on and off much faster than the eye can notice, so we see the average. A low duty cycle (for example 25%) looks dim and a high duty cycle (for example 75%) looks bright. Duty 0 is fully off and duty 1023 is fully on.

How frequency affects the output signal

Frequency is the number of on/off cycles per second. It does not change the average brightness at a given duty cycle. It changes how fast the signal switches. Too low a frequency (below about 100 Hz) can cause visible flicker. At 1000 Hz and 5000 Hz both LEDs look steady, so the difference between them can only be seen with an oscilloscope or logic analyzer, not by eye.

7. OLED output

The display shows three lines:

PWM MONITOR
LED1: xx% F:1000Hz
LED2: xx% F:5000Hz

The percentages change continuously while the LEDs fade. The frequencies stay fixed because they are configured once in setup().

8. Test results
Wokwi simulation

Both LEDs fade smoothly up and down at different speeds. The OLED shows the changing duty-cycle percentages and the frequencies of 1000 Hz and 5000 Hz.

Physical hardware

[Write what you actually saw. For example: Both LEDs fade on the real board. The OLED shows the changing percentages and both frequencies.]

9. Wokwi vs hardware
	Wokwi	Hardware
LED pins	GPIO 25 and 26	GPIO 18 and 19
OLED pins	GPIO 21 (SDA), 22 (SCL)	GPIO [your pins]
Fading	Smooth	[what you saw]
1000 Hz vs 5000 Hz	Not visible by eye	Not visible by eye
OLED	Worked directly	[any problem you had and how you fixed it]
Differences and why
Pins: I used different GPIO pins on the real board because of how my wiring was set up. Wokwi lets any pin be used, but on real hardware the code pins must match the physical wires.
Hardware issues: [Write what you ran into, for example OLED address, loose jumper wire, file not saved before upload, and how you solved it.]
Behaviour: Wokwi is an ideal simulation. Real LEDs, resistors, wires and the OLED have small tolerances, so brightness and timing can look slightly different on hardware.
10. Screenshots and photos
Wokwi

Wokwi circuit

Wokwi running with OLED

Hardware

Hardware circuit

Hardware OLED output

11. Commit history
task1 completed: two LEDs fading with different PWM frequencies
complete homework: OLED added, plus screenshots, photos and documentation
12. Safety notes
A separate current-limiting resistor is used for each LED.
The OLED voltage and pinout were checked before powering it.
Power was disconnected before changing any wiring.