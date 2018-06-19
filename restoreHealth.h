#ifndef RESTORE_HEALTH_H
#define RESTORE_HEALTH_H
#include <string>
#include "potion.h"
class RestoreHealth final : public Potion {
	public:
	RestoreHealth();
	RestoreHealth(Cell *toDecorate);
	void pickup(Player &player) override;
	~RestoreHealth();
};

#endif
