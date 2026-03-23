#define PIR_PIN 7
#define TRIG_PIN 9
#define ECHO_PIN 10
#define LED_PIN 11

long duration;
int distance;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
}

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}

void loop() {
  int motion = digitalRead(PIR_PIN);
  int dist = getDistance();

  Serial.print("Motion: ");
  Serial.print(motion);
  Serial.print(" | Distance: ");
  Serial.println(dist);

  if (motion == HIGH && dist < 50) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  delay(200);
}