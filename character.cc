#include "character.h"

using namespace std;

// Getters

bool Character::isDead() const {
	if(hp <= 0) {
		return true;
	} else {
		return false;
	}
}

Cell *Character::getHoard() const {
	return nullptr;
}

Cell *Character::getPosn() const {
	return curPosn;
}

int Character::getMaxHp() const {
	return maxHp;
}

int Character::getHp() const {
	return hp;
}

int Character::getAtk() const {
	return atk;
}

int Character::getDef() const {
	return def;
}

int Character::getGold() const {
	return gold;
}

bool Character::getActed() const {
	return acted;
}

string Character::getName() const {
	return name;
}

bool Character::getHostility() const {
	return hostile;
}

// Setters
void Character::setHoard(Cell *hoard) {

}

void Character::setHoardMovable(bool move){

}

void Character::setHostility(bool h){
	hostile = h;
}

void Character::setGold(int g) {
	gold = g;
}
void Character::setHp(int h) {
	hp = h;
}
void Character::setAtk(int a) {
	atk = a;
}
void Character::setDef(int d) {
	def = d;
}

void Character::setActed(bool a){
	acted = a;
}

void Character::setName(string name){
	this->name = name;
}

void Character::attack(Character &other){

}

Character::Character(string name, Cell *curPosn)
: name{name}, curPosn{curPosn}{
	if(name == "shade") {
		maxHp = 125;
		hp = 125;
		atk = 25;
		def = 25;
		gold = 0;
	} else if (name == "drow") {
		maxHp = 150;
		hp = 150;
		atk = 25;
		def = 15;
		gold = 0;
	} else if (name == "vampire") {
		maxHp = 2147483000;
		hp = 50;
		atk = 25;
		def = 25;
		gold = 0;
	} else if (name == "troll") {
		maxHp = 120;
		hp = 120;
		atk = 25;
		def = 15;
		gold = 0;
	} else if (name == "goblin") {
		maxHp = 110;
		hp = 110;
		atk = 15;
		def = 20;
		gold = 0;
	} else if (name == "human") {
		maxHp = 140;
		hp = 140;
		atk = 20;
		def = 20;
		gold = 4;
	} else if (name == "dwarf") {
		maxHp = 100;
		hp = 100;
		atk = 20;
		def = 30;
		gold = 0;
	} else if (name == "elf") {
		maxHp = 140;
		hp = 140;
		atk = 30;
		def = 10;
		gold = 0;
	} else if (name == "orcs") {
		maxHp = 180;
		hp = 180;
		atk = 30;
		def = 25;
		gold = 0;
	} else if (name == "merchant") {
		maxHp = 30;
		hp = 30;
		atk = 70;
		def = 5;
		gold = 4;
	} else if (name == "dragon") {
		maxHp = 150;
		hp = 150;
		atk = 20;
		def = 20;
		gold = 0;
	} else if (name == "halfling") {
		maxHp = 100;
		hp = 100;
		atk = 15;
		def = 20;
		gold = 0;
	}
}

Character::~Character(){

}
