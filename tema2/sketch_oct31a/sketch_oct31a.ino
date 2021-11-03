const int buttonPin = 7;
bool buttonState = LOW;
bool lastButtonState = LOW;

const int redPinCars = 13;
const int yellowPinCars = 12;
const int greenPinCars = 8;
const int redPinPed = 3;
const int greenPinPed = 2;

unsigned int firstPress = 0;

const int buzzerPin = 11;
int buzzerTone = 1000;

const int time_1 = 5000;
const int time_2 = 10000;

bool pressed = 0;
bool firstPhase = 1;
bool secondPhase = 1;

unsigned long lastPeriodStart = 0;
const int onDuration = 300;
const int firstPeriod = 2000;
const int secondPeriod = 500;

unsigned int counter = 0;
const int nTimes = 5;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redPinCars, OUTPUT);
  pinMode(yellowPinCars, OUTPUT);
  pinMode(greenPinCars, OUTPUT);
  pinMode(redPinPed, OUTPUT);
  pinMode(greenPinPed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  bool reading = digitalRead(buttonPin);
  if (pressed == 0) {
    digitalWrite(greenPinCars, HIGH);
    digitalWrite(redPinPed, HIGH);
    digitalWrite(greenPinPed, LOW);
    digitalWrite(redPinCars, LOW);
  }
  if (pressed == 0 && reading != lastButtonState) {
    pressed = 1;
    firstPress = millis();
  }
  if (pressed == 1) {
    if (firstPhase == 1 && millis() - firstPress >= time_1) {
      digitalWrite(yellowPinCars, HIGH);
      digitalWrite(greenPinCars, LOW);
      firstPhase = 0;
      lastPeriodStart = millis() - firstPress + time_1 - firstPeriod;
    }
    if (millis() - firstPress >= time_2) {
      digitalWrite(yellowPinCars, LOW);
      digitalWrite(redPinPed, LOW);
      digitalWrite(redPinCars, HIGH);
      digitalWrite(greenPinPed, HIGH);
      if (counter <= nTimes && millis() - firstPress - lastPeriodStart >= firstPeriod) {
        counter++;
        lastPeriodStart += firstPeriod;
        tone(buzzerPin, 400, onDuration);
      }
      if (counter > nTimes && counter <= nTimes * 2 && millis() - firstPress - lastPeriodStart >= secondPeriod) {
        counter++;
        lastPeriodStart += secondPeriod;
        tone(buzzerPin, 400, onDuration);
      }
      if (counter > 10) {
        pressed = 0;
        firstPhase = 1;
        counter = 0;
      }
    }
  }
}
