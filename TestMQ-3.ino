#include "MQ3.h"

#define MQ_PIN A0

MQ3 mq(MQ_PIN, false, 1000); // Here I use sensor have logic 3.3v (isPower5v=false) and R2=1kOhm (default 2kOhm)

void setup()
{
  Serial.begin(9600);
  Serial.print(F("MQ3 test!\n"));
  Serial.print(F("Please wait for the sensor probe to warm up (~20s)\nThe program is calculating the value of RO..."));
  mq.begin();
  Serial.print(F("ready\n"));
}

void loop()
{
  float alcohol = mq.readRawValueOfAlcohol(); // Unit (mg/L) of (BrAC)
  Serial.print(F("Level Alcohol: "));
  Serial.print(alcohol, 2); Serial.print(F(" mg/L ; "));
  Serial.print(mq.convertRawToPPM(alcohol), 0); Serial.print(F("ppm ; "));
  Serial.print(mq.convertRawToBAC(alcohol), 2); Serial.print(F("% BAC ; "));
  Serial.print(mq.convertRawToGramPerMillilitre(alcohol), 4); Serial.print(F(" g/mL\n"));

  delay(1000);
}
