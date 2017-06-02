const int switchPin = 2;

void setup() {
  pinMode(switchPin, INPUT);
}

void loop() {

if(digitalRead(switchPin) == LOW)
  digitalWrite(ledPin, LOW);
else
  digitalWrite(ledPin, HIGH);

}
