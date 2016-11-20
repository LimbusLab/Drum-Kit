/*
Characters are 'k', 't', 'd'
*/


const int tamPin = 10;
const int drumPin = 9;
const int kickPin = 11;


const int delayTime = 50;



void setup() {
  Serial.begin(115200);
  pinMode(tamPin, OUTPUT);
  pinMode(drumPin, OUTPUT);
  pinMode(kickPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char reading = Serial.read();
    if (reading == 'k') {
      turnOn(0, 0, 1);
    }
    if (reading == 't') {
      turnOn(1, 0, 0);
    }
    if (reading == 'd') {
      turnOn(0, 1, 0);
    }
  }

}

void turnOn(int tempTam, int tempDrum, int tempKick) {
  if (tempTam == 1) digitalWrite(tamPin, LOW);
  if (tempDrum == 1) digitalWrite(drumPin, LOW);
  if (tempKick == 1) digitalWrite(kickPin, LOW);

  delay(delayTime);
  digitalWrite(tamPin, HIGH);
  digitalWrite(drumPin, HIGH);
  digitalWrite(kickPin, HIGH);

}

