#include "boostDef.h"
using namespace std;

BoostDef::BoostDef(Cell *toDecorate):Potion{"potion", toDecorate}{}

void BoostDef::pickup(Player &player){
	if(player.getName() == "drow")
		player.setDef(player.getDef() + 7.5);
	else
		player.setDef(player.getDef() + 5);

	player.setActed(true);
}

BoostDef::~BoostDef(){}
