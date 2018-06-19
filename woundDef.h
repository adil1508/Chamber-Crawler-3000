#ifndef WOUND_DEF_H
#define WOUND_DEF_H
#include "potion.h"
#include <string>

class WoundDef final : public Potion {
	public:
	WoundDef();
	WoundDef(Cell *toDecorate);
	void pickup(Player &player) override;
	~WoundDef();
};

#endif
