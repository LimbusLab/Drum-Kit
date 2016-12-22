const int redLED = 10;
const int whiteLED = 11;
const int blueLED = 12;
const int switchPins[] = {2, 3, 4, 5, 6, 7, 8, 9};

const int speedPot = A1;

const int enterSwitch = A7;

boolean switchStates[] = {false};

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
  if (analogRead(enterSwitch) == 1023) {
    readSwitches();
  }
}

void readSwitches() {
  for (int i = 0; i < sizeof(switchStates); i++) {
    switchStates[i] = digitalRead(switchPins[i]);
    if(switchStates[i] == true){
      Serial.print("b,190,t,1,1,0,1,0,0,1,0,d,0,0,0,0,0,0,1,0,k,0,0,1,0,0,0,1,0");
    }
    //Serial.print("switch pin = ");
    //Serial.println(switchStates[i]);
    delay(500);
  }
}

