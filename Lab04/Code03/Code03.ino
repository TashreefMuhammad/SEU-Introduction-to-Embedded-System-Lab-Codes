// DC Motor
// L298N Motor Driver Pins
const int ENA = 9;
const int IN1 = 7;
const int IN2 = 6;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // set motor direction
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void loop() {

  // Gradually increase speed
  for (int speed = 0; speed <= 255; speed++) {
    analogWrite(ENA, speed);
    delay(200);
  }

  delay(1000);

  // Gradually decrease speed
  for (int speed = 255; speed >= 0; speed--) {
    analogWrite(ENA, speed);
    delay(200);
  }

  delay(1000);
}