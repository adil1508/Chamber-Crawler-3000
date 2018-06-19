#ifndef BOOST_ATK_H
#define BOOST_ATK_H

#include "potion.h"
#include <string>

class BoostAtk final : public Potion {

	public:

	// default ctor
	BoostAtk();

	// 1 param ctor
	BoostAtk(Cell *toDecorate);

	// uses a potion
	void pickup(Player &player) override;

	// dtor
	~BoostAtk();

};

#endif
