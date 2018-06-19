#ifndef WOUND_ATK_H
#define WOUND_ATK_H
#include "potion.h"
#include <string>

class WoundAtk final : public Potion {
	public:
	WoundAtk();
	WoundAtk(Cell *toDecorate);
	void pickup(Player &player) override;
	~WoundAtk();
};

#endif
