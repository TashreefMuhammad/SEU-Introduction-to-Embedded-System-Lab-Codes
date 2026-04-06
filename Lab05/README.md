# Lab 05: Display and Input Interfaces (LCD + Keypad)

## 🎯 Objective
Interface a 16x2 LCD display and a 4x4 matrix keypad with Arduino.

## 🧠 Concepts Covered
- I2C communication (LCD)
- Matrix keypad scanning
- Display output
- Combined input-output systems

## 🔧 Components Required
- Arduino Uno
- 16x2 LCD Display (I2C)
- 4x4 Matrix Keypad
- Jumper wires

## 🔌 Pin Configuration
- LCD (I2C): SDA → A4, SCL → A5
- Keypad Rows: Pins 9, 8, 7, 6
- Keypad Columns: Pins 5, 4, 3, 2

## 📜 Code Descriptions
- **Code01:** LCD display — counter and welcome message demo
- **Code02:** 4x4 Keypad — read and print key presses to Serial Monitor
- **Code03:** Combined — keypad input displayed on LCD screen

## 🔗 Tinkercad Simulations
- LCD: https://www.tinkercad.com/things/jOmdscUwkKy
- Keypad: https://www.tinkercad.com/things/iSIdo5Og2Bd
- Combined: https://www.tinkercad.com/things/1WfpXofUQ1M

## ▶️ How to Run
Install required libraries first:
- `Adafruit LiquidCrystal` (for LCD)
- `Keypad` (for 4x4 keypad)

## 🧪 Practice Task (In-Lab)
- Display a countdown timer on the LCD
- Build a simple PIN entry system using keypad + LCD

## 📈 Expected Learning Outcome
Students understand display interfaces, I2C communication, and combined input-output system design.
