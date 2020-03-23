#include "display.h"
#include <string.h>
#include <cmath>

void Display::add() {
  int &value = _values[_pos];
  if(value < 9)
    ++value;
  else
    value = 0;
}

void Display::dim() {
  int &value = _values[_pos];
  if(value > 0)
    --value;
  else
    value = 9;
}

void Display::nextPos() {
  if(++_pos > 3) _pos = 0;
}

void Display::resetPos() { _pos=0; }

void Display::clear() {
  static size_t size =  _numbersOfValues*sizeof(int);
  memset(_values,0, size);
  _pos = 0;
}

void  Display::setValueAt(int pos, int value) {
  if (pos<_numbersOfValues)
    _values[pos] = value;
}

int Display::valueAt(int pos) {
  if (pos<_numbersOfValues)
    return _values[pos];
  else return 0;
}

void Display::setValue(int left, int right)
{
  if (left>99 || right>99)
    return;
  _values[0] = static_cast<int>(floor(left/10));
  _values[1] = left%10;
  _values[2] = static_cast<int>(floor(right/10));
  _values[3] = right%10;
}

void  Display::setDot(bool enable) {
  _dot = enable;

}

bool  Display::isDotted() {
  return _dot;
}
