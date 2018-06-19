#include "poisonHealth.h"
using namespace std;
PoisonHealth::PoisonHealth():Potion(){}
PoisonHealth::PoisonHealth(Cell *toDecorate):Potion{"potion", toDecorate}{}

// usePotion
void PoisonHealth::pickup(Player &player){
	int hp = player.getHp();
	if (player.getName() == "drow")
	 	hp -= 15;
	else
		hp -= 10;
	player.setHp(hp);
	player.setActed(true);
}
PoisonHealth::~PoisonHealth(){}
