#include "gold.h"

using namespace std;

// default ctor
Gold::Gold(): DecoratedTile{}{}

// the ctor we will actually use
Gold::Gold(string name, Cell *toDecorate):DecoratedTile{name, toDecorate}{
	if (name == "goldSmall")
		value = 1;
	else if (name == "goldNormal")
		value = 2;
	else if (name == "goldDragon")
		value = 6;
	else	// bad name
		value = 0;
}

int Gold::getValue() const{
	return value;
}

// this is called when somebody picks me up
void Gold::pickup(Player &player){
	player.setGold(player.getGold() + value);
	Cell *playerTile = player.getPosn();
	playerTile->setName("tile");
	value = 0;
	player.setActed(true);
}

Gold::~Gold(){}
