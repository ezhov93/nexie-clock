#include "softtimer.h"

SoftTimer::SoftTimer(int interval)
{
  _timer = _obj->millis();
  _isActive = false;
  _singleShot = false;
  setInterval(interval);
  _obj = &SoftTimerInstatnce::Instance();
}

int SoftTimer::interval() const {
  return _interval;
}

bool SoftTimer::isActive() const {
  return _isActive;
}

bool SoftTimer::isSingleShot() const {
  return _singleShot;
}

bool SoftTimer::isReady() {
  bool temp = _isReady;
  _isReady = false;
  return temp;
}

void SoftTimer::setSingleShot(bool singleShot) {
  _singleShot = singleShot;
}

void SoftTimer::setInterval(int interval) {
  if (interval == 0) {
    pause();
    reset();

  }
  else _interval = interval;
}

void SoftTimer::start() {
  start(_interval);
}

void SoftTimer::start(int interval) {
  _isActive = true;
  setInterval(interval);
  _timer = _obj->millis();
}

void SoftTimer::pause() {
  _isActive = false;
}

void SoftTimer::resume() {
  _isActive = false;
}

void SoftTimer::reset() {
  _timer = _obj->millis();
  _isReady = false;
}

void SoftTimer::update() {
  if (!_isActive)
    return;
  else  {
    if (_obj->millis() - _timer >= _interval) {
      _isReady = true;
      _timer = _obj->millis();
      if (_singleShot)
        _isActive = false;
    }
  }
}
