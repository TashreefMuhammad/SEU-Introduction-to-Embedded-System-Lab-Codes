const int LED1 = 10;
const int LED2 = 11;

const int IN1 = 7;
const int IN2 = 8;

int mode = 0;

// Blink timing
unsigned long previousMillis = 0;
const unsigned long blinkInterval = 500;
bool blinkState = false;

// Breathing timing
int brightness = 0;
int fadeAmount = 5;
unsigned long previousFadeMillis = 0;
const unsigned long fadeInterval = 20;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  pinMode(IN1, INPUT);
  pinMode(IN2, INPUT);
}

void loop() {

  readInputs();
  updateOutputs();
}

void readInputs() {

  int val1 = digitalRead(IN1);
  int val2 = digitalRead(IN2);

  if (val1 == LOW && val2 == HIGH) {
    mode = 1;
  }
  else if (val1 == HIGH && val2 == LOW) {
    mode = 2;
  }
  else if (val1 == HIGH && val2 == HIGH) {
    mode = 3;
  }
  else {
    mode = 0;  // idle or undefined
  }
}

void updateOutputs() {

  unsigned long currentMillis = millis();

  if (mode == 1) {
    digitalWrite(LED2, HIGH);

    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      blinkState = !blinkState;
      digitalWrite(LED1, blinkState);
    }
  }

  else if (mode == 2) {
    digitalWrite(LED1, HIGH);

    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      blinkState = !blinkState;
      digitalWrite(LED2, blinkState);
    }
  }

  else if (mode == 3) {
    digitalWrite(LED1, HIGH);

    if (currentMillis - previousFadeMillis >= fadeInterval) {
      previousFadeMillis = currentMillis;

      analogWrite(LED2, brightness);
      brightness += fadeAmount;

      if (brightness <= 0 || brightness >= 255) {
        fadeAmount = -fadeAmount;
      }
    }
  }

  else {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
}
