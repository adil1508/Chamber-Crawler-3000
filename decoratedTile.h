#ifndef DECORATED_CLASS_H
#define DECORATED_CLASS_H

#include "cell.h"
#include <string>
#include "player.h"

// this is an abstract decorator class
class DecoratedTile : public Cell {
	Cell *toDecorate = nullptr;
	bool linked = false;
	public:
	// default ctor
	DecoratedTile();
	// 2 param ctor
	DecoratedTile(std::string name, Cell *toDecorate);
	bool isLinked() const override;
	void setLinked() override;
	// dtor
	~DecoratedTile() = 0;
};
#endif
