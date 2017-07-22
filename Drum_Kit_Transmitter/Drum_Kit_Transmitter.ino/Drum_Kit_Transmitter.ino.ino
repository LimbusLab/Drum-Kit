const int redLED = 12;
const int whiteLED = 11;
const int blueLED = 10;
const int switchPins[] = {2, 3, 4, 5, 6, 7, 8, 9};

const char drumKeys[] = {'q', 'e', 'w', 'k', 'y', 'r', 'u'};

const int speedPot = A0;
const int switchPot = A1;
unsigned long previousMillis = 0;
unsigned long previousBeatMillis = 0;

const int enterSwitch = A7;

boolean bounce = false;

int sendBeats = -1;
int drumSelect;

boolean tamStates[] = {false, false, false, false, false, false, false, false};
boolean drumStates[] = {false, false, false, false, false, false, false, false};
boolean kickStates[] = {false, false, false, false, false, false, false, false};

int stateLocation = 0;

int beat = 200;

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(A3));
  pinMode(redLED, OUTPUT);
  pinMode(whiteLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  for (int j = 0; j < sizeof(switchPins); j++) {
    pinMode(switchPins[j], INPUT);
  }
}

void loop() {
  drumSelect = map(analogRead(switchPot), 1023, 0, 4, 1);
  if (drumSelect == 1) {
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(whiteLED, LOW);
    for (int i = 0; i < sizeof(kickStates); i++) {
      kickStates[i] = digitalRead(switchPins[i]);
    }
  }
  if (drumSelect == 2) {
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(whiteLED, HIGH);
    for (int i = 0; i < sizeof(tamStates); i++) {
      tamStates[i] = digitalRead(switchPins[i]);
    }
  }
  if (drumSelect == 3) {
    digitalWrite(blueLED, HIGH);
    digitalWrite(redLED, LOW);
    digitalWrite(whiteLED, LOW);

    for (int i = 0; i < sizeof(drumStates); i++) {
      drumStates[i] = digitalRead(switchPins[i]);
    }
  }
  if (drumSelect == 4) {
    speedControl();
  }


  if (analogRead(enterSwitch) == 1023 && bounce == false) {
    //readSwitches();
    sendBeats = sendBeats * -1;
    //Serial.println(sendBeats);
    bounce = true;
  }
  if (analogRead(enterSwitch) == 0 && bounce == true) {
    bounce = false;
  }
}

void speedControl() {
  digitalWrite(blueLED, LOW);
  digitalWrite(whiteLED, LOW);

  //Serial.println(allSwitches());

  unsigned long currentMillis = millis();
  int beatReading = analogRead(speedPot);
  beat = map(beatReading, 1023, 0, 100, 250);
  /*
    if (currentMillis - previousBeatMillis >= beat * 4) { //Multiplied by 4 to display quarter beat
      previousBeatMillis = currentMillis;
      //digitalWrite(redLED, HIGH);
    }
  */
  if (currentMillis - previousMillis >= 50) {
    digitalWrite(redLED, LOW);
    digitalWrite(whiteLED, LOW);
    digitalWrite(blueLED, LOW);
  }

  if (currentMillis - previousMillis >= beat) {

    if (tamStates[stateLocation] == true && kickStates[stateLocation] == false && drumStates[stateLocation] == false) {
      if (sendBeats == 1) {
        if (allSwitches() == true) {
          checkRandom('q');
        }
        else Serial.write('q');
      }
      digitalWrite(whiteLED, HIGH);
    }
    if (tamStates[stateLocation] == false && kickStates[stateLocation] == true && drumStates[stateLocation] == false) {
      if (sendBeats == 1) {
        Serial.write('e');
      }
      digitalWrite(redLED, HIGH);
    }
    if (tamStates[stateLocation] == false && kickStates[stateLocation] == false && drumStates[stateLocation] == true) {
      if (sendBeats == 1) {
        if (allSwitches() == true) {
          checkRandom('w');
        }
        else Serial.write('w');
      }
      digitalWrite(blueLED, HIGH);
    }
    if (tamStates[stateLocation] == true && kickStates[stateLocation] == true && drumStates[stateLocation] == false) {
      if (sendBeats == 1) {
        Serial.write('k');
      }
      digitalWrite(whiteLED, HIGH);
      digitalWrite(redLED, HIGH);
    }
    if (tamStates[stateLocation] == false && kickStates[stateLocation] == true && drumStates[stateLocation] == true) {
      if (sendBeats == 1) {
        Serial.write('y');
      }
      digitalWrite(redLED, HIGH);
      digitalWrite(blueLED, HIGH);
    }
    if (tamStates[stateLocation] == true && kickStates[stateLocation] == false && drumStates[stateLocation] == true) {
      if (sendBeats == 1) {
        if (allSwitches() == true) {
          checkRandom('r');
        }
        else Serial.write('r');
      }
      digitalWrite(whiteLED, HIGH);
      digitalWrite(blueLED, HIGH);
    }
    if (tamStates[stateLocation] == true && kickStates[stateLocation] == true && drumStates[stateLocation] == true) {
      if (sendBeats == 1) {
        Serial.write('u');
      }
      digitalWrite(whiteLED, HIGH);
      digitalWrite(blueLED, HIGH);
      digitalWrite(redLED, HIGH);
    }
    else {
      if (allSwitches() == true && sendBeats == 1) {
        checkRandom('p'); // char p will do nothing
      }
    }

    stateLocation++;

    if (stateLocation > 7) {
      stateLocation = 0;
    }
    previousMillis = currentMillis;

  }
}

boolean allSwitches() {
  boolean switchHigh = true;
  for (int i = 0; i < sizeof(kickStates); i++) {
    if (digitalRead(switchPins[i]) == LOW) {
      switchHigh = false;
    }
  }
  return switchHigh;
}

void checkRandom(char drumSelect) {
  int randomNumber;
  if (drumSelect != 'p') randomNumber = random(0, 10);
  else randomNumber = random(0, 20);
  if (randomNumber <= 1) {
    int r = random(0, sizeof(drumKeys));
    Serial.write(drumKeys[r]);
  }
  else Serial.write(drumSelect);
}

