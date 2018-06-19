#include "boostAtk.h"
using namespace std;

BoostAtk::BoostAtk(Cell *toDecorate):Potion{"potion",toDecorate}{}

void BoostAtk::pickup(Player &player){
	if(player.getName() == "drow") // special case for "drow"
		player.setAtk(player.getAtk() + 7.5);
	else
		player.setAtk(player.getAtk() + 5);
	player.setActed(true);
}

BoostAtk::~BoostAtk(){}
