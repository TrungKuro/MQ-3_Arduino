#include "MQ3.h"

#define MQ_PIN A0

MQ3 mq(MQ_PIN, false);

void setup()
{
  Serial.begin(9600);
  Serial.print(F("MQ3 test!\n"));
  Serial.print(F("Please wait, the program is calculating RO..."));
  mq.begin();
  Serial.print(F("ok\n"));
}

void loop()
{
  Serial.print(F("Alcohol: "));
  mq.readAlcoholConcentration(PPM);
  Serial.print(F(" ppm\n"));

  delay(500);

  Serial.print(F("Alcohol: "));
  mq.readAlcoholConcentration(PERCENT_BAC);
  Serial.print(F("% BAC\n"));

  delay(500);

  Serial.print(F("Alcohol: "));
  mq.readAlcoholConcentration(G_PER_ML);
  Serial.print(F(" g/mL\n"));

  delay(500);
}
