#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include <string>
#include "cell.h"

class Cell;

class Character {

	protected:
	std::string name;
	Cell *curPosn;
	int maxHp;
	int hp;
	int atk;
	int def;
	int gold;
	bool acted = false;
	bool hostile = true;

	public:
	virtual void attack(Character &other);

	// getters
	Cell *getPosn() const;
	int getMaxHp() const;
	int getHp() const;
	int getAtk() const;
	int getDef() const;
	int getGold() const;
	std::string getName() const;
	bool getActed() const;
	bool getHostility() const;
	bool isDead() const;
	virtual Cell *getHoard() const;

	//setters
	void setHostility(bool h);
	void setHp(int h);
	void setAtk(int a);
	void setDef(int d);
	void setGold(int g);
	void setActed(bool a);
	void setName(std::string name);
	virtual void setHoard(Cell *hoard);
	virtual void setHoardMovable(bool move);

	// 2 param ctor
	Character(std::string name, Cell *curPosn);
	virtual ~Character() = 0;

};
#endif
