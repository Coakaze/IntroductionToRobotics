const int swPin = 9;
const int xPin = A0;
const int yPin = A1;
int xValue = 0;
int yValue = 0;
bool buttonState = LOW;
bool lastButtonState = LOW;
bool joyMove = false;

bool dotBlink = true;

const int dataPin = 12; //DS
const int latchPin = 11;  //STCP
const int clockPin = 10;  //SHCP

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const int segmentDigits[] {
  segD1, segD2, segD3, segD4
};

const int segmentsCount = 4;

bool pressed = 0;
int currentDisplay = 1;
int displayArray[5] = {0, 0, 0, 0};

const int minThreshold = 200;
const int maxThreshold = 800;

int digitArray[17] = {
//A B C D E F G DP 
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110,  // F
  B00000001  // DP
  };

void writeReg(int digit) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  digitalWrite(latchPin, HIGH);
}

void writeNumber() {
  int displayNo = 0;
  while (displayNo <= 3) {
    int lastDigit = displayArray[displayNo];
    showDigit(displayNo);
    if (displayNo == currentDisplay) {
      writeReg(digitArray[lastDigit] + 1);
    }
    else {
      writeReg(digitArray[lastDigit]);
    }
    displayNo++;
    delay(5);
  }
}

void showDigit(int digitNumber) {
  for (int i = 0; i < segmentsCount; i++) {
    digitalWrite(segmentDigits[i], HIGH);
  }
  digitalWrite(segmentDigits[digitNumber], LOW);
}

void setup ()
{
  pinMode(swPin, INPUT_PULLUP);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  for (int i = 0; i < segmentsCount; i++) {
    pinMode(segmentDigits[i], OUTPUT);
    digitalWrite(segmentDigits[i], LOW);
  }
  Serial.begin(9600);
}

void loop()
{
  int valueX = analogRead(xPin);
  int valueY = analogRead(yPin);
  int valueSw = digitalRead(swPin);
  buttonState = !digitalRead(swPin);
  writeNumber();
  
  if (buttonState != lastButtonState && buttonState == HIGH) {
    pressed = !pressed;
  }
  
  Serial.println(pressed);
  if (pressed == 0) {  //inainte sa apasam pe buton
    dotBlink = true;
    if (valueY > maxThreshold && joyMove == false) {
      joyMove = true;
      currentDisplay--;
    }
    if (valueY < minThreshold && joyMove == false) {
      joyMove = true;
      currentDisplay++;
    }
    if (currentDisplay > 3) {
      currentDisplay = 0;
    }
    if (currentDisplay < 0) {
      currentDisplay = 3;
    }
    if (valueY > minThreshold && valueY < maxThreshold) {
      joyMove = false;
    }
  }
  else {  //dupa ce am dat lock-in
    dotBlink = false;
    if (valueX > maxThreshold && joyMove == false) {
      joyMove = true;
      displayArray[currentDisplay]++; 
    }
    if (valueX < minThreshold && joyMove == false) {
      joyMove = true;
      displayArray[currentDisplay]--;
    }
    if (displayArray[currentDisplay] < 0) {
      displayArray[currentDisplay] = 9;
    }
    if (displayArray[currentDisplay] > 9) {
      displayArray[currentDisplay] = 0;
    }
    if (valueX > minThreshold && valueX < maxThreshold) {
      joyMove = false;
    }
  }
}
