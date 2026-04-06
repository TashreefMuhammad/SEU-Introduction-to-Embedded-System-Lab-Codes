# Code 02 — External Interrupt: The Solution

## Board
Arduino Uno

## Components
| Component | Pin |
|-----------|-----|
| Yellow LED + 330Ω resistor | Pin 11 |
| Green LED + 330Ω resistor | Pin 10 |
| Push button | Pin 2 → GND |

> **Important:** The button must be on **Pin 2** (INT0) or **Pin 3** (INT1). These are the only two pins on Arduino Uno that support hardware external interrupts.

---

## What This Code Does

Same busy task as Code 01 — yellow LED ON for 3 seconds, OFF for 0.5 seconds. But now the button is handled by a hardware interrupt. Every single button press is captured immediately, no matter what `loop()` is doing at that moment.

---

## How an Interrupt Works

When the button is pressed, the ATmega328P hardware detects the signal change on Pin 2 and **immediately pauses** whatever the CPU is doing. It jumps to a special function called an ISR (Interrupt Service Routine), runs it, and then resumes exactly where it left off.

```
loop() is inside delay(3000) ...
    → you press button
    → CPU pauses delay() mid-wait
    → CPU runs buttonISR() immediately
    → pressCount++, pressDetected = true
    → CPU returns to delay() exactly where it paused
    → delay() continues counting
```

The MCU never misses the press, even during a 3-second delay.

---

## Line-by-Line Explanation

### volatile keyword
```cpp
volatile int  pressCount    = 0;
volatile bool pressDetected = false;
```
`volatile` tells the compiler: *"this variable can change at any time, outside of normal program flow."* Without it, the compiler might optimise the variable into a CPU register and never re-read it from memory — causing `loop()` to see stale values even after the ISR has changed them.

**Rule:** Any variable shared between an ISR and the main code must be `volatile`.

---

### The ISR function
```cpp
void buttonISR() {
    pressCount++;
    pressDetected = true;
}
```
This runs automatically when the interrupt fires. Two rules apply here:

1. **No `delay()`** — delay() depends on Timer0 interrupts, which are blocked while an ISR runs. Calling delay() inside an ISR will freeze the program.
2. **No `Serial.print()`** — Serial uses interrupts internally. Calling it inside an ISR causes conflicts and corrupted output.

The correct pattern: set a flag in the ISR, handle everything else in `loop()`.

---

### Attaching the interrupt
```cpp
attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
```

| Part | Meaning |
|------|---------|
| `digitalPinToInterrupt(BUTTON_PIN)` | Converts pin 2 to interrupt number 0 (INT0) |
| `buttonISR` | The function to call when the interrupt fires |
| `FALLING` | Trigger when the pin goes from HIGH → LOW |

**Why FALLING?** The button uses `INPUT_PULLUP`, so the pin sits at HIGH when not pressed and drops to LOW when pressed. The falling edge (HIGH→LOW) marks the moment of press.

Other trigger options:
| Mode | When it fires |
|------|--------------|
| `RISING` | LOW → HIGH transition |
| `FALLING` | HIGH → LOW transition |
| `CHANGE` | Either transition |
| `LOW` | While pin is LOW (continuous, rarely used) |

---

### The flag pattern in loop()
```cpp
if (pressDetected) {
    pressDetected = false;
    ...
}
```
The ISR sets `pressDetected = true`. The `loop()` checks for this flag and clears it after handling. This separation keeps the ISR short and puts the slow work (Serial print, LED flash) safely in `loop()`.

---

## Try This

1. Upload the code. Open Serial Monitor (9600 baud).
2. While the yellow LED is ON, press the button 5 times quickly.
3. After the LED turns OFF, check Serial Monitor.
4. Every press should be reported — compare with Code 01.

---

## Practice Tasks

1. **Break it deliberately:** Remove `volatile` from `pressCount`. Upload and press the button 20+ times. Does the count behave correctly? Explain what you observe.

2. **Second interrupt:** Add a second button on Pin 3 (INT1). Write a separate ISR that resets `pressCount` to zero when pressed.

3. **Understand FALLING:** Change `FALLING` to `RISING`. Now the button needs to go LOW→HIGH to trigger. What physical change do you need to make to the wiring for this to work?

4. **Break the ISR rules:** Move `Serial.println(pressCount)` inside `buttonISR()`. Press the button rapidly. What strange output appears? Why?
