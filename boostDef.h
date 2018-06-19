#ifndef BOOST_DEF_H
#define BOOST_DEF_H

#include "potion.h"

class BoostDef final : public Potion {

	public:

	// default ctor
	BoostDef();

	// 1 param ctor
	BoostDef(Cell *toDecorate);

	// overidden method
	void pickup(Player &player) override;

	// dtor
	~BoostDef();

};


#endif
