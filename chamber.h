#ifndef __CHAMBER_H__
#define __CHAMBER_H__
#include <iostream>
#include <vector>
#include "cell.h"
#include "tile.h"
#include "enemy.h"
#include "floor.h"

class Chamber {
      int total;
      int row;
      int col;
      int num;
      int globStarX;
      int globStarY;
      std::vector<std::vector<Cell *>> Tiles;
      std::vector<Enemy *> Enemies;
      TextDisplay *td;

    public:
      Chamber(int n, TextDisplay *td, Player * pc, Cell *door1, Cell *door2, Cell *door3 = nullptr, Cell *door4 = nullptr);
      ~Chamber();
      void addEm(Enemy *em);
      void moveEm();
      void enemiesActed(bool val);
      void enemiesAttack();
	  void setMarchantMad();
      int getNum();
      int getRow();
      int getCol();
      int getGlobStarX();
      int getGlobStarY();
      int getTotal();
      Cell *getCell(int row, int col);
      void setCell(int row, int col, Cell *cell);
      void resetAct();
};

#endif
