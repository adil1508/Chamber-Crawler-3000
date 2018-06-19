#include "restoreHealth.h"
using namespace std;

RestoreHealth::RestoreHealth():Potion{}{}
RestoreHealth::RestoreHealth(Cell *toDecorate):Potion{"potion", toDecorate}{}

// uses the potion on character
void RestoreHealth::pickup(Player &player){
	int maxHp = player.getMaxHp();
	int hp = player.getHp();
	if (player.getName() == "drow")
	 	hp += 15;
	else
		hp += 10;
	if (hp > maxHp){
		player.setHp(maxHp);
	} else {
		player.setHp(hp);
	}
	player.setActed(true);
}


RestoreHealth::~RestoreHealth(){}
