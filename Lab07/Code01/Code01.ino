#include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 10

Servo myServo;

long duration;
int distance;

void setup() {
  myServo.attach(6);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

void loop() {
  distance = getDistance();

  Serial.println(distance);

  int angle = map(distance, 0, 100, 0, 180);
  angle = constrain(angle, 0, 180);

  myServo.write(angle);

  delay(200);
}