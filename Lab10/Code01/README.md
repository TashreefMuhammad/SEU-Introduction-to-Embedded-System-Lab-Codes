# Code 01 — The Polling Problem

## Board
Arduino Uno

## Components
| Component | Pin |
|-----------|-----|
| Yellow LED + 330Ω resistor | Pin 11 |
| Push button | Pin 7 → GND |

---

## What This Code Does

The Arduino simulates a "busy task" — the yellow LED stays ON for 3 seconds, then OFF for 0.5 seconds. This repeats forever.

The button is only checked **once per loop cycle** — meaning once every 3.5 seconds. This is called **polling**: the MCU periodically checks whether something happened.

---

## The Problem

The MCU spends 3 seconds inside `delay(3000)`. During those 3 seconds, it cannot do anything else. It cannot check the button. It cannot respond to any event.

If you press the button 5 times while the LED is ON, the MCU will likely report only 0 or 1 press — because it only looks at the button state **once**, after the delay finishes.

---

## Try This

1. Upload the code and open Serial Monitor (9600 baud).
2. Watch the yellow LED turn ON.
3. While the LED is ON, press the button **5 times quickly**.
4. Wait for the LED to turn OFF.
5. Count how many presses Serial Monitor reports.

**Expected result:** Far fewer than 5 presses are reported.

---

## Why This Happens — Step by Step

```
loop() starts
  → LED turns ON
  → delay(3000) begins
      ← you press button 3 times here — MCU does NOT see them
  → delay(3000) ends
  → LED turns OFF
  → delay(500)
  → button checked ONCE here — sees current state only
  → if button is not held at this exact moment: press count = 0
loop() repeats
```

The MCU is not ignoring you. It simply has no mechanism to notice events that happen while it is busy waiting.

---

## Key Concept

Polling works acceptably when:
- The MCU has nothing else to do
- The event happens slowly and predictably

Polling **fails** when:
- The MCU is doing other work (delays, calculations, communication)
- Events happen quickly or unpredictably (button presses, sensor triggers)

This is why **interrupts** were invented. Code 02 solves this exact problem.

---

## Questions to Answer Before Moving On

1. How many presses did Serial Monitor actually detect out of 5?
2. Why does `delay(3000)` prevent the button from being read?
3. What would happen if you changed `delay(3000)` to `delay(10)`? Would polling work better? Why?
