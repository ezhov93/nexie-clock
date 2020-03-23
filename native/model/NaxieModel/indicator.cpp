#include "indicator.h"

#include <windows.h>
inline static void delay(int x) {
  auto &timer = SoftTimerInstatnce::Instance();
  timer.delay(x);
}

Indicator::Indicator(QLCDNumber *ui)
{
  _ui = ui;
  timer.setInterval(0);
}

void Indicator::write(int value) { _ui->display(value); }

void Indicator::setValue(const int value) {
  if (value == _value)
    return;
  if ( value>=0 && value<=9) {
    _lastValue = _value;
    _value = value;
  }
}

void Indicator::burn()
{
  for (int cnt = 0; cnt < BurnLoops; ++cnt) {
    for (int val = 0; val < 10; ++val) {
      write(val);
      delay(BurnTimeMs);
    }
  }
}

void Indicator::setEffect(const Effect effect)
{
  _effect = effect;
  switch (_effect) {
  case (EffectNone):
    _flipTime = FlipNone;
    break;
  case (EffectFading):
    _flipTime = FlipFading;
    break;
  case (EffectEnumValues):
    _flipTime =FlipEnumValues;
    break;
  case (EffectEnumCathode):
    _flipTime = FlipEnumCathode;
    break;
  }
}

void Indicator::update() {
  switch (_effect) {
  case EffectNone:
      write(value());
    break;
  case EffectFading:
    if (!_flipInit) {
      _flipInit = true;

    }
    break;
  case EffectEnumValues:

    break;
  case EffectEnumCathode:

    break;
  }
}
