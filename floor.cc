#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "floor.h"
using namespace std;

Floor::Floor(string file) : col{79}, row{25}, chambNum{5}, orgDef{0}, orgAtk{0},
     pc{nullptr}, level{0}, td{nullptr} {
    int total_map = 5;
    if (file != "") {
       string s;
       ifstream myfile{file};
       int one_map = 25;
       for (int c = 0; c < total_map; ++c) {
           ostringstream ss;
           for (int i = 0; i < one_map; ++i) {
               if (getline(myfile, s)) {
                  ss << s;
               }
           }
           string cur = ss.str();
           contents.emplace_back(cur);
       }
    } else {
       for (int i = 0; i < total_map; ++i) {
           contents.emplace_back(file);
       }
    }
}

Floor::~Floor() {
     clearFloor();
     delete pc;
}

void Floor::setPlayer(Player * p) {
     delete pc;
     pc = p;
}

void Floor::setLevel() {
     level += 1;
}

// overloaded
void Floor::setLevel(int level){
    this->level = level;
}

void Floor::resetAct() {
     for (unsigned int i = 0; i < Chambers.size(); ++i) {
         Chambers[i]->resetAct();
     }
}

Player *Floor::getPlayer() {
     return pc;
}

int Floor::getLevel() {
     return level;
}

bool Floor::isWon(){
    return won;
}

void Floor::setWon(){
    won = true;
}

void Floor::clearFloor() {
     for (unsigned int j = 0; j < Others.size(); ++j) {
         for (unsigned int k = 0; k < Others[j].size(); ++k) {
             delete Others[j][k];
         }
         Others[j].clear();
     }
     Others.clear();
     for (unsigned int i = 0; i < Chambers.size(); ++i) {
         delete Chambers[i];
     }
     Chambers.clear();
     delete td;
     td = nullptr;
}

