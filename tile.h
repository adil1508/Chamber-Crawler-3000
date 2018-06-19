#ifndef TILE_H
#define TILE_H
#include <string>
#include "cell.h"

class Tile final : public Cell {
	public:
	Tile();
	// pure virtual method for
	// subclasses to act accordingly
	void pickup(Player &player) override;
	Tile(std::string name, int globalX, int globalY, bool movable, bool occupied);
	~Tile();
};

#endif
