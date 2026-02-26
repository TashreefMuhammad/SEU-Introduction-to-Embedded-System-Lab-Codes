void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 50; i <= 250; ++i) {
    analogWrite(11, i);
    delay(200);
  }
  for(int i = 250; i >= 50; --i) {
    analogWrite(11, i);
    delay(200);
  }
}
