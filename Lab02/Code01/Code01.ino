const int LED1 = 10;
const int LED2 = 11;

int mode = 0;

// Timing variables for blinking
unsigned long previousMillis = 0;
const unsigned long blinkInterval = 500;  // 500 ms

bool ledState = false;

// Variables for breathing effect
int brightness = 0;
int fadeAmount = 5;
unsigned long previousFadeMillis = 0;
const unsigned long fadeInterval = 20; // controls speed of breathing

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  Serial.begin(9600);
  Serial.println("Enter 1, 2, or 3:");
}

void loop() {
  handleSerialInput();
  updateMode();
}

void handleSerialInput() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == '1') {
      mode = 1;
      Serial.println("Mode 1: LED1 blink, LED2 ON");
    }
    else if (command == '2') {
      mode = 2;
      Serial.println("Mode 2: LED2 blink, LED1 ON");
    }
    else if (command == '3') {
      mode = 3;
      Serial.println("Mode 3: LED1 ON, LED2 breathing");
    }
  }
}

void updateMode() {
  unsigned long currentMillis = millis();

  if (mode == 1) {
    // LED2 always ON
    digitalWrite(LED2, HIGH);

    // LED1 blinking
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(LED1, ledState);
    }
  }

  else if (mode == 2) {
    // LED1 always ON
    digitalWrite(LED1, HIGH);

    // LED2 blinking
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(LED2, ledState);
    }
  }

  else if (mode == 3) {
    // LED1 always ON
    digitalWrite(LED1, HIGH);

    // LED2 breathing effect
    if (currentMillis - previousFadeMillis >= fadeInterval) {
      previousFadeMillis = currentMillis;

      analogWrite(LED2, brightness);

      brightness += fadeAmount;

      if (brightness <= 0 || brightness >= 255) {
        fadeAmount = -fadeAmount;
      }
    }
  }
}