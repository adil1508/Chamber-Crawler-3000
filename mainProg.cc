#include "floor.h"
#include "player.h"
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char const *argv[]){
    ifstream lose{"lose.txt"};
    ifstream win{"win.txt"};
    string tmp;
    string los;
    string wi;
    while (getline(lose, tmp)) {
          los = los + tmp + "\n";
    }
    while (getline(win, tmp)) {
          wi = wi + tmp + "\n";
    }
	string s = "";
	if (argc == 2){
		s = argv[1];
	}
	Floor f{s};
	bool frozen = false; // enemies frozen
	string race;
	string cmd;
	cout << "Welcome adventurer!" << endl << endl;
	cout << "Pick a race: " << endl;
	cout << "(s) Shade	Hp: 125 Atk: 25 Def: 25" << endl;
	cout << "(d) Drow	Hp: 150 Atk: 25 Def: 15" << endl;
	cout << "(v) Vampire	Hp: 50 Atk: 25 Def: 25" << endl;
	cout << "(t) Troll	Hp: 120 Atk: 25 Def: 15" << endl;
	cout << "(g) Goblin	Hp: 110 Atk: 15 Def: 20" << endl << endl;
	cout << "Enter  race: " << endl;
	cin >> race;
	if (race == "d")
		race = "drow";
	else if (race == "v")
		race = "vampire";
	else if (race == "t")
		race = "troll";
	else if (race == "g")
		race = "goblin";
	else
		race = "shade";
	// create player, need to pass in a cell
	Player *p = new Player{race};
	f.setPlayer(p);
	f.init();
	f.setAction("Player created");
	cout << f << endl;
	// read in commands and call appropriate methods
	while (cin >> cmd){
		Player *pc = f.getPlayer();
		pc->setActed(false);
		bool usedPotion = false;
		int origHp = pc->getHp();
		// resets the characters set to false
		// after checking switch
		if(!frozen){
			// reset all characters acted to false
			f.enemiesActed(false);
		}
		if (cmd == "no" || cmd == "nw" || cmd == "ne" || cmd == "so" || cmd == "sw" || cmd == "se" || cmd == "ea" || cmd == "we"){
			// move player
			// call method from f, the Floor object
			f.movePlayer(cmd);
		} else if (cmd == "u"){ // use potion
			string direction;
			cin >> direction;
			// use potion on player
			f.usePotion(direction);
			usedPotion = true;
		} else if (cmd == "a"){ // attack
			string direction;
			cin >> direction;
			// player attack in that direction
			f.attack(direction);
			pc->getPosn()->notifyObservers();
		} else if (cmd == "f"){
			// stops enemies moving
			f.enemiesActed(true);
			if (frozen){
				frozen = false;
				f.enemiesActed(false);
				f.setAction("Enemies unfrozen");
			} else{
				frozen = true;
				f.enemiesActed(true);
				f.setAction("Enemies frozen");
			}
		} else if (cmd == "r"){
			string race;
			cout << "Pick a race: " << endl;
			cout << "(s) Shade	Hp: 125 Atk: 25 Def: 25" << endl;
			cout << "(d) Drow	Hp: 150 Atk: 25 Def: 15" << endl;
			cout << "(v) Vampire	Hp: 50 Atk: 25 Def: 25" << endl;
			cout << "(t) Troll	Hp: 120 Atk: 25 Def: 15" << endl;
			cout << "(g) Goblin	Hp: 110 Atk: 15 Def: 20" << endl << endl;
			cout << "Enter  race: " << endl;
			cin >> race;
			if (race == "d")
				race = "drow";
			else if (race == "v")
				race = "vampire";
			else if (race == "t")
				race = "troll";
			else if (race == "g")
				race = "goblin";
			else
				race = "shade";
			// restart the game
			// reset the board
			// reset all stats of player. destroy old, create new with the race string
			f.setLevel(0);
			p = new Player{race};
			f.setPlayer(p);
			f.init();
			f.setAction("Game restarted");
                        cout << f << endl;
                        continue;
		} else if (cmd == "q"){
			cout << "Game sucessfully quit" << endl;
			break;
		} 
                // check if player wins the game
                if (f.isWon()) {
                        cout << wi;
                        cout << "Score: ";
                        int score = p->getGold();
                        if (p->getName() == "shade") {
                           score = p->getGold() * 15 / 10;
                        }
                        cout << score << endl;
                        break;
                }
		// enemies possibly attack
		f.enemiesAttack();
		int curHp = pc->getHp();
		if (origHp > curHp && !usedPotion){
			f.setAction(f.getAction() + " and got attacked for " + to_string(origHp-curHp) + " damage");
		}
		// move all enemies
		f.moveEnemy();
		cout << f << endl;
		// check if player is dead
		if (p->isDead()){
			cout << los;
                        cout << "Score: ";
                        int score = p->getGold();
                        if (p->getName() == "shade") {
                           score = p->getGold() * 15 / 10;
                        }
                        cout << score << endl;
                        break;
		}
		// special case for troll
		if (p->getName() == "troll"){
			int hp = p->getHp();
			hp += 5;
			if (hp > p->getMaxHp()){
				p->setHp(p->getMaxHp());
			} else {
				p->setHp(hp);
			}
		}
	}
}
