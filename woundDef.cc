#include "woundDef.h"
using namespace std;

WoundDef::WoundDef():Potion{}{}

WoundDef::WoundDef(Cell *toDecorate):Potion{"potion", toDecorate}{}

void WoundDef::pickup(Player &player){
	if(player.getName() == "drow")
		player.setDef(player.getDef() - 7.5);
	else
		player.setDef(player.getDef() - 5);
	player.setActed(true);
}

WoundDef::~WoundDef(){}
