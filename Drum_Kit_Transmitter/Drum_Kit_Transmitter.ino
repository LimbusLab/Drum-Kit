const int kickInput = 4;
const int measures = 4;
const int beatLed = 11;

boolean firstHit = false;

int kick[] = {1, 0, 1, 0, 1, 0, 1, 0};

int beat = 0;
int beginTime = 0;

boolean hit = false;

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

void setup() {
  Serial.begin(115200);
  pinMode(kickInput, INPUT);
  pinMode(beatLed, OUTPUT);
}

void loop() {
  int reading = analogRead(0);
  beat = map(reading, 0, 1023, 200, 800);
  //Serial.println(beat);
  currentMillis = millis();
  blinkKick();
  if (digitalRead(kickInput) == HIGH && firstHit == false) {
    firstHit = true;
    beginTime = millis();
    for (int i = 0; i < 8; i++) {
      kick[i] = 0;
    }
  }
  if (digitalRead(kickInput) == HIGH && firstHit == true) {
    recordKick();
  }
  if (currentMillis - beginTime >= beat * 5 && firstHit == true) {
    firstHit = false;
    for (int i = 0; i < 8; i++) {
      Serial.print(kick[i]);
    }
  }

}

void recordKick(){
  int currentTime = millis() - beginTime;
    int halfBeat = beat / 2;
    int quarterBeat = beat / 4;
    if (currentTime + quarterBeat <= halfBeat) {
      Serial.println("1st");
      kick[0] = 1;
    }
    else if (currentTime + quarterBeat > halfBeat && currentTime + quarterBeat <= halfBeat * 2) {
      Serial.println("2nd");
      kick[1] = 1;
    }
    else if (currentTime + quarterBeat > halfBeat * 2 && currentTime + quarterBeat <= halfBeat * 3) {
      Serial.println("3rd");
      kick[2] = 1;
    }
    else if (currentTime + quarterBeat > halfBeat * 3 && currentTime + quarterBeat <= halfBeat * 4) {
      Serial.println("4th");
      kick[3] = 1;
    }
    else if (currentTime + quarterBeat > halfBeat * 4 && currentTime + quarterBeat <= halfBeat * 5) {
      Serial.println("5th");
      kick[4] = 1;
    }
    else if (currentTime + quarterBeat > halfBeat * 5 && currentTime + quarterBeat <= halfBeat * 6) {
      Serial.println("6th");
      kick[5] = 1;
    }
    else if (currentTime + quarterBeat > halfBeat * 6 && currentTime + quarterBeat <= halfBeat * 7) {
      Serial.println("7th");
      kick[6] = 1;
    }
    else if (currentTime + quarterBeat > halfBeat * 7 && currentTime + quarterBeat <= halfBeat * 8) {
      Serial.println("8th");
      kick[7] = 1;
    }
    else firstHit = false;
}

void blinkKick(){
  if (currentMillis - previousMillis > beat) {
    digitalWrite(beatLed, HIGH);
    previousMillis = currentMillis;
  }
  if (currentMillis - previousMillis > 50) {
    digitalWrite(beatLed, LOW);
  }
}

