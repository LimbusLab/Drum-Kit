/*
   Format is in b,500,t,0,1,0,1,d,1,0,1,0,k,1,1,1,1
*/


const int tamPin = 10;
const int drumPin = 9;
const int kickPin = 11;

const int measure = 4;

const int delayTime = 50;

int tam[measure] = {0,0,0,0};
int drum[measure] = {0,0,0,0};
int kick[measure] = {0,0,0,0};
int beat = 200;

void setup() {
  Serial.begin(115200);
  pinMode(tamPin, OUTPUT);
  pinMode(drumPin, OUTPUT);
  pinMode(kickPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    if (Serial.find('b')) {
      beat = Serial.parseInt();
      //Serial.println(beat);
    }
    if (Serial.find('t')) {
      for (int i = 0; i < measure; i++) {
        tam[i] = Serial.parseInt();
        //Serial.println(tam[i]);
      }
    }
    if (Serial.find('d')) {
      for (int i = 0; i < measure; i++) {
        drum[i] = Serial.parseInt();
        //Serial.println(drum[i]);
      }
    }
    if (Serial.find('k')) {
      for (int i = 0; i < measure; i++) {
        kick[i] = Serial.parseInt();
        //Serial.println(drum[i]);
      }
    }

  }
  for (int j = 0 ; j < measure; j++) {
    turnOn(tam[j], drum[j], kick[j]);
    delay(beat);
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

