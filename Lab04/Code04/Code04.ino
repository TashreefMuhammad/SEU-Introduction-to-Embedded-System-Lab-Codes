// Servo Motor
#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(10);   // signal pin
}

void loop() {

  // move from 0° to 180°
  for(int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);
    delay(20);
  }

  // move back from 180° to 0°
  for(int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    delay(20);
  }

}