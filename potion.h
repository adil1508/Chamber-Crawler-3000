#ifndef POTION_H
#define POTION_H

#include <string>
#include "decoratedTile.h"

// abstract class for Potion decorator
class Potion : public DecoratedTile {
	public:
	Potion();
	Potion(std::string name, Cell *toDecorate);
	~Potion();
};

#endif
