#include <Keypad.h>

/*

      C1 C2 C3 C4
R1 -> 1  2  3  A
R2 -> 4  5  6  B
R3 -> 7  8  9  C
R4 -> *  0  #  D

*/

// Define keypad layout
char keys[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Row and column pins
byte rowPins[4] = {9, 8, 7, 6};
byte colPins[4] = {5, 4, 3, 2};

// Create keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

void setup()
{
  Serial.begin(9600);
  Serial.println("Keypad Ready");
}

void loop()
{
  char key = keypad.getKey();

  if (key)  // if a key is pressed
  {
    Serial.print("Key Pressed: ");
    Serial.println(key);
  }
}