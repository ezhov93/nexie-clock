#include "model.h"
#include <QTime>
#include <QDebug>
#include <windows.h>
#include <QtConcurrent/QtConcurrentRun>
#include <cmath>

Model::Model(QObject *parent):
  QObject(parent),
  _dateTime(new QDateTime), _alarm(new QTime)
{
  reset();
  QtConcurrent::run([&](){
    while(true) {
      QThread::sleep(1000);
      mutex.lock();
      *_dateTime = _dateTime->addSecs(60);
      mutex.unlock();
    }
  });
}

Model::Mode operator++(Model::Mode &m, int)
{
  using IntType = typename std::underlying_type<Model::Mode>::type;
  if ( m == Model::Mode::Year)
    m = Model::Mode::Work;
  else
    m = static_cast<Model::Mode>( static_cast<IntType>(m) + 1 );
  return m;
}

void Model::command(Command cmd) {
  switch (cmd) {
  case Up:
    _display.add();
    break;
  case Down:
    _display.dim();
    break;
  case Enter:
    if (_display.pos() >= 3 || _mode == Mode::Work) {
      _display.resetPos();
      _mode++;
    }
    else _display.nextPos();
    break;
  case Enable:
    reset();
    break;
  }
  mutex.lock();
  _change = true;
  mutex.unlock();
}

void Model::displayUpdate(Display &display) {
  bool exit = false;
  while (!exit) {
    Mode mode = _mode;
    if (mode == Mode::Work) {
      Sleep(1000);
      _display.resetPos();
      const QTime time = _dateTime->time();
      const int hours = time.hour();
      const int minutes = time.minute();
      _display.setValueAt(0,hours/10);
      _display.setValueAt(1,hours%10);
      _display.setValueAt(2,minutes/10);
      _display.setValueAt(3,minutes%10);
    }
    else {
      Sleep(25);
      if (!_change)
        continue;
      if (mode == Mode::Time) {
        qDebug()<<"Mode: Time";
        int hours = _display.toQString().left(2).toInt();
        int minutes = _display.toQString().right(2).toInt();
        _dateTime->setHMS(hours, minutes, 0);

      }
      else if (mode == Mode::Alarm) {
        qDebug()<<"Mode: Alarm";
        int hours = _display.toQString().left(2).toInt();
        int minutes = _display.toQString().right(2).toInt();
        _alarm->setHMS(hours, minutes, 0);

      }
      else if (mode == Mode::Date) {
        qDebug()<<"Mode: Date";
        QDate tmp = *_date;
        int day = _display.toQString().left(2).toInt();
        int month = _display.toQString().right(2).toInt();
        int year = tmp.year();
        _date->setDate(year, month, day);
      }
      else if (mode == Mode::Year) {
        qDebug()<<"Mode: Year";
        QDate tmp = *_date;
        int month = tmp.month();
        int day = tmp.day();
        int year = _display.toQString().toInt();
        _date->setDate(year, month, day);
      }
      else {
        qDebug()<<"Mode: ERROR";
        exit = true;
      }
    }
    emit displayUpdate(_display);
    mutex.lock();
    _change = false;
    mutex.unlock();
  }
}


void Model::reset() {
  *_time = QTime(0,0,0);
  *_alarm = QTime(0,0,0);
  *_date = QDate(2019,1,1);
  _display.clear();
}