void Floor::init() {
     if (level == 0) {
        orgDef = pc->getDef(); // set original atk and def
        orgAtk = pc->getAtk();
     } else {
        pc->setDef(orgDef); // get rid of non-permanent potion effect
        pc->setAtk(orgAtk);
     }
     clearFloor();
     td = new TextDisplay{row, col, contents[level]};
     setLevel();
     for (int i = 0; i < row; ++i) { // only creating new Others once at the beginning
         vector<Other *> rowOth(col);
         for (int j = 0; j < col; ++j) {
             char tmp = td->getSymbol(i, j);
             if (tmp == '+') {
                rowOth[j] = new Other{"door", i, j, true, false};
             } else if (tmp == '#') {
                rowOth[j] = new Other{"path", i, j, true, false};
             } else {
                rowOth[j] = nullptr;
             }
         }
         Others.push_back(rowOth);
     }
     for (int r = 0; r < row; ++r) {

         for (int c = 0; c < col; ++c) {

             char cur = td->getSymbol(r, c);
             if (cur == '+' || cur == '#') {
               char no = td->getSymbol(r-1, c);
               if (no == '+' || no == '#') {
                  Others[r][c]->attach("no", Others[r-1][c]);
               }
               char so = td->getSymbol(r+1, c);
               if (so == '+' || so == '#') {
                  Others[r][c]->attach("so", Others[r+1][c]);
               }
               char ea = td->getSymbol(r, c+1);
               if (ea == '+' || ea == '#') {
                  Others[r][c]->attach("ea", Others[r][c+1]);
               }
               char we = td->getSymbol(r, c-1);
               if (we == '+' || we == '#') {
               Others[r][c]->attach("we", Others[r][c-1]);
               }
               char nw = td->getSymbol(r-1, c-1);
               if (nw == '+' || nw == '#') {
                  Others[r][c]->attach("nw", Others[r-1][c-1]);
               }
               char ne = td->getSymbol(r-1, c+1);
               if (ne == '+' || ne == '#') {
                  Others[r][c]->attach("ne", Others[r-1][c+1]);
               }
               char sw = td->getSymbol(r+1, c-1);
               if (sw == '+' || sw == '#') {
                  Others[r][c]->attach("sw", Others[r+1][c-1]);
               }
               char se = td->getSymbol(r+1, c+1);
               if (se == '+' || se == '#') {
                  Others[r][c]->attach("se", Others[r+1][c+1]);
               }
               Others[r][c]->attach(td);
             }
         }
     }
     for (int num = 0; num < chambNum; ++num) { // creating Chambers

         if (num == 0) {
            Chambers.push_back(new Chamber{num, td, pc, Others[4][29], Others[7][13]});
         } else if (num == 1) {
            Chambers.push_back(new Chamber{num, td, pc, Others[4][38], Others[7][43], Others[11][60], Others[13][69]});
         } else if (num == 2) {
            Chambers.push_back(new Chamber{num, td, pc, Others[9][43], Others[13][43]});
         } else if (num == 3) {
            Chambers.push_back(new Chamber{num, td, pc, Others[14][13], Others[20][25]});
         } else {
            Chambers.push_back(new Chamber{num, td, pc, Others[15][69], Others[18][43], Others[20][36]});
         }

     }

     Others[4][29]->attach("nw", Chambers[0]->getCell(0, 25));
     Others[4][29]->attach("we", Chambers[0]->getCell(1, 25));
     Others[4][29]->attach("sw", Chambers[0]->getCell(2, 25));
     Others[7][13]->attach("nw", Chambers[0]->getCell(3, 9));
     Others[7][13]->attach("no", Chambers[0]->getCell(3, 10));
     Others[7][13]->attach("ne", Chambers[0]->getCell(3, 11));
     Others[4][38]->attach("ne", Chambers[1]->getCell(0, 0));
     Others[4][38]->attach("ea", Chambers[1]->getCell(1, 0));
     Others[4][38]->attach("se", Chambers[1]->getCell(2, 0));
     Others[7][43]->attach("nw", Chambers[1]->getCell(3, 3));
     Others[7][43]->attach("no", Chambers[1]->getCell(3, 4));
     Others[7][43]->attach("ne", Chambers[1]->getCell(3, 5));
     Others[11][60]->attach("ne", Chambers[1]->getCell(7, 22));
     Others[11][60]->attach("ea", Chambers[1]->getCell(8, 22));
     Others[11][60]->attach("se", Chambers[1]->getCell(9, 22));
     Others[13][69]->attach("nw", Chambers[1]->getCell(9, 29));
     Others[13][69]->attach("no", Chambers[1]->getCell(9, 30));
     Others[13][69]->attach("ne", Chambers[1]->getCell(9, 31));
     Others[9][43]->attach("sw", Chambers[2]->getCell(0, 4));
     Others[9][43]->attach("so", Chambers[2]->getCell(0, 5));
     Others[9][43]->attach("se", Chambers[2]->getCell(0, 6));
     Others[13][43]->attach("nw", Chambers[2]->getCell(2, 4));
     Others[13][43]->attach("no", Chambers[2]->getCell(2, 5));
     Others[13][43]->attach("ne", Chambers[2]->getCell(2, 6));
     Others[14][13]->attach("sw", Chambers[3]->getCell(0, 8));
     Others[14][13]->attach("so", Chambers[3]->getCell(0, 9));
     Others[14][13]->attach("se", Chambers[3]->getCell(0, 10));
     Others[20][25]->attach("nw", Chambers[3]->getCell(4, 20));
     Others[20][25]->attach("we", Chambers[3]->getCell(5, 20));
     Others[20][25]->attach("sw", Chambers[3]->getCell(6, 20));
     Others[15][69]->attach("sw", Chambers[4]->getCell(0, 31));
     Others[15][69]->attach("so", Chambers[4]->getCell(0, 32));
     Others[15][69]->attach("se", Chambers[4]->getCell(0, 33));
     Others[18][43]->attach("sw", Chambers[4]->getCell(3, 5));
     Others[18][43]->attach("so", Chambers[4]->getCell(3, 6));
     Others[18][43]->attach("se", Chambers[4]->getCell(3, 7));
     Others[20][36]->attach("ne", Chambers[4]->getCell(3, 0));
     Others[20][36]->attach("ea", Chambers[4]->getCell(4, 0));
     Others[20][36]->attach("se", Chambers[4]->getCell(5, 0));

     // locating player and generating items and enemies
     if (contents[0] == "") {
        int location = locatePlayer();
        generate(location);
     }
}

void Floor::usePotion(string direction){
    Cell *cur = pc->getPosn();
    Cell *neighbor = cur->getNeighbor(direction);
    // only run if neighbor exists at direction
    if (neighbor){
        string cellName = neighbor->getName();
        // only run if the neighbor is a potion
        if (cellName == "potion"){
            // original stats
            int origHp = pc->getHp();
            int origAtk = pc->getAtk();
            int origDef = pc->getDef();
            neighbor->pickup(*pc); // use the potion
            // new stats
            int newHp = pc->getHp();
            int newAtk = pc->getAtk();
            int newDef = pc->getDef();
            if (newHp > origHp){
                action = "Used restore health potion";
            } else if (origHp > newHp){
                action = "Used poison health potion";
            } else if (newAtk > origAtk){
                action = "Used boost attack potion";
            } else if (origAtk > newAtk){
                action = "Used wound attack potion";
            } else if (newDef > origDef){
                action = "Used boost defence potion";
            } else if (origDef > newDef){
                action = "Used wound defence potion";
            }
            neighbor->setName("tile");
            neighbor->setMovable(true);
            td->notify(*neighbor);
        } else {
            action = "No potion there!";
        }
    } else {
            action = "Invalid move!";
    }
}

