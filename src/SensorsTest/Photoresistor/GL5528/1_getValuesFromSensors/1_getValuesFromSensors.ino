
const int leftSensorPin = A0;
const int rightSensorPin = A2;

int rightSensorValue = 0;
int leftSensorValue = 0;

int rightSensorMaxValue = 0;
int leftSensorMaxValue = 0;
int rightSensorMinValue = 1024;
int leftSensorMinValue = 1024;

String open, sep, close, arr, mi, ma, outputString = "";

void setup() {
  open = String("(");
  sep = String(",");
  close = String(")");
  arr = String(" --> ");
  mi = String("min(");
  ma = String("max(");

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  rightSensorValue = analogRead(rightSensorPin);
  leftSensorValue = analogRead(leftSensorPin);

  rightSensorMaxValue = max(rightSensorMaxValue, rightSensorValue);
  leftSensorMaxValue = max(leftSensorMaxValue, leftSensorValue);

  rightSensorMinValue = min(rightSensorMinValue, rightSensorValue);
  leftSensorMinValue = min(leftSensorMinValue, leftSensorValue);

  // (#,#) --> min(#,#), max(#,#)
  outputString = open + leftSensorValue + sep + rightSensorValue + close + arr + mi + leftSensorMinValue + sep + rightSensorMinValue + close + sep + ma + leftSensorMaxValue + sep + rightSensorMaxValue + close;
  Serial.println(outputString);

  delay(400);
}
