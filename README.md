# SEU — Introduction to Embedded Systems Lab
### CSE382 | Department of Computer Science & Engineering
### Southeast University

**Instructor:** Tashreef Muhammad, Lecturer, Dept. of CSE

---

## About This Repository

This is the official lab code repository for **CSE382: Introduction to Embedded Systems Lab**, the hands-on companion to the CSE381 theory course.

Every lab session has a dedicated folder containing working code, wiring instructions, and explanations. The labs are designed to be done in order - each one builds on skills from the previous sessions.

---

## Platforms Used

This course uses three hardware platforms, each representing a different class of embedded computing:

| Platform | Type | Language | Used In |
|----------|------|----------|---------|
| Arduino Uno (ATmega328P) | 8-bit Microcontroller | C / C++ | Labs 01–08, Lab 10 |
| ESP32 | 32-bit WiFi Microcontroller | C++ (Arduino IDE) | Lab 09 |
| Raspberry Pi | Single Board Computer (Linux) | Python | Lab 09 |

**Why three platforms?**
- **Arduino Uno** — teaches fundamentals: GPIO, sensors, actuators, timers, interrupts, registers. Nothing is hidden. Every concept is visible.
- **ESP32** — adds wireless connectivity. Shows how microcontrollers power IoT applications.
- **Raspberry Pi** — shows a full Linux-based embedded system. Demonstrates the boundary between microcontroller and computer.

---

## Lab Modules

| Lab | Topic | Key Concepts | Platform |
|-----|-------|-------------|----------|
| Lab 01 | LED Control | Digital output, PWM, analogWrite | Arduino Uno |
| Lab 02 | Serial Communication | UART, Serial Monitor, input modes | Arduino Uno |
| Lab 03 | Digital Input & Sensors | PIR, HC-SR04, DHT11, sensor reading | Arduino Uno |
| Lab 04 | Motor Control | DC motor, L298N, servo, stepper, PWM | Arduino Uno |
| Lab 05 | Display & Input Interfaces | LCD (I2C), 4×4 keypad, combined I/O | Arduino Uno |
| Lab 06 | Sensor Fusion | Multi-sensor logic, conditional control | Arduino Uno |
| Lab 07 | Servo Control via Sensor | Sensor-to-actuator mapping, map() | Arduino Uno |
| Lab 08 | System Integration | State-based design, alarm system | Arduino Uno |
| Lab 09 | Advanced Platforms | ESP32 WiFi server, Raspberry Pi GPIO | ESP32, RPi |
| Lab 10 | Interrupts & Memory-Mapped I/O | ISR, volatile, timer registers, DDRB/PORTB | Arduino Uno |

---

## Lab 10 — Special Note

Lab 10 is structured differently from the other labs. It contains **five codes** rather than one or two, each with its own dedicated README file explaining every line, operator, and concept in detail.

This lab directly connects your theory class (CSE381) register-level content to working, observable code:

| Code | What it teaches |
|------|----------------|
| Code 01 | The polling problem — why delay-based code misses events |
| Code 02 | External interrupts — ISR, volatile, FALLING trigger |
| Code 03 | Timer interrupt — OCR1A, TCCR1B, TIMSK1, bare-metal calculation |
| Code 04 | Arduino abstraction vs direct registers — DDRB, PORTB, PIND |
| Code 05 | Memory-mapped I/O — raw address pointers, `volatile uint8_t*` |

---

## Repository Structure

```
SEU-Introduction-to-Embedded-System-Lab-Codes/
│
├── Lab01/
│   ├── Code01/          ← LED blink
│   ├── Code02/          ← PWM fade
│   └── README.md
│
├── Lab02/
│   ├── Code01/          ← Serial-controlled LED modes
│   ├── Code02/          ← Button-controlled LED modes
│   └── README.md
│
├── Lab03/
│   ├── Code01/          ← PIR motion sensor
│   ├── Code02/          ← HC-SR04 ultrasonic distance
│   ├── Code03/          ← DHT11 temperature and humidity
│   ├── Code04/          ← All three sensors combined
│   └── README.md
│
├── Lab04/
│   ├── Code01/          ← DC motor without driver
│   ├── Code02/          ← DC motor with L298N (forward/reverse)
│   ├── Code03/          ← DC motor speed ramp
│   ├── Code04/          ← Servo motor sweep
│   ├── Code05/          ← Stepper motor
│   └── README.md
│
├── Lab05/
│   ├── Code01/          ← 16×2 LCD display (I2C)
│   ├── Code02/          ← 4×4 matrix keypad
│   ├── Code03/          ← LCD + keypad combined
│   └── README.md
│
├── Lab06/
│   ├── Code01/          ← PIR + ultrasonic sensor fusion
│   └── README.md
│
├── Lab07/
│   ├── Code01/          ← Servo angle controlled by distance
│   └── README.md
│
├── Lab08/
│   ├── Code01/          ← Motion-triggered LED and buzzer alarm
│   └── README.md
│
├── Lab09/
│   ├── ESP32/           ← WiFi web server, browser-controlled LED
│   ├── RaspberryPi/     ← Python GPIO LED blink
│   └── README.md
│
└── Lab10/
    ├── Code01/          ← Polling problem (Code01.ino + README.md)
    ├── Code02/          ← External interrupt (Code02.ino + README.md)
    ├── Code03/          ← Timer interrupt bare-metal (Code03.ino + README.md)
    ├── Code04/          ← Arduino abstraction vs registers (Code04.ino + README.md)
    ├── Code05/          ← Memory-mapped I/O raw pointers (Code05.ino + README.md)
    └── README.md
```

