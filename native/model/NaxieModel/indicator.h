#ifndef INDICATOR_H
#define INDICATOR_H

#include "softtimer.h"
#include <QLCDNumber>

class Indicator
{
public:
  enum Effect {
    EffectNone,
    EffectFading,
    EffectEnumValues,
    EffectEnumCathode
  };
  Indicator(QLCDNumber*);
  void setValue(const int value);
  int value() const { return _value; }
  void burn();
  void setEffect(const Effect);
  void setBright(const int);
  int bright() const;
  Effect effect() const;
  void update();

private:
  enum Burn {
    BurnTimeMs = 10,
    BurnLoops = 3,
    BurnPeriodMin = 15
  };
  enum FlipTime { //ms
    FlipNone = 0,
    FlipFading = 130,
    FlipEnumValues = 50,
    FlipEnumCathode = 40
  };

  int _value = 0;
  int _lastValue = 0;
  int _bright = 0;
  Effect _effect = EffectNone;
  FlipTime _flipTime = FlipNone;
  bool _flipInit = false;
  SoftTimer timer;
  void write(int);

  QLCDNumber *_ui;
};

#endif // INDICATOR_H
