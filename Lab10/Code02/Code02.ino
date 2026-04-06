// Lab 10 - Code 02: External Interrupt
// Board: Arduino Uno
// Button MUST be on Pin 2 (INT0) or Pin 3 (INT1)

const int LED_BUSY   = 11;
const int LED_PRESS  = 10;
const int BUTTON_PIN = 2;

volatile int  pressCount    = 0;
volatile bool pressDetected = false;

void buttonISR() {
    pressCount++;
    pressDetected = true;
}

void setup() {
    pinMode(LED_BUSY,   OUTPUT);
    pinMode(LED_PRESS,  OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.begin(9600);

    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);

    Serial.println("Interrupt Demo — press button at ANY time.");
}

void loop() {
    digitalWrite(LED_BUSY, HIGH);
    delay(3000);
    digitalWrite(LED_BUSY, LOW);
    delay(500);

    if (pressDetected) {
        pressDetected = false;
        digitalWrite(LED_PRESS, HIGH);
        delay(100);
        digitalWrite(LED_PRESS, LOW);
        Serial.print("Press captured. Total: ");
        Serial.println(pressCount);
    }
}
