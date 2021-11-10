const int antennaPin = A1;
const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int pinDP = 9;
const int buzzerPin = 11;
int buzzerTone = 1000;
const int duration = 1000;

const int noOfDigits = 10;
const int readings = 50;
bool state = HIGH;
bool dpState;
int index = 0;
int totalReadings = 0;
int average = 0;

const int segSize = 8;
int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

int counter = 0;

bool digitMatrix[noOfDigits][segSize - 1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void setup() {
  pinMode(antennaPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  Serial.begin(9600);
}

void displayNumber(byte digit, bool decimalPoint) {
  for (int i = 0; i < segSize - 1; i++) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
  digitalWrite(pinDP, decimalPoint);
}

void loop() {
  for (int i = 0; i < readings; i++) {
    int val = analogRead(antennaPin);
    average += val;
  }
  int number = 0;
  number = average / readings;
  average = 0;
  number = constrain(number, 1, 100);
  number = map(number, 1, 100, 0, 9);
  displayNumber(number, LOW);
  Serial.println(number);
  if (number == 0) {
    noTone(buzzerPin);
  }
  else {
    tone(buzzerPin, number);
  }
  delay(500);
}
