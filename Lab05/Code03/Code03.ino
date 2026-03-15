#include <Keypad.h>
#include <Adafruit_LiquidCrystal.h>

// LCD initialization
Adafruit_LiquidCrystal lcd(0x27);

// Keypad layout
char keys[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Pin configuration
byte rowPins[4] = {9,8,7,6};
byte colPins[4] = {5,4,3,2};

// Create keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

void setup()
{
  lcd.begin(16,2);
  lcd.setBacklight(1);

  lcd.setCursor(0,0);
  lcd.print("Keypad Ready");
  
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Press Key:");
}

void loop()
{
  char key = keypad.getKey();

  if(key)
  {
    lcd.clear();
    if(key == '#') {
      	lcd.setCursor(0,0);
    	lcd.print("CSE382");
    }
    else if(key == '*') {
      	lcd.setCursor(0,1);
    	lcd.print("Embedded lab");
    }
    else{
      	lcd.print("Press Key:");
    	lcd.setCursor(0,1);
    	lcd.print("Key: ");
    	lcd.print(key);
    }
    lcd.print("   "); // clear leftovers
  }
}