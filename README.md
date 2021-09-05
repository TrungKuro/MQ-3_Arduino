# MQ3 Alcohol Sensor Library
Library sensor MQ-3 for **boards Arduino**
<p align="center"><img src="/readme/mq-3.jpg"/></p>

## Constructors
```
MQ3(uint8_t pin, bool isPower5v=true, float res2=2000);
```
+ pin      : the pin Analog connect
+ isPower5v: the level logic of sensor (default 5v)
+ res2     : the resistor R2 base on Schematic (default 2kΩ)

## Methods

### Need calculate RO before used, wait ~20s
```
void begin();
```

### Get value Raw, unit (mg/L) of BrAC
```
float readRawValueOfAlcohol();
```

### Get value, with other unit like: (ppm) of BrAC, (%) of BAC, (g/mL) of BAC, ...
```
float readAlcoholConcentration(uint8_t unit=PPM);
```
+ unit: convert from (mg/L) to the selected unit
  - PERCENT_BAC (%) of (BAC)
  - G_PER_ML    (g/mL) of (BAC)
  - PPM         (ppm) of (BrAC)

### Convert from (mg/L) to (%) of BAC
```
float convertRawtoBAC(float raw);
```
+ raw: the value Raw, unit (mg/L)

### Convert from (mg/L) to (g/mL) of BAC
```
float convertRawToGramPerMillilitre(float raw);
```
+ raw: the value Raw, unit (mg/L)
### Convert from (mg/L) to (ppm) of BrAC
```
float convertRawToPPM(float raw);
```
+ raw: the value Raw, unit (mg/L)
