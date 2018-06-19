#ifndef OTHER_H
#define OTHER_H

#include "cell.h"
#include <string>
#include "player.h"

class Other final : public Cell {
	public:
	// default ctor
	Other();

	// 5 param ctor
	Other(std::string name, int globalX, int globalY, bool movable, bool occupied);

	// pure virtual method for
	// subclasses to act accordingly
	void pickup(Player &player) override;

	// dtor
	~Other();
};

#endif
