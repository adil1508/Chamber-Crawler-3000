#include "enemy.h"

using namespace std;

void Enemy::attack(Character &other) {
	srand(time(NULL));

	int miss = rand() % 100;
	int dmg = 0;
	if(miss < 50) {
		dmg = 0;
	} else {
		dmg = ceil((100.0 / (100 + other.getDef())) * atk);
	}

	// case for elf, second attack
	if(name == "elf" && other.getName() != "drow"){
		miss = rand() % 100;
		if(miss > 50)
			dmg += dmg;
	}

	int newHp = 0;

	if(name == "orcs" && other.getName() == "goblin") { // orcs VS goblin
		newHp = other.getHp() - (1.5 * dmg);
	} else {	// all other battles
		newHp = other.getHp() - dmg;
	}

	if (newHp < 0){
		other.setHp(0);
	} else {
		other.setHp(newHp);
	}

		acted = true;
}

void Enemy::setPosn(Cell *c){
	curPosn = c;
}

Cell *Enemy::getHoard() const {
	return hoard;
}

void Enemy::setHoard(Cell *hoard){
	this->hoard = hoard;
}

void Enemy::setHoardMovable(bool move){
	if (hoard){
		hoard->setMovable(move);
		hoard->setOccupied(false);
	}
}

 Enemy::Enemy(string name, Cell *curPosn):Character{name,curPosn}{
	if (name == "human") {
		hostile = true;
	} else if (name == "dwarf") {
		hostile = true;
	} else if (name == "elf") {
		hostile = true;
	} else if (name == "orcs") {
		hostile = true;
	} else if (name == "merchant") {
		hostile = false;
	} else if (name == "dragon") {
		hostile = true;
	} else if (name == "halfling") {
		hostile = true;
	}
}

Enemy::Enemy(std::string name, Cell *curPosn, Cell *hoards):Character{name,curPosn}, hoard{hoard}{
	if (name == "human") {
		hostile = true;
	} else if (name == "dwarf") {
		hostile = true;
	} else if (name == "elf") {
		hostile = true;
	} else if (name == "orcs") {
		hostile = true;
	} else if (name == "merchant") {
		hostile = false;
	} else if (name == "dragon") {
		this->hoard = hoard;
		hostile = true;
	} else if (name == "halfling") {
		hostile = true;
	}
}

Enemy::~Enemy(){}
