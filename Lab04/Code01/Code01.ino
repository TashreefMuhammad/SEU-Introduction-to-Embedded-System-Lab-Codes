// DC Motor
// Without Motor Driver
const int IN1 = 6;
const int IN2 = 5;
void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void loop()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(5000); // Wait for 1000 millisecond(s)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(5000); // Wait for 1000 millisecond(s)
}