#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "character.h"
#include "enemy.h"

class Cell;
class Character;

class Player: public Character {
	public:
	Player(std::string name);
	Player(std::string name, Cell *curPosn);
	int getMaxHp();
	void setPosn(Cell *c);
	void attack(Character &other);
	~Player();
};

#endif