// player attacks on a tile
void Floor::attack(std::string direction){
    Cell *cur = pc->getPosn();
    Cell *neighbor = cur->getNeighbor(direction);
    // only run if neighbor exists at direction
    if(neighbor){
        string cellName = neighbor->getName();
        if (cellName == "enemy"){
            // get the enemy
            Character *enemy = neighbor->getCharacter();
			if(enemy->getName() == "merchant") merchantMad = true;
			for(int i = 0; i < chambNum; i++) {
				Chambers[i]->setMarchantMad();
			}
            int origEnemHp = enemy->getHp();
            // player attacks the enemy
            pc->attack(*enemy);
            int afterEnemHp = enemy->getHp();
            int damage = origEnemHp - afterEnemHp;
            action = "Attacked " + enemy->getName() + " for " + to_string(damage) + " damage!";
            // the case where enemy dies after player attack
            if (enemy->isDead()){
                neighbor->setName("tile");
                neighbor->setMovable(true);
                neighbor->setOccupied(false);
                //set name for character
                action = "Killed " + enemy->getName() + "!";
                enemy->setName("dead");
                td->notify(*neighbor);
            }
        } else {
            action = "Not an enemy!";
        }
    } else {
        action = "Invalid attack";
    }
}



// sets all enemies acted to val
void Floor::enemiesActed(bool val){
    for (auto chamber : Chambers){
        chamber->enemiesActed(val);
    }
}

// all the enemies will attack
void Floor::enemiesAttack(){
    for(auto chamber : Chambers){
        chamber->enemiesAttack();
    }
}

void Floor::movePlayer(string dir) {
     Cell *tmp = pc->getPosn();
     if (tmp->getNeighbor(dir)) { // intended move accessible
        Cell *cur = tmp->getNeighbor(dir);
        string oldType = tmp->getName();
        string newType = cur->getName();
        if (cur->isMovable()) { // Player can move
           if (cur->getName() == "stairs") { // reaching stairs
              if (level == 5) {
                 won = true;
              } else {
                 action = "Congragulations! You've progressed to the next floor!";
                 clearFloor();
                 init();
              }
          } else { // moving on a non-stair cell
              pc->setPosn(cur);
              action = "Player moves " + dir;
              if (newType.substr(0, 4) == "gold") { // gold pickup
                  action += " and picks up " + to_string(cur->getValue()) + " gold";
                  cur->pickup(*pc);
             }
             // move the player
             cur->setName("player-" + cur->getName());
             cur->setCharacter(pc);
             cur->setMovable(false);
             cur->setOccupied(true);
             cur->notifyObservers();
             tmp->setName(oldType.substr(7,4));
             tmp->setCharacter(nullptr);
             tmp->setMovable(true);
             tmp->setOccupied(false);
             tmp->notifyObservers();
            }
        } else { // update action to display
            action = "Can't move! " + cur->getName() + " is in the way!";
         }
      } else {
         action = "Invalid Move!";
      }
}

int Floor::locatePlayer() {
	srand(time(NULL));
	//random generate the Player
	int pc_randCham = rand() %chambNum;
	int pc_tileRow = Chambers[pc_randCham]->getRow();
	int pc_tileCol = Chambers[pc_randCham]->getCol();
	Cell *pc_initPosn = nullptr;
	while(pc_initPosn == nullptr || pc_initPosn->isOccupied()) {
		int pc_randRow = rand() %pc_tileRow;
		int pc_randCol = rand() %pc_tileCol;
		pc_initPosn = Chambers[pc_randCham]->getCell(pc_randRow, pc_randCol);
	}
	pc->setPosn(pc_initPosn);
	pc_initPosn->setName("player_tile");
	pc_initPosn->setCharacter(pc);
	pc_initPosn->setOccupied(true);
	pc_initPosn->notifyObservers();
	return pc_randCham;
}

