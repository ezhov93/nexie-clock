#ifndef SOFTTIMER_H
#define SOFTTIMER_H

#include <chrono>
#include <thread>


class SoftTimerInstatnce
{
public:
  static SoftTimerInstatnce& Instance()
  {
    static SoftTimerInstatnce theSingleInstance;
    return theSingleInstance;
  }
  inline unsigned int millis() const {return _timer; }
  void delay(int ms) const {
    const uint32_t time = millis();
    while (millis()-time < ms);
  }


private:
  SoftTimerInstatnce() {
    std::thread timer([=]() {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      ++_timer;
    });
    timer.detach();
  }
  SoftTimerInstatnce(const SoftTimerInstatnce& root) = delete;
  SoftTimerInstatnce& operator=(const SoftTimerInstatnce&) = delete;
  unsigned int _timer;
};

class SoftTimer
{
public:
  explicit SoftTimer(int interval = 1000);
  int interval() const;
  bool isActive() const;
  bool isReady();
  bool isSingleShot() const;
  void setSingleShot(bool singleShot = false);
  void setInterval(int interval);
  void start();
  void start(int interval);
  void pause();
  void resume();
  void reset();
  void update();

private:
  SoftTimerInstatnce *_obj;
  uint32_t _timer;
  int _interval;
  uint32_t(*time)();
  uint32_t _handler;
  bool _isActive;
  bool _isReady;
  bool _singleShot;
};

#endif // SOFTTIMER_H
