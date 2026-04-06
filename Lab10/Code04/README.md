# Code 04 — Arduino Abstraction vs Direct Register Access

## Board
Arduino Uno (ATmega328P)

## Components
| Component | Arduino Pin | AVR Pin |
|-----------|------------|---------|
| Red LED + 330Ω | Pin 13 | PB5 |
| Green LED + 330Ω | Pin 12 | PB4 |
| Blue LED + 330Ω | Pin 8 | PB0 |
| Push button | Pin 7 → GND | PD7 |

---

## What This Code Does

Two versions of the same behaviour:
- **Version A:** Uses `pinMode()`, `digitalWrite()`, `digitalRead()`
- **Version B:** Uses `DDRB`, `PORTB`, `PINB`, `DDRD`, `PORTD`, `PIND` directly

Run Version A. Observe the LEDs. Upload Version B. The LEDs behave identically.

This demonstrates that Arduino functions are simply wrappers — they perform these exact register operations internally. When you write `digitalWrite(13, HIGH)`, the Arduino library translates it into `PORTB |= (1 << PB5)` for you.

---

## Pin Mapping — Arduino Uno to AVR Registers

| Arduino Pin | Port | Bit | DDRx | PORTx | PINx |
|------------|------|-----|------|-------|------|
| Pin 13 | B | 5 | DDRB | PORTB | PINB |
| Pin 12 | B | 4 | DDRB | PORTB | PINB |
| Pin 8 | B | 0 | DDRB | PORTB | PINB |
| Pin 7 | D | 7 | DDRD | PORTD | PIND |

---

## The Three GPIO Registers

Every port has three registers. For Port B:

| Register | Address | Purpose |
|----------|---------|---------|
| DDRB | 0x24 | Direction: write 1 = output, write 0 = input |
| PORTB | 0x25 | Output value: write 1 = HIGH, write 0 = LOW |
| PINB | 0x23 | Input state: read 1 = pin is HIGH, read 0 = pin is LOW |

---

## Operator Reference — Every Operator Used in Version B

### Left shift: `(1 << n)`
Creates a number with only bit `n` set to 1, all others 0.
```
(1 << 5) = 0b00100000 = 32
(1 << 4) = 0b00010000 = 16
(1 << 0) = 0b00000001 = 1
```
This is how you target a specific pin without affecting others.

---

### OR-assign: `|=`  — Set a bit HIGH (output ON)
```cpp
PORTB |= (1 << PB5);
```
`|=` performs bitwise OR and stores the result back.
Bitwise OR: any bit that is 1 in either operand becomes 1 in the result.

```
PORTB before:  0b00010000   (only bit 4 was set)
(1 << PB5):    0b00100000   (bit 5 mask)
Result (OR):   0b00110000   (bit 5 now set, bit 4 unchanged)
```
This sets bit 5 (Pin 13) HIGH **without touching any other pin**.

---

### AND-assign with NOT: `&= ~(...)` — Set a bit LOW (output OFF)
```cpp
PORTB &= ~(1 << PB4);
```
Two operations combined:

**Step 1 — Bitwise NOT: `~(1 << PB4)`**
Inverts every bit of the mask, creating a pattern with a 0 only in the target position.
```
(1 << PB4):       0b00010000
~(1 << PB4):      0b11101111   ← 0 only at bit 4
```

**Step 2 — AND-assign: `&=`**
Bitwise AND: a bit stays 1 only if it is 1 in both operands.
```
PORTB before:     0b00110000   (bits 5 and 4 set)
~(1 << PB4):      0b11101111   (0 at bit 4, 1 everywhere else)
Result (AND):     0b00100000   (bit 4 cleared, bit 5 unchanged)
```
This clears bit 4 (Pin 12) LOW **without touching any other pin**.

---

### Read with AND: `PIND & (1 << PD7)` — Read a specific bit
```cpp
bool pressed = !(PIND & (1 << PD7));
```
`PIND` contains the current voltage state of all Port D pins as 8 bits.

`PIND & (1 << PD7)` masks out all bits except bit 7:
```
PIND (example):   0b10000000   (pin 7 is HIGH — button not pressed)
(1 << PD7):       0b10000000
Result (AND):     0b10000000   → non-zero → button NOT pressed

PIND (example):   0b00000000   (pin 7 is LOW — button pressed)
(1 << PD7):       0b10000000
Result (AND):     0b00000000   → zero → button IS pressed
```

The `!` (logical NOT) inverts the result so `pressed = true` when the button is held.

---

### Setting direction — DDRB and DDRD
```cpp
DDRB |= (1 << PB5) | (1 << PB4) | (1 << PB0);
```
Sets bits 5, 4, and 0 of DDRB in one line. The `|` between the masks combines them:
```
(1 << PB5) = 0b00100000
(1 << PB4) = 0b00010000
(1 << PB0) = 0b00000001
Combined:    0b00110001
```
All three bits are set to 1 → three pins configured as outputs simultaneously.

```cpp
DDRD &= ~(1 << PD7);
```
Clears bit 7 of DDRD → Pin 7 configured as input.

```cpp
PORTD |= (1 << PD7);
```
When a pin is configured as input, writing 1 to its PORTD bit **enables the internal pull-up resistor** — exactly as `INPUT_PULLUP` does in Arduino.

---

## What to Observe

Run Version A. Write down what you see. Upload Version B. The behaviour is identical.

Open the Arduino source code (find `wiring_digital.c` in the Arduino installation) and look up `digitalWrite()`. You will find the exact same register operations written there.

---

## Practice Tasks

1. **Side-by-side proof:** Run Version A and note the Serial Monitor output. Run Version B. Is the output identical word for word?

2. **Single write:** Using only one assignment to `PORTB` (no `|=` or `&=`), set pins 13 and 12 HIGH and pin 8 LOW simultaneously. What binary value do you write?

3. **Fourth LED:** Add a fourth LED on Pin 9 (PB1). Add it to the DDRB setup line. Make it toggle (XOR) every time the button is pressed. Which operator do you use?

4. **PORTB vs PINB:** While Pin 13 is set HIGH via PORTB, read both `PORTB` and `PINB` and print them to Serial Monitor. Are they the same? Why might they differ in some hardware conditions?

5. **Pointer syntax:** Declare `volatile uint8_t* pb = (volatile uint8_t*)0x25;` and rewrite the Red LED ON line using `*pb`. Does it compile and behave correctly?
