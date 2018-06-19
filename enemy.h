#ifndef _ENEMY_H_
#define _ENEMY_H_
#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "character.h"

class Enemy : public Character {
	Cell *hoard = nullptr;
	public:
	Cell *getHoard() const override;
	void setPosn(Cell *c);
	void setHoard(Cell *hoard) override;
	void setHoardMovable(bool move) override;
	void attack(Character &other) override ;
	Enemy(std::string name, Cell *curPosn);
	// 3 param ctor. specifically for dragon
	Enemy(std::string name, Cell *curPosn, Cell *hoard);
	~Enemy();
};
#endif
