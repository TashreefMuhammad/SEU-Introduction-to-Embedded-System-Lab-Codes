# Lab 10: Interrupts and Memory-Mapped I/O

## Board
Arduino Uno (ATmega328P) — all codes

---

## Objective
Understand interrupt-driven programming and direct hardware register access, connecting what was taught in theory class to working, observable code.

---

## Learning Approach

This lab is designed to be done **in order**. Each code builds on the previous one.

| Code | Topic | What you learn |
|------|-------|---------------|
| Code 01 | The Polling Problem | Why polling fails — feel the problem firsthand |
| Code 02 | External Interrupt | How interrupts solve the polling problem |
| Code 03 | Timer Interrupt (Bare-Metal) | Configure Timer1 registers, fire ISR every 1 second |
| Code 04 | Abstraction vs Registers | Arduino functions vs direct DDRB/PORTB/PINB writes |
| Code 05 | Memory-Mapped I/O | Raw address pointers — the deepest level |

---

## Components Required (Full Lab)

| Component | Quantity | Used In |
|-----------|----------|---------|
| Arduino Uno | 1 | All codes |
| LED (any colour) | 3 | Code 01–05 |
| Push button | 1–2 | Code 01–04 |
| Resistor 330Ω | 3 | All codes with LEDs |
| Breadboard | 1 | All codes |
| Jumper wires | Several | All codes |

---

## Pin Reference

| Arduino Pin | AVR Name | Port | Bit | Used In |
|-------------|----------|------|-----|---------|
| Pin 2 | PD2 | D | 2 | Code 02 (INT0 — interrupt only) |
| Pin 7 | PD7 | D | 7 | Code 01, 04 |
| Pin 8 | PB0 | B | 0 | Code 04 |
| Pin 10 | PB2 | B | 2 | Code 02 |
| Pin 11 | PB3 | B | 3 | Code 01, 02, 03 |
| Pin 12 | PB4 | B | 4 | Code 04 |
| Pin 13 | PB5 | B | 5 | Code 03, 04, 05 |

---

## ATmega328P Register Reference

| Register | Address | Purpose |
|----------|---------|---------|
| PINB | 0x23 | Read Port B pin states |
| DDRB | 0x24 | Port B direction (1=output, 0=input) |
| PORTB | 0x25 | Port B output / pull-up |
| PIND | 0x29 | Read Port D pin states |
| DDRD | 0x2A | Port D direction |
| PORTD | 0x2B | Port D output / pull-up |
| TCCR1A | 0x80 | Timer1 control register A |
| TCCR1B | 0x81 | Timer1 control register B (mode + prescaler) |
| OCR1A | 0x88 | Timer1 compare value |
| TIMSK1 | 0x6F | Timer1 interrupt enable |

---

## Key Rules — Quick Reference

### ISR Rules (Code 02, 03)
- Keep ISRs short — do minimal work inside them
- No `delay()` inside an ISR
- No `Serial.print()` inside an ISR
- Any variable shared between an ISR and `loop()` must be `volatile`
- Set a flag in the ISR, handle the action in `loop()`

### Bit Manipulation Reference
| Operation | Syntax | Effect |
|-----------|--------|--------|
| Set bit n HIGH | `REG \|= (1 << n)` | Turn pin ON |
| Set bit n LOW | `REG &= ~(1 << n)` | Turn pin OFF |
| Toggle bit n | `REG ^= (1 << n)` | Flip pin state |
| Read bit n | `(REG >> n) & 0x01` | Returns 0 or 1 |

---

## Connection to Theory Notes

| Theory Concept | Where Practised |
|----------------|----------------|
| Memory-mapped I/O philosophy | Code 05 — raw address pointer |
| GPIO registers DDRx, PORTx, PINx | Code 04 and 05 |
| Benefits of memory-mapped I/O | Code 04 — single-cycle access, unified programming model |
| Trade-offs (volatile required) | Code 02, 04, 05 — volatile demonstrated and broken deliberately |
| Timer PSC and compare value design | Code 03 — OCR1A calculated from scratch |
| Interrupt-driven design | Code 01 vs Code 02 — polling problem demonstrated |

---

## Important Notes

- Button for external interrupt **must be on Pin 2 or Pin 3** — these are the only hardware interrupt pins on Arduino Uno
- All register-level code in this lab is specific to **ATmega328P** — register addresses differ on other microcontrollers
- Read each code's individual README before uploading — each one has observation questions to answer before and after running