void Floor::generate(int pc_randCham){
	//0 - RH, 1 - BA, 2 - BD, 3 - PH, 4 - WA, 5 - WD, 6 - normal gold pile,
	//7 - small hoard, 8 - merchant hoard, 9 - dragon hoard
	srand(time(NULL));
	//random generating the stairs
	int stairs_randCham = rand() %chambNum;
	while(stairs_randCham == pc_randCham){
		stairs_randCham = rand() %chambNum;
	}
	int stairs_tileRow = Chambers[stairs_randCham]->getRow();
	int stairs_tileCol = Chambers[stairs_randCham]->getCol();
	Cell *stairs_initPosn = nullptr;
	while(stairs_initPosn == nullptr || stairs_initPosn->isOccupied()) {
		int stairs_randRow = rand() %stairs_tileRow;
		int stairs_randCol = rand() %stairs_tileCol;
		stairs_initPosn = Chambers[stairs_randCham]->getCell(stairs_randRow, stairs_randCol);
	}
	//construct the stairs here
	stairs_initPosn->setName("stairs");
	stairs_initPosn->notifyObservers();
	stairs_initPosn->setOccupied(true);
	stairs_initPosn->setMovable(true);

	//random generating 10 potions
	for(int i = 0; i < 10; ++i) {
		//find where to generate potion
		int potion_type = rand() %6;
		int potion_cham = rand() %chambNum;
		int potion_tileRow = Chambers[potion_cham]->getRow();
		int potion_tileCol = Chambers[potion_cham]->getCol();
		Cell *potion_initPosn = nullptr;
		int potion_randRow = 0;
		int potion_randCol = 0;
		while(potion_initPosn == nullptr || potion_initPosn->isOccupied()) {
			potion_randRow = rand() %potion_tileRow;
			potion_randCol = rand() %potion_tileCol;
			potion_initPosn =  Chambers[potion_cham]->getCell(potion_randRow, potion_randCol);
		}
		//construct the potion
		if(potion_type == 0) {
			Chambers[potion_cham]->setCell(potion_randRow, potion_randCol, new RestoreHealth{potion_initPosn});
		} else if(potion_type == 1) {
			Chambers[potion_cham]->setCell(potion_randRow, potion_randCol, new BoostAtk{potion_initPosn});
		} else if(potion_type == 2) {
			Chambers[potion_cham]->setCell(potion_randRow, potion_randCol, new BoostDef{potion_initPosn});
		} else if(potion_type == 3) {
			Chambers[potion_cham]->setCell(potion_randRow, potion_randCol, new PoisonHealth{potion_initPosn});
		} else if(potion_type == 4) {
			Chambers[potion_cham]->setCell(potion_randRow, potion_randCol, new WoundAtk{potion_initPosn});
		} else if(potion_type == 5) {
			Chambers[potion_cham]->setCell(potion_randRow, potion_randCol, new WoundDef{potion_initPosn});
		}
		Chambers[potion_cham]->getCell(potion_randRow, potion_randCol)->notifyObservers();
		potion_initPosn->setName("potion");
		potion_initPosn->notifyObservers();
		potion_initPosn->setMovable(false);
		potion_initPosn->setOccupied(true);
	}
	//random generating gold
	for(int k = 0; k < 10; ++k) {
		int goldArr[] = {6, 6, 6, 6, 6, 7, 7, 9};
		int gold_cham = rand() %chambNum;
		int gold_it = rand() %8;
		int gold_type = goldArr[gold_it];
		int gold_tileRow = Chambers[gold_cham]->getRow();
		int gold_tileCol = Chambers[gold_cham]->getCol();
		Cell *gold_initPosn = nullptr;
		int gold_randRow = 0;
		int gold_randCol = 0;
		//when it's DH, check if at least 1 neighbour is valid and not occupied
		while(gold_initPosn == nullptr || gold_initPosn->isOccupied()) {
			gold_randRow = rand() %gold_tileRow;
			gold_randCol = rand() %gold_tileCol;
			gold_initPosn =  Chambers[gold_cham]->getCell(gold_randRow, gold_randCol);
		}
		vector <Cell *> possibleNeighbors = gold_initPosn->validNeighbors();
		while((gold_type == 9) &&
		(possibleNeighbors.size() == 0 || gold_initPosn == nullptr || gold_initPosn->isOccupied())) {
			gold_randRow = rand() %gold_tileRow;
			gold_randCol = rand() %gold_tileCol;
			gold_initPosn = Chambers[gold_cham]->getCell(gold_randRow, gold_randCol);

		}
		//construct the gold
		if(gold_type == 6) {
            gold_initPosn = new Gold{"goldNormal", gold_initPosn};
			Chambers[gold_cham]->setCell(gold_randRow, gold_randCol, gold_initPosn);
			Chambers[gold_cham]->getCell(gold_randRow, gold_randCol)->notifyObservers();
		} else if(gold_type == 7) {
            gold_initPosn = new Gold{"goldSmall", gold_initPosn};
			Chambers[gold_cham]->setCell(gold_randRow, gold_randCol, gold_initPosn);
			Chambers[gold_cham]->getCell(gold_randRow, gold_randCol)->notifyObservers();
		} else if(gold_type == 9) {
			gold_initPosn = new Gold{"goldDragon", gold_initPosn};
			Chambers[gold_cham]->setCell(gold_randRow, gold_randCol, gold_initPosn);
			//respwan the dragon within the range
			int possibleDragonDir = possibleNeighbors.size();
			int dragonDir = rand() %possibleDragonDir;
			Cell *dragon_initPosn = possibleNeighbors[dragonDir];
			//find dragon's local Posn
			Enemy *newDragon = new Enemy{"dragon", dragon_initPosn, gold_initPosn};
			newDragon->setHoard(gold_initPosn);
			Chambers[gold_cham]->addEm(newDragon);
			dragon_initPosn->setCharacter(newDragon);
			gold_initPosn->setName("goldDragon");
			dragon_initPosn->setName("enemy");
			gold_initPosn->notifyObservers();
			dragon_initPosn->notifyObservers();
			dragon_initPosn->setMovable(false);
			dragon_initPosn->setOccupied(true);
			gold_initPosn->setMovable(false);
			gold_initPosn->setOccupied(true);
		}
	}
	//random generating the enemies
	for(int e = 0; e < 20; ++e) {
		char enemyArr[] = {'h','h','h','h','w','w','w','e','e',
		'o','o','m','m','l','l','l','l','l'};
		int enemy_cham = rand() %chambNum;
		int enemy_it = rand() %18;
		char enemy_type = enemyArr[enemy_it];
		int enemy_tileRow = Chambers[enemy_cham]->getRow();
		int enemy_tileCol = Chambers[enemy_cham]->getCol();
		Cell *enemy_initPosn = nullptr;
		int enemy_randRow = 0;
		int enemy_randCol = 0;
		while(enemy_initPosn == nullptr || enemy_initPosn->isOccupied()) {
			enemy_randRow = rand() %enemy_tileRow;
			enemy_randCol = rand() %enemy_tileCol;
			enemy_initPosn = Chambers[enemy_cham]->getCell(enemy_randRow, enemy_randCol);
		}
		//construct the enemies
		if(enemy_type == 'h') {
			Enemy *temp = new Enemy{"human", enemy_initPosn};
			Chambers[enemy_cham]->addEm(temp);
			enemy_initPosn->setCharacter(temp);
		} else if(enemy_type == 'w') {
			Enemy *temp = new Enemy{"dwarf", enemy_initPosn};
			Chambers[enemy_cham]->addEm(temp);
			enemy_initPosn->setCharacter(temp);
		} else if(enemy_type == 'e') {
			Enemy *temp = new Enemy{"elf", enemy_initPosn};
			Chambers[enemy_cham]->addEm(temp);
			enemy_initPosn->setCharacter(temp);
		} else if(enemy_type == 'o') {
			Enemy *temp = new Enemy{"orcs", enemy_initPosn};
			Chambers[enemy_cham]->addEm(temp);
			enemy_initPosn->setCharacter(temp);
		} else if(enemy_type == 'm') {
			Enemy *temp = new Enemy{"merchant", enemy_initPosn};
			if(merchantMad == true) temp->setHostility(true);
			Chambers[enemy_cham]->addEm(temp);
			enemy_initPosn->setCharacter(temp);
		} else if(enemy_type == 'l') {
			Enemy *temp = new Enemy{"halfling", enemy_initPosn};
			Chambers[enemy_cham]->addEm(temp);
			enemy_initPosn->setCharacter(temp);
		}
		enemy_initPosn->setName("enemy");
		enemy_initPosn->notifyObservers();
		enemy_initPosn->setMovable(false);
		enemy_initPosn->setOccupied(true);
	}
}

void Floor::moveEnemy() {
     for (int i = 0; i < chambNum; ++i) {
         Chambers[i]->moveEm();
     }
}

string Floor::getAction() const{
        return action;
}

void Floor::setAction(string action){
    this->action = action;
}

ostream &operator<<(ostream &out, const Floor &f) {
     out << *(f.td);
     out << "Race: " << f.pc->getName() << " Gold: " << f.pc->getGold();
     out << "                                                  Floor: " << f.level << endl;
     out << "HP: " << f.pc->getHp() << endl;
     out << "Atk: " << f.pc->getAtk() << endl;
     out << "Def: " << f.pc->getDef() << endl;
     out << "Action: " << f.action;
     return out;
}
