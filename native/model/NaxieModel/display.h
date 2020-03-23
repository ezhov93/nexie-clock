#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
public:
  Display() = default;
  void add();
  void dim();
  void nextPos();
  void resetPos();
  int pos() const { return _pos; }
  void clear();
  void setDigitAt(int pos, int);
  int valueAt(int pos);
  void setDigit(int left, int right);
  void digit(int &left, int &right);
  void setDot(bool);
  bool isDotted();

private:
  static constexpr int _numbersOfValues = 4;
  int _pos = 0;
  int _values[_numbersOfValues];
  bool _dot = false;

};

#endif // DISPLAY_H
