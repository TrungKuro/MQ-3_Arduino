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

#include "MQ3.h"

/*!
 *  @brief  Instantiates a new MQ3 class
 *  @param  pin
 *          Pin number that sensor is connected (note: use pin Analog)
 *  @param  isPower5v
 *          The sensor use logic 3.3v or 5v (default 5v)
 *  @param  res2
 *          The value Resistance R2 of sensor (default 1KOhm)
 */
MQ3::MQ3(uint8_t pin, bool isPower5v, uint32_t res2)
{
  _pin = pin;
  _isPower5v = isPower5v;
  _res2 = res2;
}

/////////////////////////////////////////////////////////////////////

/*!
 *  @brief  It will delay ~15s to heat probe sensor to ready
 *          Then calculate value RO based on RS
 */
void MQ3::begin()
{
  delay(10000);
  _resO=0;

  uint8_t count=5;
  uint8_t i=count;
  while (i--)
  {
    _resO += (MQ3::calculateRS()/AIR); // RS/RO = 60 => RS/60 = RO
    delay(1000);
  }
  _resO /= count;
}

float MQ3::readAlcoholConcentration(uint8_t unit)
{
  switch (unit)
  {
    case PERCENT_BAC: MQ3::convertRawtoBAC(MQ3::readRawValueOfAlcohol()); break;
    case G_PER_ML:    MQ3::convertRawToGramPerMillilitre(MQ3::readRawValueOfAlcohol()); break;
    case PPM:         MQ3::readRawValueOfAlcohol();
  }
}

/*!
 *  @brief  Calculate the concentration of alcohol is present in Air, unit (mg/L)
 *          It using the function pow() for Exponent with the value return "double"
 */
float MQ3::readRawValueOfAlcohol()
{
  return 0.4 * pow(MQ3::calculateRS()/_resO, -1.43068);
}

/////////////////////////////////////////////////////////////////////

/*!
 *  @brief  Convert the value unit (mg/L) to unit BAC (%)
 *          1 mg/L <=> 0,0001% BAC
 */
float MQ3::convertRawtoBAC(float raw)
{
  return raw * 0.0001;
}

/*!
 *  @brief  Convert the value unit (mg/L) to unit (g/mL)
 *          1 mg/L <=> 0,000001 (g/mL)
 */
float MQ3::convertRawToGramPerMillilitre(float raw)
{
  return raw * 0.000001;
}

/*
 *  The unit (mg/L) is also unit (ppm)
 *  1 mg/L <=> 1 (ppm)
 */
// float MQ3::convertRawToPPM(float raw)
// {
//   return raw;
// }

/////////////////////////////////////////////////////////////////////

/*!
 *  @brief  Calculate value RS based on R2 and level Logic with the value Analog voltage of sensor
 */
double MQ3::calculateRS()
{
  uint16_t sensorValue = analogRead(_pin);
  double sensorVolt = sensorValue * (_isPower5v?5.0:3.3) / 1024.0;
  double RS = (_isPower5v?5.0:3.3) * _res2 / sensorVolt - _res2;

  return RS;
}
