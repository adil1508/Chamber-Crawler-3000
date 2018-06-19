#include "tile.h"
using namespace std;

Tile::Tile():Cell{}{}

Tile::Tile(string name, int globalX, int globalY, bool movable, bool occupied):
Cell{name, globalX, globalY, movable, occupied}{}

void Tile::pickup(Player &player){}

Tile::~Tile(){}
