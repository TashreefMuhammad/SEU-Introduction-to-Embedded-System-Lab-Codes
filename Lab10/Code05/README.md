# Code 05 — Memory-Mapped I/O: Raw Address Access

## Board
Arduino Uno (ATmega328P)

## Components
| Component | Arduino Pin | AVR Pin |
|-----------|------------|---------|
| Red LED + 330Ω | Pin 13 | PB5 |

---

## What This Code Does

Turns Pin 13 ON and OFF using a raw memory address pointer — the most direct form of memory-mapped I/O possible in C.

Three ways are provided. All produce physically identical output on Pin 13. This proves the central idea from your theory notes:

> *"Hardware is memory. The CPU controls physical pins by reading and writing to specific addresses — exactly as it would read and write RAM."*

---

## The Core Idea — Memory-Mapped I/O Explained

In a normal computer, memory addresses hold data. Write a value to address X and later read it back — you get that value.

In a microcontroller, some addresses are wired directly to hardware. Writing to address `0x25` does not store a number in a memory cell — it changes the voltage on physical pins. Reading from address `0x23` does not retrieve stored data — it reports the current voltage levels on the pins right now.

The CPU has no idea it is doing anything special. It issues the same LOAD and STORE instructions it always does. The hardware takes care of making the right physical thing happen.

```
CPU writes 0b00100000 to address 0x25
                ↓
    Hardware sees: bit 5 is 1
                ↓
    Pin 13 voltage goes to 5V
                ↓
    LED turns ON
```

---

## The Pointer Declaration

```cpp
volatile uint8_t* PORTB_PTR = (volatile uint8_t*) 0x25;
```

This single line contains several parts. Here is each one explained:

---

### `uint8_t`
An unsigned 8-bit integer — a number from 0 to 255, stored in exactly 1 byte. PORTB is 8 bits wide (one bit per pin in Port B), so `uint8_t` is the correct type to describe what is at that address.

---

### `uint8_t*`
A pointer to a `uint8_t`. In C, a pointer holds a memory address rather than a value. Instead of storing the number 37, it stores the address *where* 37 lives.

---

### `volatile`
Tells the compiler: *"do not assume this memory location is stable — it can change at any time for reasons you cannot see in the code."*

Without `volatile`, the compiler might read PORTB once, store the result in a CPU register, and reuse that cached copy instead of re-reading the actual hardware register. This would cause the code to work with stale data and the LED to behave incorrectly.

Hardware registers change when pins change state. The compiler cannot predict this. `volatile` forces a fresh read every time.

---

### `(volatile uint8_t*) 0x25`
A cast. The number `0x25` (37 in decimal) is just an integer. The cast `(volatile uint8_t*)` tells the compiler: *"treat this integer as a memory address pointing to a volatile 8-bit value."* This is how you create a pointer to a specific hardware register address.

---

### The complete declaration
```cpp
volatile uint8_t* PORTB_PTR = (volatile uint8_t*) 0x25;
```
*"PORTB_PTR is a pointer to a volatile 8-bit value located at memory address 0x25."*

When the ATmega328P receives a write to address 0x25, its internal hardware drives Port B pins accordingly. When you write to `*PORTB_PTR`, you are writing to address 0x25 — and physical pins change state.

---

## The Dereference Operator: `*`

```cpp
*PORTB_PTR |= (1 << 5);
```

The `*` before a pointer means: *"go to the address this pointer holds and work with what is there."*

Without `*`:
```cpp
PORTB_PTR           // This is the address itself: 0x25
```

With `*`:
```cpp
*PORTB_PTR          // This is the 8-bit value AT address 0x25 — the PORTB register
```

Reading `*PORTB_PTR` retrieves the current state of Port B.
Writing to `*PORTB_PTR` changes Port B — and therefore changes pin voltages.

---

## Operator Breakdown — Every Operation in Loop()

### Turn LED ON
```cpp
*PORTB_PTR |= (1 << 5);
```

**Step 1 — `(1 << 5)`:** Left shift. Creates a byte with only bit 5 set.
```
1          = 0b00000001
1 << 5     = 0b00100000   ← bit 5 is 1, everything else is 0
```

