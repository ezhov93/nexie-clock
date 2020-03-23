#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QTimer>
#include "display.h"
#include <QMutex>

enum Command { Up, Down, Enter, Enable };

class Model: public QObject
{
  Q_OBJECT

public:
  Model(QObject *parent = nullptr);

signals:
  void displayUpdate(Display &);


public slots:
  void command(Command);
  void update();

private:
  enum class Mode { Work, Time, Alarm, Date, Year };
  friend Mode operator++(Mode &, int);

  QMutex mutex;
  Mode _mode = Mode::Work;
  Display _display;
  QDateTime *_dateTime;
  QTime *_alarm;
  bool _change = false;

  void reset();
};


#endif // MODEL_H
