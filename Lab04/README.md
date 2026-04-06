# Lab 04: Motor Control (DC, Servo, Stepper)

## 🎯 Objective
Control different types of motors using Arduino.

## 🧠 Concepts Covered
- PWM Control
- Motor Drivers (L298N)
- Actuator types: DC, Servo, Stepper

## 🔧 Components Required
- DC Motor
- Servo Motor
- Stepper Motor (28BYJ-48)
- L298N Motor Driver
- Arduino Uno

## 🔌 Pin Configuration
- DC Motor (L298N): ENA → Pin 9, IN1 → Pin 7, IN2 → Pin 6
- Servo: Signal → Pin 10
- Stepper: IN1→8, IN3→10, IN2→9, IN4→11

## 📜 Code Descriptions
- **Code01:** DC motor without motor driver (basic direction control)
- **Code02:** DC motor with L298N — forward, stop, reverse
- **Code03:** DC motor speed ramping up and down via PWM
- **Code04:** Servo motor sweeping 0° to 180° and back
- **Code05:** Stepper motor full revolution clockwise and counter-clockwise

## ▶️ How to Run
Upload each code and observe the corresponding motor behavior.

## 🧪 Practice Task (In-Lab)
- Change motor speed and direction on button press
- Map a potentiometer to servo angle using analogRead and map()

## 📈 Expected Learning Outcome
Students understand actuator control, PWM, and motor driver usage.
