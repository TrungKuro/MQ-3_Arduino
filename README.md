# MQ3 Alcohol Sensor Library
Library sensor MQ-3 for **boards Arduino**

## Constructors
```
MQ3(uint8_t pin, bool isPower5v=true, float res2=2000);
```
+ pin       : the pin Analog connect
+ isPower5v : the level logic of sensor (default 5v)
+ res2      : the resistor R2 base on Schematic (default 2kOhm)

## Methods
### Caculate RO before used
```
void begin();
```
### Get value Raw, unit (mg/L)
```
float readRawValueOfAlcohol();
```
### Get value, with other unit like: ppm, BAC, (g/mL), ...
```
float readAlcoholConcentration(uint8_t unit=PPM);
```
+ unit      : Convert from (mg/L) to the selected unit
  - (% BAC)
  - (g/mL)
  - (ppm)
### Convert from (mg/L) to BAC
```
float convertRawtoBAC(float raw);
+ raw       : The value Alcohol concentration, unit (mg/L)
```
### Convert from (mg/L) to (g/mL)
```
float convertRawToGramPerMillilitre(float raw);
```
+ raw       : The value Alcohol concentration, unit (mg/L)
