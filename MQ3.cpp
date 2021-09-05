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
 *          The value Resistance R2 of sensor (default 2KOhm)
 */
MQ3::MQ3(uint8_t pin, bool isPower5v, float res2)
{
  _pin = pin;
  _isPower5v = isPower5v;
  _res2 = res2;
}

/////////////////////////////////////////////////////////////////////

/*!
 *  @brief  It will delay ~20s to heat probe sensor to ready
 *          Then calculate value RO based on RS
 */
void MQ3::begin()
{
  delay(19000);
  _resO=0;

  uint8_t count=10;
  uint8_t i=count;
  while (i--)
  {
    _resO += (MQ3::calculateRS()/AIR); // Calculate the average of RO (RO = RS/60)
    delay(100);
  }
  _resO /= (float)count;
}

/*!
 *  @brief  Read Alcohol Concentration
 *  @param  unit
 *          The unit (%) of (BAC)
 *          The unit (g/mL) of (BAC)
 *          The unit default (ppm) of (BrAC)
 */
float MQ3::readAlcoholConcentration(uint8_t unit)
{
  switch (unit)
  {
    case PERCENT_BAC: return MQ3::convertRawToBAC(MQ3::readRawValueOfAlcohol());
    case G_PER_ML:    return MQ3::convertRawToGramPerMillilitre(MQ3::readRawValueOfAlcohol());
    case PPM:         return MQ3::convertRawToPPM(MQ3::readRawValueOfAlcohol());
  }
}

/*!
 *  @brief  Calculate the concentration of alcohol is present in Air, unit (mg/L) of (BrAC)
 */
float MQ3::readRawValueOfAlcohol()
{
  return 0.4 * pow(MQ3::calculateRS()/_resO, -1.43068);
}

/////////////////////////////////////////////////////////////////////

/*!
 *  @brief  Convert the value unit (mg/L) of (BrAC) to unit (%) of (BAC)
 *          1 mg/L <=> 0,2% BAC
 */
float MQ3::convertRawToBAC(float raw)
{
  return raw * 0.2;
}

/*!
 *  @brief  Convert the value unit (mg/L) of (BrAC) to unit (g/mL) of (BAC)
 *          1 mg/L <=> 0,002 g/mL
 */
float MQ3::convertRawToGramPerMillilitre(float raw)
{
  return raw * 0.002;
}

/*!
 *  @brief  Convert the value unit (mg/L) of (BrAC) to unit (ppm) of (BrAC)
 *          1 mg/L <=> 500 ppm
 */
float convertRawToPPM(float raw)
{
  return raw * 500.0;
}

/////////////////////////////////////////////////////////////////////

/*!
 *  @brief  Calculate value RS based on R2 and level Logic with the value Analog voltage of sensor
 */
float MQ3::calculateRS()
{
  float sensorValue = analogRead(_pin);
  float sensorVolt = sensorValue * (_isPower5v?5.0:3.3) / (_isPower5v?1024.0:675.84);
  float RS = (_isPower5v?5.0:3.3) * _res2 / sensorVolt - _res2;

  return RS;
}
