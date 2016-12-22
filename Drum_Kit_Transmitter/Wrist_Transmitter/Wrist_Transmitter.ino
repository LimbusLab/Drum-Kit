const int redLED = 10;
const int whiteLED = 11;
const int blueLED = 12;
const int switchPins[] = {2, 3, 4, 5, 6, 7, 8, 9};

const int speedPot = A1;

const int enterSwitch = A7;

boolean switchStates[] = {false, false, false, false, false, false, false, false};

char* beats[] = {
  ",t,1,1,0,1,0,0,1,0,d,0,0,0,0,0,0,1,0,k,0,0,1,0,0,0,1,0",
  ",t,0,0,0,0,0,0,0,0,d,0,0,0,0,0,0,0,0,k,0,0,0,0,0,0,0,0"
};
int beat = 200;

void setup() {
  Serial.begin(115200);
  pinMode(redLED, OUTPUT);
  pinMode(whiteLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  for (int j = 0; j < sizeof(switchPins); j++) {
    pinMode(switchPins[j], INPUT);
  }
}

void loop() {
  int beatReading = analogRead(speedPot);
  beat = map(beatReading, 1023, 0, 100, 1000);
  if (analogRead(enterSwitch) == 1023) {
    readSwitches();
  }
}

void readSwitches() {
  for (int i = 0; i < sizeof(switchStates); i++) {
    switchStates[i] = digitalRead(switchPins[i]);
    //Serial.print("switch pin = ");
    //Serial.println(switchStates[i]);
  }
  if (switchStates[0] == true) {
    digitalWrite(whiteLED, HIGH);
    Serial.print("b,");
    Serial.print(beat);
    Serial.println(beats[0]);
    delay(50);
    digitalWrite(whiteLED, LOW);
    delay(500);
  }
  else if (switchStates[1] == true) {
    digitalWrite(whiteLED, HIGH);
    Serial.print("b,");
    Serial.print(beat);
    Serial.println(beats[1]);
    delay(50);
    digitalWrite(whiteLED, LOW);
    delay(500);
  }
  else {
    digitalWrite(whiteLED, HIGH);
    Serial.println("b,190,t,0,0,0,0,0,0,0,0,d,0,0,0,0,0,0,0,0,k,0,0,0,0,0,0,0,0");
    delay(50);
    digitalWrite(whiteLED, LOW);
    delay(500);
  }
}

