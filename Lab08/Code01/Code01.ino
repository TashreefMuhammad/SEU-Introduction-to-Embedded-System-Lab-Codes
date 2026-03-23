#define PIR_PIN 7
#define LED_PIN 11
#define BUZZER_PIN 5

int state = 0;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int motion = digitalRead(PIR_PIN);

  if (motion == HIGH) {
    state = 1;
  } else {
    state = 0;
  }

  if (state == 1) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);
  } else {
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  Serial.println(state);
  delay(200);
}