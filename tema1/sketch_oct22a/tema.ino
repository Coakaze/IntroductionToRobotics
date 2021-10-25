const int bluePin = 11;
const int greenPin = 10;
const int redPin = 6;

const int potPinBlue = A0;
const int potPinGreen = A1;
const int potPinRed = A2;

int potValueBlue = 0;
int potValueGreen = 0;
int potValueRed = 0;

int brightnessBlue = 0;
int brightnessGreen = 0;
int brightnessRed = 0;

void setup() {
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(potPinBlue, INPUT);
  pinMode(potPinGreen, INPUT);
  pinMode(potPinRed, INPUT);
  Serial.begin(9600);
}

void loop() {
  potValueBlue = analogRead(potPinBlue);
  potValueGreen = analogRead(potPinGreen);
  potValueRed = analogRead(potPinRed);
  
  brightnessBlue = map(potValueBlue, 0, 1023, 0, 255);
  brightnessGreen = map(potValueGreen, 0, 1023, 0, 255);
  brightnessRed = map(potValueRed, 0, 1023, 0, 255);
  
  analogWrite(bluePin, brightnessBlue);
  analogWrite(greenPin, brightnessGreen);
  analogWrite(redPin, brightnessRed);
}