**Step 2 — `|=`:** OR-assign. Sets bit 5 in PORTB without disturbing other bits.
```
*PORTB_PTR before:  0b00000000
mask (1 << 5):      0b00100000
Result after OR:    0b00100000   ← bit 5 now 1 → Pin 13 HIGH → LED ON
```

---

### Turn LED OFF
```cpp
*PORTB_PTR &= ~(1 << 5);
```

**Step 1 — `(1 << 5)`:** Same mask as before: `0b00100000`

**Step 2 — `~`:** Bitwise NOT. Inverts every bit.
```
(1 << 5):    0b00100000
~(1 << 5):   0b11011111   ← 0 only at bit 5
```

**Step 3 — `&=`:** AND-assign. Clears bit 5 while leaving all other bits alone.
```
*PORTB_PTR before:  0b00100000
mask ~(1 << 5):     0b11011111
Result after AND:   0b00000000   ← bit 5 now 0 → Pin 13 LOW → LED OFF
```

---

### Read back the register value
```cpp
Serial.println(*PORTB_PTR, BIN);
```
Reads the 8-bit value at address 0x25 and prints it in binary. When the LED is ON, bit 5 will be 1. When OFF, bit 5 will be 0.

---

### Read actual pin state
```cpp
(*PINB_PTR >> 5) & 0x01
```
`PINB_PTR` points to address 0x23 — the Pin Input register for Port B.

**`>> 5`:** Right shift by 5 positions — moves bit 5 down to bit 0.
```
*PINB_PTR:       0b00100000
>> 5:            0b00000001
```

**`& 0x01`:** Masks out all bits except bit 0, leaving only a clean 0 or 1.

This reads the actual electrical state of Pin 13 at this moment.

---

## PORTB vs PINB — Why Two Different Addresses?

| Register | Address | What it does |
|----------|---------|--------------|
| PORTB | 0x25 | What you told the pin to be (your written value) |
| PINB | 0x23 | What the pin actually is right now (measured voltage) |

For an output pin these are normally the same. But on an input pin, PORTB controls the pull-up resistor and PINB reports the actual external voltage. They are fundamentally different things — which is why they need separate addresses.

---

## The Three Ways — Side by Side

| | Way 1 | Way 2 | Way 3 |
|--|-------|-------|-------|
| Turn ON | `digitalWrite(13, HIGH)` | `PORTB \|= (1 << PB5)` | `*PORTB_PTR \|= (1 << 5)` |
| Turn OFF | `digitalWrite(13, LOW)` | `PORTB &= ~(1 << PB5)` | `*PORTB_PTR &= ~(1 << 5)` |
| Abstraction level | High — hides everything | Medium — register name | None — raw address |
| Speed | Slowest | Fast | Fast (identical to Way 2) |

Way 2 and Way 3 are electrically and functionally identical. `PORTB` is simply a name that the AVR header files (`avr/io.h`) define as `*(volatile uint8_t*)0x25`. Writing `PORTB` is the same as writing `*PORTB_PTR` — the compiler produces the same machine code for both.

---

## Practice Tasks

1. **Run all three ways:** Switch between Way 1, Way 2, and Way 3 by commenting/uncommenting. Is the LED behaviour identical each time?

2. **Print the address:** Add `Serial.println((uint16_t)PORTB_PTR, HEX)`. What does it print? Does it match 0x25?

3. **Verify Way 2 = Way 3:** Look up the definition of PORTB in your AVR header file (`avr/io.h`). Find the line that defines PORTB. What does it expand to?

4. **Toggle using XOR:** Add a third section that toggles Pin 13 using `*PORTB_PTR ^= (1 << 5)`. Explain in one sentence why XOR produces a toggle.

5. **Two pins at once:** Using a single write to `*PORTB_PTR`, turn Pin 13 ON and Pin 12 ON simultaneously. What value do you write? Why can you not do this with `digitalWrite()` in a single call?

6. **Remove volatile:** Remove `volatile` from the pointer declaration. Upload and observe. Does the LED stop blinking correctly? Explain what the compiler likely did without volatile.
