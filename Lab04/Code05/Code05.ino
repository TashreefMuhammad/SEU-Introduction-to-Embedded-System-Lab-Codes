// Stepper Motor
#include <Stepper.h>

const int stepsPerRevolution = 2048;

// IN1, IN3, IN2, IN4 order works best for 28BYJ-48
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {

  myStepper.setSpeed(10); // RPM
}

void loop() {

  // rotate clockwise
  myStepper.step(stepsPerRevolution);

  delay(1000);

  // rotate counter-clockwise
  myStepper.step(-stepsPerRevolution);

  delay(1000);
}