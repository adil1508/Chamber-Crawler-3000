#include "cell.h"
using namespace std;

Cell::Cell():name{""},
globalX{0},
globalY{0},
movable{true},
occupied{false}{}

Cell::Cell(string name, int globalX, int globalY, bool movable, bool occupied):
name{name},
globalX{globalX},
globalY{globalY},
movable{movable},
occupied{occupied}{}

bool Cell::isLinked() const {
	return false;
}

void Cell::setLinked() {}

string Cell::getName() const {
	return name;
}

int Cell::getX() const {
	return globalX;
}

int Cell::getY() const {
	return globalY;
}

bool Cell::isMovable() const {
	return movable;
}

bool Cell::isOccupied() const {
	return occupied;
}

Character *Cell::getCharacter() const {
	return character;
}

TextDisplay * Cell::getDisplay() const {
	return display;
}

map<string, Cell *> Cell::getNeighbors() const {
		return neighbors;
}

Cell *Cell::getNeighbor(string direction) const {
	if (neighbors.count(direction)){
		return neighbors.at(direction);
	} else {
		return nullptr;
	}
}

int Cell::getValue() const {
        return 1;
}

void Cell::setName(string name){
	this->name = name;
}

void Cell::setX(int globalX){
	this->globalX = globalX;
}

void Cell::setY(int globalY){
	this->globalY = globalY;
}

void Cell::setMovable(bool movable){
	this->movable = movable;
}

void Cell::setOccupied(bool occupied){
	this->occupied = occupied;
}

// sets character a Cell might point to
// HAVE to run for enemy or player Cells
void Cell::setCharacter(Character *character){
	this->character = character;
}

// detach an observer Cell from neighbors
void Cell::detach(std::string name){
	neighbors.erase(name);
}

void Cell::attach(string name, Cell *observerCell){
	neighbors[name] = observerCell;;
}

void Cell::attach(TextDisplay *display){
	this->display = display;
}

void Cell::attachMe(){
	for (auto neighbor : neighbors){
		if (neighbor.first == "nw"){
			(neighbor.second)->detach("se");	// detach old neighbor
			(neighbor.second)->attach("se", this);	// attach me instead
		} else if (neighbor.first == "no"){
			(neighbor.second)->detach("so");
			(neighbor.second)->attach("so", this);
		} else if (neighbor.first == "ne"){
			(neighbor.second)->detach("sw");
			(neighbor.second)->attach("sw", this);
		} else if (neighbor.first == "we"){
			(neighbor.second)->detach("ea");
			(neighbor.second)->attach("ea", this);
		} else if (neighbor.first == "ea"){
			(neighbor.second)->detach("we");
			(neighbor.second)->attach("we", this);
		} else if (neighbor.first == "sw"){
			(neighbor.second)->detach("ne");
			(neighbor.second)->attach("ne", this);
		} else if (neighbor.first == "so"){
			(neighbor.second)->detach("no");
			(neighbor.second)->attach("no", this);
		} else if (neighbor.first == "se"){
			(neighbor.second)->detach("nw");
			(neighbor.second)->attach("nw", this);
		}
	}
}

// returns a vector of neighbors
// that are not nullptr and not occupied
std::vector<Cell *> Cell::validNeighbors() const {
	// the vector to return
	vector<Cell *> valid;
	for (auto p : neighbors){
		// add Cell * if the Cell * is valid
		// and not occupied
		if (p.second){
			if (!p.second->isOccupied() && p.second->getName() == "tile"){
				valid.emplace_back(p.second);
			}
		}
	}
	return valid;
}

// SUBJECT METHOD
// notify observers
void Cell::notifyObservers(){
	for (auto it = neighbors.begin(); it != neighbors.end(); ++it){
		(it->second)->notify(this);
	}
	display->notify(*this);
}

// OBSERVER METHOD
// does something when notified
void Cell::notify(Cell *whoNotified){
	// enemy cell being notified by player
	if (name == "enemy" && character->getHostility() 
		&& whoNotified->getName().substr(0,6) == "player" && !character->getActed()){ 
		character->attack(*(whoNotified->getCharacter()));
	} else if(this->name == "goldDragon" && whoNotified->getName().substr(0,6) == "player"){ 
		// player notified a goldDragon
		for(auto p : neighbors){
			if((p.second)->getName() == "enemy"){
				if((p.second)->getCharacter()->getName() == "dragon" && !((p.second)->getCharacter()->getActed())){
					(p.second)->getCharacter()->attack(*(whoNotified->getCharacter()));
				}
			}
		}
	}
}

Cell::~Cell(){}