---

## How to Use This Repository

**For each lab:**
1. Open the lab folder
2. Read the `README.md` first — it explains the objective, components, and wiring
3. Open the code in Arduino IDE (or Thonny for Raspberry Pi)
4. Wire the circuit as described
5. Upload and observe
6. Attempt the practice tasks — do not skip them

**For Lab 10 specifically:**
- Each code folder has its own `README.md` — read it before uploading that code
- Do the codes in order: Code 01 → 02 → 03 → 04 → 05
- Answer the observation questions in each README as you go

---

## Software Setup

### Arduino IDE (Labs 01–08, Lab 10)
1. Download from [arduino.cc/en/software](https://www.arduino.cc/en/software)
2. Select board: **Tools → Board → Arduino Uno**
3. Select port: **Tools → Port → (your COM port)**

### Arduino IDE for ESP32 (Lab 09)
1. Go to **File → Preferences → Additional Boards Manager URLs**
2. Add: `https://dl.espressif.com/dl/package_esp32_index.json`
3. Go to **Tools → Board → Boards Manager**, search ESP32, install
4. Select board: **ESP32 Dev Module**

### Python for Raspberry Pi (Lab 09)
- No installation needed — Python and RPi.GPIO are pre-installed on Raspberry Pi OS
- Run code directly from terminal: `python3 filename.py`

### Required Arduino Libraries
| Library | Used In | Install via |
|---------|---------|-------------|
| DHT sensor library | Lab 03 | Library Manager |
| Adafruit LiquidCrystal | Lab 05 | Library Manager |
| Keypad | Lab 05 | Library Manager |
| Servo (built-in) | Lab 04, 07 | Pre-installed |
| Stepper (built-in) | Lab 04 | Pre-installed |

To install: **Sketch → Include Library → Manage Libraries → search name → Install**

---

## Components Reference

| Component | Used In |
|-----------|---------|
| Arduino Uno | Labs 01–08, 10 |
| LED (assorted colours) + 330Ω resistors | Labs 01–08, 10 |
| Push buttons | Labs 02, 10 |
| PIR sensor (HC-SR501) | Labs 03, 06, 08 |
| Ultrasonic sensor (HC-SR04) | Labs 03, 06, 07 |
| DHT11 temperature/humidity sensor | Lab 03 |
| DC motor + L298N driver | Lab 04 |
| Servo motor | Labs 04, 07 |
| Stepper motor (28BYJ-48) | Lab 04 |
| 16×2 LCD display (I2C) | Lab 05 |
| 4×4 matrix keypad | Lab 05 |
| Passive buzzer | Lab 08 |
| ESP32 board | Lab 09 |
| Raspberry Pi | Lab 09 |

---

## Advice to Students

These codes are starting points — not answers to copy.

The goal of each lab is not to make the hardware work. The goal is to understand **why** it works. Before moving to the next code, make sure you can answer:
- What does each line of code do?
- What would happen if you removed or changed this line?
- How does this connect to what you learned in theory class?

The practice tasks in each README are not optional. They are where the real learning happens.

If your code works but you cannot explain it, you have not finished the lab.

---

## Academic Integrity

The code in this repository is provided for learning. Submitting lab work copied directly from this repository without modification or understanding is a violation of course policy.

You are expected to:
- Modify the starting code
- Attempt the practice tasks
- Be able to explain every line during lab evaluation

---

## Contact

For corrections, questions, or contributions:

**Tashreef Muhammad**
Lecturer, Department of CSE, Southeast University