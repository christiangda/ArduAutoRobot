
const int SensorRightPin = A0;
const int SensorLeftPin = A2;
const int SensorThresholdPin = A4;

const int IndicatorRightPin = 3;
const int IndicatorLeftPin = 2;

int SensorRight = 0;
int SensorLeft = 0;
int SensorDifference = 0;
const int Closeness = 50;

int SensorRightMax = 0;
int SensorLeftMax = 0;
int SensorRightMin = 1024;
int SensorLeftMin = 1024;

// Strings formater
const String open = "(";
const String sep = ",";
const String close = ")";
const String arr = " --> ";
const String mi = "min(";
const String ma = "max(";
const String diff = "difference(";
const String th = "threshold(";

String OuputValues = "";
String OuputMinMax = "";
String OuputDifference = "";
String OutputThreshold = "";
String OutputMoveTo = "";
String OutputString = "";

void setup() {
  pinMode(IndicatorLeftPin, OUTPUT);
  pinMode(IndicatorRightPin, OUTPUT);

  pinMode(SensorThresholdPin, INPUT);
  pinMode(SensorLeftPin, INPUT);
  pinMode(SensorRightPin, INPUT);

  Serial.begin(9600);
}

void loop() {

  int Threshold = analogRead(SensorThresholdPin);

  // put your main code here, to run repeatedly:
  SensorRight = analogRead(SensorRightPin);
  SensorLeft = analogRead(SensorLeftPin);

  SensorDifference = abs(SensorRight - SensorLeft);

  SensorRightMax = max(SensorRightMax, SensorRight);
  SensorLeftMax = max(SensorLeftMax, SensorLeft);

  SensorRightMin = min(SensorRightMin, SensorRight);
  SensorLeftMin = min(SensorLeftMin, SensorLeft);

  // (#,#) --> min(#,#), max(#,#) --> thresold(#,#)
  OuputValues = open + SensorLeft + sep + SensorRight + close;
  OuputMinMax = mi + SensorLeftMin + sep + SensorRightMin + close + sep + ma + SensorLeftMax + sep + SensorRightMax + close;
  OuputDifference = diff + SensorDifference + close;
  OutputThreshold = th + Threshold + sep + Threshold / 2 + close;


  Serial.println(OutputString);
  delay(400);

  // Move Forward
  if (
    SensorLeft <= Threshold &&
    SensorRight <= Threshold &&
    SensorLeft >= Threshold / 2 &&
    SensorRight >= Threshold / 2 &&
    SensorDifference <= Closeness
  )
  {
    OutputMoveTo = "Forward";
    digitalWrite(IndicatorLeftPin, HIGH);
    digitalWrite(IndicatorRightPin, HIGH);
    delay(10);
  }
  //Move Stop
  else if (
    SensorLeft >= Threshold &&
    SensorRight >= Threshold &&
    SensorDifference <= Closeness
  )
  {
    OutputMoveTo = "Stop";
    digitalWrite(IndicatorLeftPin, LOW);
    digitalWrite(IndicatorRightPin, LOW);
    delay(10);
  }
  //Move Right
  else if (
    SensorLeft >= Threshold / 2 &&
    SensorRight >= Threshold / 2 &&
    SensorLeft < SensorRight
  )
  {
    OutputMoveTo = "Right";
    digitalWrite(IndicatorLeftPin, HIGH);
    digitalWrite(IndicatorRightPin, LOW);
    delay(10);
  }
  //Move Left
  else if (
    SensorLeft >= Threshold / 2 &&
    SensorRight >= Threshold / 2 &&
    SensorLeft > SensorRight
  )
  {
    OutputMoveTo = "Left";
    digitalWrite(IndicatorLeftPin, LOW);
    digitalWrite(IndicatorRightPin, HIGH);
    delay(10);
  }
  //Move Loss, move arround
  else if (
    SensorLeft < Threshold / 2 &&
    SensorRight < Threshold / 2
  )
  {
    OutputMoveTo = "Loss";
    for (int i = 0; i < 10; i++) {
      digitalWrite(IndicatorLeftPin, LOW);
      digitalWrite(IndicatorRightPin, HIGH);
      delay(70);
      digitalWrite(IndicatorLeftPin, HIGH);
      digitalWrite(IndicatorRightPin, HIGH);
      delay(70);
      digitalWrite(IndicatorLeftPin, HIGH);
      digitalWrite(IndicatorRightPin, LOW);
      delay(70);
      digitalWrite(IndicatorLeftPin, LOW);
      digitalWrite(IndicatorRightPin, LOW);
      delay(70);
    }
  }
  OutputString = OuputValues + arr + OuputMinMax + arr + OuputDifference + arr + OutputThreshold + arr + OutputMoveTo;
}

