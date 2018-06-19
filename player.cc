#include "player.h"
using namespace std;
class Character;

Player::Player(string name):Character{name, nullptr}{}
Player::Player(string name, Cell *curPosn): Character{name,curPosn}{}

void Player::attack(Character &other) {
	srand(time(NULL));
	int dmg = ceil((100.0 / (100 + other.getDef())) * atk);
	// special case for vampire
	if(name == "vampire") hp += 5;
	if(name != "drow" && other.getName() == "elf") {
		other.setHp(other.getHp() -2 * dmg);
		if(other.isDead()){
			int amount = rand() %100;
			if(amount < 50) {
				gold += 1;
			} else {
				gold += 2;
			}
		}
	} else if(other.getName() == "human") {
		other.setHp(other.getHp() - dmg);
		if(other.isDead()){
			gold += other.getGold();
		}
	} else if(other.getName() == "halfling") {
		int miss = rand() %100;
		if(miss < 50) dmg = 0;
		other.setHp(other.getHp() - dmg);
		if(other.isDead()){
			int amount = rand() %100;
			if(amount < 50) {
				gold += 1;
			} else {
				gold += 2;
			}
		}
	} else if(other.getName() == "merchant") {
		other.setHostility(true);
		other.setHp(other.getHp() - dmg);
		if(other.isDead()){
			gold += other.getGold();
		}
	} else {
		other.setHp(other.getHp() - dmg);
		if(name == "vampire") {
			if(other.getName() == "dwarf") {
				hp -= 10;
			}
		}
		if(other.isDead()){
			if(other.getName() == "dragon") other.setHoardMovable(true);
			int amount = rand() %100;
			if(amount < 50) {
				gold += 1;
			} else {
				gold += 2;
			}
			if(name == "goblin") gold += 5;
		}
	}
	acted = true;
}

int Player::getMaxHp(){
	return maxHp;
}

void Player::setPosn(Cell *c){
	curPosn = c;
}

Player::~Player(){}
