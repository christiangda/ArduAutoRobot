
const int SensorRightPin = A0;
const int SensorLeftPin = A2;
const int SensorThresholdPin = A4;

const int IndicatorRightPin = 3;
const int IndicatorLeftPin = 2;

int SensorRight = 0;
int SensorLeft = 0;
int SensorDifference = 0;
const int closeness = 60;

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

  int thresold = analogRead(SensorThresholdPin);

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
  OutputThreshold = th + thresold + sep + thresold / 2 + close;

  OutputString = OuputValues + arr + OuputMinMax + arr + OuputDifference + arr + OutputThreshold;

  Serial.println(OutputString);

  delay(400);
}
