# Code 03 — Timer Interrupt (Bare-Metal Registers)

## Board
Arduino Uno (ATmega328P)

## Components
| Component | Arduino Pin | AVR Pin |
|-----------|------------|---------|
| Red LED + 330Ω | Pin 13 | PB5 |
| Green LED + 330Ω | Pin 11 | PB3 |

---

## What This Code Does

Two LEDs blink at completely different rates with no coordination:
- **Red LED (Pin 13):** Controlled by a hardware Timer1 interrupt — toggles every exactly 1 second
- **Green LED (Pin 11):** Controlled by `loop()` — blinks freely at its own rate

Both run simultaneously and independently. The timer fires in the background no matter what `loop()` is doing. There are no Arduino libraries — only raw AVR hardware registers.

---

## How Timer Interrupts Work

The ATmega328P has a hardware counter inside Timer1. It counts up from 0 on every timer clock tick. When the count reaches the value stored in `OCR1A`, it fires an interrupt and resets to 0. This cycle repeats forever, completely independent of the CPU's main program.

```
Timer clock ticks: 0, 1, 2, 3 ... 15623, 15624 → INTERRUPT! → 0, 1, 2 ...
                                                      ↓
                                               ISR runs here
                                               Red LED toggles
```

---

## The Calculation

This connects directly to what your theory notes describe as the PSC/ARR design problem.

```
CPU clock frequency    = 16,000,000 Hz
Prescaler selected     = 1024
Timer clock frequency  = 16,000,000 ÷ 1024 = 15,625 Hz
Desired interval       = 1 second = 15,625 timer ticks
OCR1A value            = 15,625 − 1 = 15,624
  (subtract 1 because the counter counts 0 through 15624 = 15625 steps)
```

---

## Register Configuration — Line by Line

### Setting pins as outputs
```cpp
DDRB |= (1 << PB5);   // Pin 13 → output
DDRB |= (1 << PB3);   // Pin 11 → output
```
`DDRB` is the Data Direction Register for Port B. Setting a bit to 1 makes that pin an output. `(1 << PB5)` creates a number with only bit 5 set. `|=` sets that bit without touching the others.

---

### Configuring Timer1
```cpp
TCCR1A = 0;
```
Timer/Counter Control Register A. Writing 0 disables PWM output compare modes — we only want the interrupt, not a waveform output.

```cpp
TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
```
Timer/Counter Control Register B. Two things are configured here in one line:

| Bit | Name | Purpose |
|-----|------|---------|
| WGM12 | Waveform Generation Mode bit 2 | Selects CTC mode (Clear Timer on Compare) |
| CS12 | Clock Select bit 2 | Together with CS10, selects prescaler = 1024 |
| CS10 | Clock Select bit 0 | |

**CTC mode** means the timer resets to 0 automatically when it reaches `OCR1A`. Without this, the timer would overflow and wrap around — producing the wrong interval.

**Prescaler options:**

| CS12 | CS11 | CS10 | Prescaler |
|------|------|------|-----------|
| 0 | 0 | 1 | 1 (no prescaling) |
| 0 | 1 | 0 | 8 |
| 0 | 1 | 1 | 64 |
| 1 | 0 | 0 | 256 |
| 1 | 0 | 1 | **1024** ← used here |

---

```cpp
OCR1A = 15624;
```
Output Compare Register A. The timer counts up to this value, fires the interrupt, then resets. Derived from the calculation above.

---

```cpp
TIMSK1 = (1 << OCIE1A);
```
Timer Interrupt Mask Register 1. Setting `OCIE1A` (Output Compare Interrupt Enable A) allows Timer1 to fire the compare match interrupt. Without this line, the timer runs but produces no interrupt.

---

```cpp
sei();
```
Set Enable Interrupts — enables the global interrupt flag. Even if a specific interrupt is enabled, no interrupts will fire unless this global flag is set. This is the master switch.

---

### The ISR
```cpp
ISR(TIMER1_COMPA_vect) {
    seconds++;
    PORTB ^= (1 << PB5);
}
```
`TIMER1_COMPA_vect` is the interrupt vector name — the AVR hardware knows to call this function when Timer1 hits `OCR1A`.

`PORTB ^= (1 << PB5)` uses XOR to toggle bit 5. XOR with 1 flips a bit: if it was 0 it becomes 1, if it was 1 it becomes 0. This toggles Pin 13 between HIGH and LOW on every interrupt — producing a 1-second blink.

---

### loop() runs freely
```cpp
void loop() {
    PORTB |=  (1 << PB3);   // Pin 11 HIGH
    delay(150);
    PORTB &= ~(1 << PB3);   // Pin 11 LOW
    delay(150);
}
```
The green LED blinks at its own rate driven by `loop()`. The timer interrupt fires in the background every second — pausing `loop()` for a few microseconds to run the ISR, then resuming exactly where it left off. From the green LED's perspective, nothing was interrupted.

---

## What to Observe

Upload the code and watch both LEDs. The red LED blinks at a steady, exact 1-second pace. The green LED blinks faster at its own rate. They are completely independent — changing the green LED's timing has zero effect on the red LED's timing.

---

## Practice Tasks

1. **Change the interval:** Modify `OCR1A` to make the red LED blink every 500ms. Show your full calculation before changing the code. (Answer to verify: OCR1A = 7812)

2. **Change the prescaler:** Switch to prescaler 256 (set only CS12, clear CS10). Recalculate OCR1A for a 1-second interval.

3. **Count to 10:** Add a second `volatile int` variable. Print "10 seconds elapsed!" to Serial Monitor every time it reaches 10, then reset it.

4. **Compare with digitalWrite:** Replace `PORTB ^= (1 << PB5)` with `digitalWrite(13, !digitalRead(13))`. Does it still work? Run both versions with a logic analyser or oscilloscope if available — the register version is significantly faster.
