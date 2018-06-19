#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <utility>
#include <sstream>
#include <vector>
class Cell;

class TextDisplay {
  std::vector<std::vector<char>> theDisplay;
  int row;
  int col;
  public:
  TextDisplay(int row, int col, std::string content);
  void notify(Cell &whoNotified);
  ~TextDisplay();
  char getSymbol(int x, int y); // return the symbol of position (x. y)
  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

#endif

