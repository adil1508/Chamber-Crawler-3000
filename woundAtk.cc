#include "woundAtk.h"
using namespace std;
WoundAtk::WoundAtk():Potion{}{}

// 1 param ctor
WoundAtk::WoundAtk(Cell *toDecorate):Potion{"potion",toDecorate}{}

// uses a potion
void WoundAtk::pickup(Player &player){
	if(player.getName() == "drow")
		player.setAtk(player.getAtk() - 7.5);
	else
		player.setAtk(player.getAtk() - 5);
	player.setActed(true);
}
WoundAtk::~WoundAtk(){}
