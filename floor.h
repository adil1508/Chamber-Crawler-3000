#ifndef __FLOOR_H__
#define __FLOOR_H__
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "cell.h"
#include "textdisplay.h"
#include "other.h"
#include "chamber.h"
#include "player.h"
#include "boostAtk.h"
#include "boostDef.h"
#include "poisonHealth.h"
#include "restoreHealth.h"
#include "woundAtk.h"
#include "woundDef.h"
#include "gold.h"

class Chamber;

class Floor {
    const int col;
    const int row;
    const int chambNum;
    bool won = false;
	bool merchantMad = false;
    int orgDef; // keep track of Player's original defence
    int orgAtk; // keep track of Player's original attack
    Player *pc;
    int level;
    TextDisplay *td;
    std::vector<Chamber *> Chambers;
    std::vector<std::vector<Other *>> Others;
    std::vector<std::string> contents;
    std::string action; // action message to print out
    void clearFloor();
	
    public:
	Floor(std::string file = "");
    ~Floor();
    void movePlayer(std::string dir);
    void moveEnemy();
    int locatePlayer();
    void generate(int pc_randCham);
    void resetAct();
    void usePotion(std::string direction);
    void attack(std::string direction);
    void enemiesActed(bool val);
    void enemiesAttack();
    void init();
	bool isWon();
    Player *getPlayer();
    int getLevel();
    std::string getAction() const;
    void setAction(std::string action);
    void setLevel(int level);
    void setLevel();
    void setPlayer(Player * p);
	void setWon();
    friend std::ostream &operator<<(std::ostream &out, const Floor &f);

};

std::ostream &operator<<(std::ostream &out, const Floor &f);

#endif
