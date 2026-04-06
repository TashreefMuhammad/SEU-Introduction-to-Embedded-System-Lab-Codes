// Lab 10 - Code 03: Timer Interrupt (Bare-Metal)
// Board: Arduino Uno
// No libraries — only AVR hardware registers

#include <avr/io.h>
#include <avr/interrupt.h>

volatile int seconds = 0;

ISR(TIMER1_COMPA_vect) {
    seconds++;
    PORTB ^= (1 << PB5);
}

void setup() {
    DDRB |= (1 << PB5);
    DDRB |= (1 << PB3);

    Serial.begin(9600);

    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
    OCR1A  = 15624;
    TIMSK1 = (1 << OCIE1A);

    sei();

    Serial.println("Timer running. Red = 1 sec. Green = free.");
}

void loop() {
    PORTB |=  (1 << PB3);
    delay(150);
    PORTB &= ~(1 << PB3);
    delay(150);

    Serial.print("Seconds: ");
    Serial.println(seconds);
}
