#ifndef GOLD_H
#define GOLD_H

#include "decoratedTile.h"
#include <string>

// final decorator
class Gold final : public DecoratedTile{

	int value;

	public:
	// default ctor
	Gold();

	// the ctor we will actually use
	Gold(std::string name, Cell *toDecorate);

	int getValue() const override;

	// implemented pure virtual method
	// added its own value to callers character trove
	void pickup(Player &player) override;

	// dtor
	~Gold();

};
#endif
