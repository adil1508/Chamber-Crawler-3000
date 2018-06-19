#include "decoratedTile.h"

using namespace std;

// default ctor
DecoratedTile::DecoratedTile():Cell(){
}

// 2 param ctor
DecoratedTile::DecoratedTile(string name, Cell *toDecorate):Cell{name,toDecorate->getX(),toDecorate->getY(),true,true},
toDecorate{toDecorate}{
    this->character = toDecorate->getCharacter();
    this->display = toDecorate->getDisplay();
    this->neighbors = toDecorate->getNeighbors();
    this->attachMe();
    if (name == "goldDragon" || name == "potion"){
        this->movable = false;
    }

}

bool DecoratedTile::isLinked() const {
	return linked;
}
void DecoratedTile::setLinked(){
	linked = true;
}

DecoratedTile::~DecoratedTile(){
    delete toDecorate;
}
