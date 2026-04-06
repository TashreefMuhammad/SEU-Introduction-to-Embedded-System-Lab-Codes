// Lab 10 - Code 01: The Polling Problem
// Board: Arduino Uno

const int LED_BUSY   = 11;
const int BUTTON_PIN = 7;

int pressCount = 0;

void setup() {
    pinMode(LED_BUSY, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.begin(9600);
    Serial.println("Polling Demo — press button while LED is ON.");
}

void loop() {
    digitalWrite(LED_BUSY, HIGH);
    delay(3000);
    digitalWrite(LED_BUSY, LOW);
    delay(500);

    if (digitalRead(BUTTON_PIN) == LOW) {
        pressCount++;
        delay(200);
        Serial.print("Press detected. Total: ");
        Serial.println(pressCount);
    }
}
