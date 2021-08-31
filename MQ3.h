/*!
 *  @file MQ3.cpp
 *
 *  Library Sensor MQ3 use with boards Arduino
 *  Function tests levels of alcohol in the air
 *
 *  @section author Author
 *
 *  Written by TrungKuro
 *
 *  @section license License
 *
 *  Hshop license, all text above must be included in any redistribution
 */

#ifndef MQ3_H
#define MQ3_H

#include <Arduino.h>

#define AIR 60.0 // The RS/R0 ratio is a constant 60 in "clean air"

/* Define types Unit of MQ-3 */
#define PERCENT_BAC 1 // Blood alcohol level (BAC - %)
#define G_PER_ML 2    // Gram Per Millilitre (g/mL)
#define PPM 3         // Parts Per Million (ppm)

class MQ3
{
public:
  MQ3(uint8_t pin, bool isPower5v=true, float res2=2000);

  void begin();
  float readAlcoholConcentration(uint8_t unit=PPM);
  float readRawValueOfAlcohol(); // Unit (mg/L), based on ratio RS/RO

  float convertRawtoBAC(float raw);
  float convertRawToGramPerMillilitre(float raw);

private:
  uint8_t _pin;
  float _res2, _resO;
  bool _isPower5v;

  float calculateRS();
};

#endif
