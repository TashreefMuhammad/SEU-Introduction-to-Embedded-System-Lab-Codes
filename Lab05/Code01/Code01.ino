#include <Adafruit_LiquidCrystal.h>

// Initialize LCD (Tinkercad usually works with address 0)
Adafruit_LiquidCrystal lcd(0);

void setup() {
  
  // Initialize LCD
  lcd.begin(16, 2);
  
  // Turn on backlight
  lcd.setBacklight(1);

  // Display welcome message
  lcd.setCursor(0, 0);
  lcd.print("Embedded Lab");

  lcd.setCursor(0, 1);
  lcd.print("LCD Demo");

  delay(3000);

  lcd.clear();
}

void loop() {

  // Display counter heading
  lcd.setCursor(0,0);
  lcd.print("Counter:");

  // Count from 0 to 20
  for(int i = 0; i <= 20; i++)
  {
    lcd.setCursor(9,0);
    lcd.print("   ");   // clear previous number
    lcd.setCursor(9,0);
    lcd.print(i);

    delay(500);
  }

  lcd.clear();

  // Second screen
  lcd.setCursor(0,0);
  lcd.print("SEU CSE382");

  lcd.setCursor(0,1);
  lcd.print("Ready...");

  delay(3000);

  lcd.clear();
}