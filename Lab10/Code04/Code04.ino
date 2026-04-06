// Lab 10 - Code 04: Arduino Abstraction vs Direct Registers
// Board: Arduino Uno
//
// Run VERSION A first, then VERSION B.
// LED behaviour must be identical — proving Arduino functions
// are wrappers around the same register writes.

// ── VERSION A: Arduino functions ──────────────────────────
// Comment out Version B below and uncomment this block.

/*
void setup() {
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(8,  OUTPUT);
    pinMode(7,  INPUT_PULLUP);
    Serial.begin(9600);
    Serial.println("Version A: Arduino abstraction");
}

void loop() {
    bool pressed = (digitalRead(7) == LOW);
    if (pressed) {
        digitalWrite(13, HIGH);
        digitalWrite(12, LOW);
        digitalWrite(8,  HIGH);
        Serial.println("Button pressed — Red + Blue ON");
    } else {
        digitalWrite(13, LOW);
        digitalWrite(12, HIGH);
        digitalWrite(8,  LOW);
        Serial.println("No press — Green ON");
    }
    delay(200);
}
*/

// ── VERSION B: Direct register access ─────────────────────
void setup() {
    DDRB |= (1 << PB5) | (1 << PB4) | (1 << PB0);
    DDRD &= ~(1 << PD7);
    PORTD |= (1 << PD7);
    Serial.begin(9600);
    Serial.println("Version B: Direct registers");
}

void loop() {
    bool pressed = !(PIND & (1 << PD7));
    if (pressed) {
        PORTB |=  (1 << PB5);
        PORTB &= ~(1 << PB4);
        PORTB |=  (1 << PB0);
        Serial.println("Button pressed — Red + Blue ON");
    } else {
        PORTB &= ~(1 << PB5);
        PORTB |=  (1 << PB4);
        PORTB &= ~(1 << PB0);
        Serial.println("No press — Green ON");
    }
    delay(200);
}
