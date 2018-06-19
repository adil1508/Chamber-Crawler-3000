#include "potion.h"
using namespace std;

// default ctor
Potion::Potion():DecoratedTile{}{
	name = "potion";
	movable = false;
}

Potion::Potion(string name, Cell *toDecorate):DecoratedTile{name, toDecorate}{}
Potion::~Potion(){}
