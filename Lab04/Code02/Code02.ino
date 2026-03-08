// DC Motor
// L298N Motor Driver Pins
const int ENA = 9;   // PWM speed control
const int IN1 = 7;   // Direction
const int IN2 = 6;   // Direction

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void loop() {

  // MOTOR FORWARD
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 200);   // speed (0-255)

  delay(3000);

  // MOTOR STOP
  analogWrite(ENA, 0);

  delay(2000);

  // MOTOR REVERSE
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 200);

  delay(3000);

  // STOP AGAIN
  analogWrite(ENA, 0);

  delay(2000);
}