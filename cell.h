#ifndef CELL_H
#define CELL_H
#include <map>
#include <string>
#include "character.h"
#include "textdisplay.h"

class Character;
class Player;
class Enemy;

class Cell {
    protected:
    std::string name;
    int globalX;
    int globalY;
    bool movable;
    bool occupied;
    Character *character = nullptr;
    std::map<std::string, Cell *> neighbors;
    TextDisplay *display = nullptr;
    public:
    Cell();
    // 5 param ctor
    Cell(std::string name, int globalX, int globalY, bool movable, bool occupied);

    // Getters
    std::string getName() const;
    int getX() const;
    int getY() const;
    bool isMovable() const;
    bool isOccupied() const;
    Character *getCharacter() const;
    TextDisplay *getDisplay() const;
    std::map<std::string, Cell *> getNeighbors() const;
    virtual int getValue() const;
	virtual bool isLinked() const;
	virtual void setLinked();
	
    // special Getters
    // returns a cell * to neighbor at direction
    // nullptr otherwise
    Cell *getNeighbor(std::string direction) const;

    // returns a vector of neighbors
    // that are not nullptr and not occupied
    std::vector<Cell *> validNeighbors() const;

    // Setters
    void setName(std::string name);
    void setX(int globalX);
    void setY(int globalY);
    void setMovable(bool movable);
    void setOccupied(bool occupied);
    void setCharacter(Character *character);

	// detach an observer Cell from neighbors
	void detach(std::string name);

    // attach an observer Cell
    void attach(std::string name, Cell *observer);

    void attach(TextDisplay *display);

	// a reduntant method.
	// attach itself to its neighbors
	void attachMe();

	// pure virtual method for
	// subclasses to act accordingly
	virtual void pickup(Player &player) = 0;
	void notifyObservers();
    void notify(Cell *whoNotified);
    virtual ~Cell()=0;
};

#endif
