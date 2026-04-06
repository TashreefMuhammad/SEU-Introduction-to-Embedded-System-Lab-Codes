// Lab 10 - Code 05: Memory-Mapped I/O — Raw Address Access
// Board: Arduino Uno
//
// Three ways to turn Pin 13 ON — all produce identical results.
// Uncomment ONE setup block at a time and compare.

#include <avr/io.h>

// Raw pointer to DDRB and PORTB memory addresses
volatile uint8_t* DDRB_PTR  = (volatile uint8_t*) 0x24;
volatile uint8_t* PORTB_PTR = (volatile uint8_t*) 0x25;
volatile uint8_t* PINB_PTR  = (volatile uint8_t*) 0x23;

void setup() {
    Serial.begin(9600);

    // ── WAY 1: Arduino function ───────────────────────────
    // pinMode(13, OUTPUT);

    // ── WAY 2: Register name ──────────────────────────────
    // DDRB |= (1 << PB5);

    // ── WAY 3: Raw memory address ─────────────────────────
    *DDRB_PTR |= (1 << 5);

    Serial.println("Memory-Mapped I/O Demo");
    Serial.println("Writing to address 0x25 controls Pin 13.");
}

void loop() {
    // ── WAY 1 ─────────────────────────────────────────────
    // digitalWrite(13, HIGH);
    // delay(1000);
    // digitalWrite(13, LOW);
    // delay(1000);

    // ── WAY 2 ─────────────────────────────────────────────
    // PORTB |=  (1 << PB5);
    // delay(1000);
    // PORTB &= ~(1 << PB5);
    // delay(1000);

    // ── WAY 3 ─────────────────────────────────────────────
    *PORTB_PTR |= (1 << 5);
    Serial.print("PORTB value (ON):  0b");
    Serial.println(*PORTB_PTR, BIN);
    delay(1000);

    *PORTB_PTR &= ~(1 << 5);
    Serial.print("PORTB value (OFF): 0b");
    Serial.println(*PORTB_PTR, BIN);

    Serial.print("Actual pin state (PINB bit 5): ");
    Serial.println((*PINB_PTR >> 5) & 0x01);
    Serial.println("---");
    delay(1000);
}
