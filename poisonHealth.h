#ifndef POISON_HEALTH_H
#define POISON_HEALTH_H

#include "potion.h"
#include <string>

class PoisonHealth final : public Potion {
	public:
	// default ctor
	PoisonHealth();
	
	// 1  param ctor
	PoisonHealth(Cell *toDecorate);

	// implement usePotion
	void pickup(Player &player) override;

	// dtor 
	~PoisonHealth();
};

#endif
