#include "other.h"
using namespace std;

// default ctor
Other::Other():Cell{}{}

// 5 param ctor
Other::Other(string name, int globalX, int globalY, bool movable, bool occupied):
Cell{name, globalX, globalY, movable, occupied}{
	movable = true;
	occupied = false;
}
// pure virtual method for
// subclasses to act accordingly
void Other::pickup(Player &player) {}

// dtor
Other::~Other(){}
