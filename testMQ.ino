#include "MQ3.h"

#define MQ_PIN A0

MQ3 mq(MQ_PIN, false);

void setup()
{
  Serial.begin(9600);
  Serial.println(F("MQ3 test!\n"));
  Serial.println(F("Please wait, the program is calculating RO..."));
  mq.begin();
  Serial.println(F(" Finish\n"));
}

void loop()
{
  Serial.println(F("Alcohol: "));
  mq.readAlcoholConcentration(PPM);
  Serial.println(F(" ppm\n"));

  delay(500);

  Serial.println(F("Alcohol: "));
  mq.readAlcoholConcentration(PERCENT_BAC);
  Serial.println(F("% BAC\n"));

  delay(500);

  Serial.println(F("Alcohol: "));
  mq.readAlcoholConcentration(G_PER_ML);
  Serial.println(F(" g/mL\n"));

  delay(500);
}