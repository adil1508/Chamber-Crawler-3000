#include <iostream>
#include "chamber.h"
using namespace std;

Chamber::Chamber(int n, TextDisplay *td, Player * pc, 
   Cell *door1, Cell *door2, Cell *door3, Cell *door4) {
     num = n;
     if (num == 0) {
        globStarX = 3;
        globStarY = 3;
        row = 4;
        col = 26;
     } else if (num == 1) {
        globStarX = 3;
        globStarY = 39;
        row = 10;
        col = 37;

     } else if (num == 2) {
        globStarX = 10;
        globStarY = 38;
        row = 3;
        col = 12;
     } else if (num == 3) {
        globStarX = 15;
        globStarY = 4;
        row = 7;
        col = 21;
     } else {
        globStarX = 16;
        globStarY = 37;
        row = 6;
        col = 39;
     }
     total = row * col;
     for (int j = 0; j < row; ++j) {
         vector<Cell *> rowOfT(col);
         for (int k = 0; k < col; ++k) {
             char tmp = td->getSymbol(j+globStarX, k+globStarY);
             if (num == 1) {
                if (j > 3) {
                   if (k > 15) {
                      if (tmp == '.') {
                         rowOfT[k] = new Tile{"tile", j+globStarX, k+globStarY, true, false}; 
						 rowOfT[k]->attach(td);
                      } else if (tmp == '@'|| tmp == '\\' || tmp == 'M' || tmp == 'L' || tmp == 'O' 
                                 || tmp == 'W' || tmp == 'E' || tmp == 'D' || tmp == 'H') {
                        rowOfT[k] = new Tile{"tile", j+globStarX, k+globStarY, true, false}; 
						rowOfT[k]->attach(td);
						if(tmp == '@') {
							rowOfT[k]->setName("player_tile");
							pc->setPosn(rowOfT[k]);
							rowOfT[k]->setCharacter(pc);
							rowOfT[k]->setOccupied(true);
							rowOfT[k]->notifyObservers();
						} else if(tmp == '\\') {
							rowOfT[k]->setName("stairs");
							rowOfT[k]->setOccupied(true);
							rowOfT[k]->setMovable(true);
							rowOfT[k]->notifyObservers();
						} else if(tmp == 'M') {
							Enemy *temp = new Enemy{"merchant", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'L') {
							Enemy *temp = new Enemy{"halfling", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'O') {
							Enemy *temp = new Enemy{"orcs", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'E') {
							Enemy *temp = new Enemy{"elf", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'W') {
							Enemy *temp = new Enemy{"dwarf", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'H') {
							Enemy *temp = new Enemy{"human", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'D') {
							Enemy *temp = new Enemy{"dragon", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						}
                      } else if (tmp == '0' || tmp == '1' || tmp == '2' || tmp == '3' || tmp == '4' 
                                 || tmp == '5' || tmp == '6' || tmp == '7' || tmp == '8' || tmp == '9') {
						if(tmp == '0') {
							rowOfT[k] = new RestoreHealth{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '1') {
							rowOfT[k] = new BoostAtk{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '2') {
							rowOfT[k] = new BoostDef{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '3') {
							rowOfT[k] = new PoisonHealth{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '4') {
							rowOfT[k] = new WoundAtk{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '5') {
							rowOfT[k] = new WoundDef{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '6') {
							rowOfT[k] = new Gold{"goldNormal", new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->notifyObservers();
						} else if(tmp == '7') {
							rowOfT[k] = new Gold{"goldSmall", new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->notifyObservers();
						} else if(tmp == '8') {
							// there is no such thing
						} else if(tmp == '9') {
							rowOfT[k] = new Gold{"goldDragon", new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->notifyObservers();
						}
                      } else {
                         rowOfT[k] = nullptr;
                      }
                   } else {
                      rowOfT[k] = nullptr;
                   }
                } else {
                  if (tmp == '.') {
                     rowOfT[k] = new Tile{"tile", j+globStarX, k+globStarY, true, false};  
					 rowOfT[k]->attach(td);
                  } else if (tmp == '@'|| tmp == '\\' || tmp == 'M' || tmp == 'L' || tmp == 'O' 
                             || tmp == 'W' || tmp == 'E' || tmp == 'D' || tmp == 'H') {
                        rowOfT[k] = new Tile{"tile", j+globStarX, k+globStarY, true, false}; 
						rowOfT[k]->attach(td);
						if(tmp == '@') {
							rowOfT[k]->setName("player_tile");
							pc->setPosn(rowOfT[k]);
							rowOfT[k]->setCharacter(pc);
							rowOfT[k]->setOccupied(true);
							rowOfT[k]->notifyObservers();
						} else if(tmp == '\\') {
							rowOfT[k]->setName("stairs");
							rowOfT[k]->setOccupied(true);
							rowOfT[k]->setMovable(true);
							rowOfT[k]->notifyObservers();
						} else if(tmp == 'M') {
							Enemy *temp = new Enemy{"merchant", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'L') {
							Enemy *temp = new Enemy{"halfling", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'O') {
							Enemy *temp = new Enemy{"orcs", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'E') {
							Enemy *temp = new Enemy{"elf", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'W') {
							Enemy *temp = new Enemy{"dwarf", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'H') {
							Enemy *temp = new Enemy{"human", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'D') {
							Enemy *temp = new Enemy{"dragon", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						}
                      } else if (tmp == '0' || tmp == '1' || tmp == '2' || tmp == '3' || tmp == '4' || tmp == '5' 
                                 || tmp == '6' || tmp == '7' || tmp == '8' || tmp == '9') {
						if(tmp == '0') {
							rowOfT[k] = new RestoreHealth{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '1') {
							rowOfT[k] = new BoostAtk{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '2') {
							rowOfT[k] = new BoostDef{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '3') {
							rowOfT[k] = new PoisonHealth{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '4') {
							rowOfT[k] = new WoundAtk{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '5') {
							rowOfT[k] = new WoundDef{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '6') {
							rowOfT[k] = new Gold{"goldNormal", new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->notifyObservers();
						} else if(tmp == '7') {
							rowOfT[k] = new Gold{"goldSmall", new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->notifyObservers();
						} else if(tmp == '8') {
							// there is no such thing
						} else if(tmp == '9') {
							rowOfT[k] = new Gold{"goldDragon", new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->notifyObservers();
						}
                  } else {
                     rowOfT[k] = nullptr;
                  }  
                }
             } else {
                if (tmp == '.') {
                   rowOfT[k] = new Tile{"tile", j+globStarX, k+globStarY, true, false};  
				   rowOfT[k]->attach(td);
                } else if (tmp == '@'|| tmp == '\\' || tmp == 'M' || tmp == 'L' || tmp == 'O' 
                           || tmp == 'W' || tmp == 'E' || tmp == 'D' || tmp == 'H') {
                        rowOfT[k] = new Tile{"tile", j+globStarX, k+globStarY, true, false}; 
						rowOfT[k]->attach(td);
						if(tmp == '@') {
							rowOfT[k]->setName("player_tile");
							pc->setPosn(rowOfT[k]);
							rowOfT[k]->setCharacter(pc);
							rowOfT[k]->setOccupied(true);
							rowOfT[k]->notifyObservers();
						} else if(tmp == '\\') {
							rowOfT[k]->setName("stairs");
							rowOfT[k]->setOccupied(true);
							rowOfT[k]->setMovable(true);
							rowOfT[k]->notifyObservers();
						} else if(tmp == 'M') {
							Enemy *temp = new Enemy{"merchant", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'L') {
							Enemy *temp = new Enemy{"halfling", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'O') {
							Enemy *temp = new Enemy{"orcs", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'E') {
							Enemy *temp = new Enemy{"elf", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'W') {
							Enemy *temp = new Enemy{"dwarf", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'H') {
							Enemy *temp = new Enemy{"human", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == 'D') {
							Enemy *temp = new Enemy{"dragon", rowOfT[k]};
							addEm(temp);
							rowOfT[k]->setCharacter(temp);
							rowOfT[k]->setName("enemy");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						}
                      } else if (tmp == '0' || tmp == '1' || tmp == '2' || tmp == '3' || tmp == '4' 
                                 || tmp == '5' || tmp == '6' || tmp == '7' || tmp == '8' || tmp == '9') {
						if(tmp == '0') {
							rowOfT[k] = new RestoreHealth{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '1') {
							rowOfT[k] = new BoostAtk{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '2') {
							rowOfT[k] = new BoostDef{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '3') {
							rowOfT[k] = new PoisonHealth{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '4') {
							rowOfT[k] = new WoundAtk{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '5') {
							rowOfT[k] = new WoundDef{new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->setName("potion");
							rowOfT[k]->notifyObservers();
							rowOfT[k]->setMovable(false);
							rowOfT[k]->setOccupied(true);
						} else if(tmp == '6') {
							rowOfT[k] = new Gold{"goldNormal", new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->notifyObservers();
						} else if(tmp == '7') {
							rowOfT[k] = new Gold{"goldSmall", new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->notifyObservers();
						} else if(tmp == '8') {
							// there is no such thing
						} else if(tmp == '9') {
							rowOfT[k] = new Gold{"goldDragon", new Tile{"tile", j+globStarX, k+globStarY, true, false}};
							rowOfT[k]->attach(td);
							rowOfT[k]->notifyObservers();
						}
                } else {
                   rowOfT[k] = nullptr;
                }
            }
         }
         Tiles.emplace_back(rowOfT);
     }
     for (int r = 0; r < row; ++r) {
         for (int c = 0; c < col; ++c) {
             char cur = td->getSymbol(r+globStarX, c+globStarY);
             if ((cur == '.' || cur == '@'|| cur == '\\' || cur == 'M' || cur == 'L' 
                  || cur == 'O' || cur == 'W' || cur == 'E' || cur == 'D' || cur == 'H' || 
                  cur == 'P' || cur == 'G')
                 && Tiles[r][c] != nullptr) {
                char no = td->getSymbol(r+globStarX-1, c+globStarY);
                if (no == '.' || no == '@'|| no == '\\' || no == 'M' || no == 'L'
                  || no == 'O' || no == 'W' || no == 'E' || no == 'D' || no == 'H' ||
                  no == 'P' || no == 'G') {
                   Tiles[r][c]->attach("no", Tiles[r-1][c]);
                }
                char so = td->getSymbol(r+globStarX+1, c+globStarY);
                if (so == '.' || so == '@'|| so == '\\' || so == 'M' || so == 'L'
                  || so == 'O' || so == 'W' || so == 'E' || so == 'D' || so == 'H' ||
                  so == 'P' || so == 'G') {
                   Tiles[r][c]->attach("so", Tiles[r+1][c]);
                }
                char ea = td->getSymbol(r+globStarX, c+globStarY+1);
                if (ea == '.' || ea == '@'|| ea == '\\' || ea == 'M' || ea == 'L'
                  || ea == 'O' || ea == 'W' || ea == 'E' || ea == 'D' || ea == 'H' ||
                  ea == 'P' || ea == 'G') {
                   Tiles[r][c]->attach("ea", Tiles[r][c+1]);
                }
                char we = td->getSymbol(r+globStarX, c+globStarY-1);
                if (we == '.' || we == '@'|| we == '\\' || we == 'M' || we == 'L'
                  || we == 'O' || we == 'W' || we == 'E' || we == 'D' || we == 'H' ||
                  we == 'P' || we == 'G') {
                   Tiles[r][c]->attach("we", Tiles[r][c-1]);
                }
                char nw = td->getSymbol(r+globStarX-1, c+globStarY-1);
                if (nw == '.' || nw == '@'|| nw == '\\' || nw == 'M' || nw == 'L'
                  || nw == 'O' || nw == 'W' || nw == 'E' || nw == 'D' || nw == 'H' ||
                  nw == 'P' || nw == 'G') {
                   Tiles[r][c]->attach("nw", Tiles[r-1][c-1]);
                }
                char ne = td->getSymbol(r+globStarX-1, c+globStarY+1);
                if (ne == '.' || ne == '@'|| ne == '\\' || ne == 'M' || ne == 'L'
                  || ne == 'O' || ne == 'W' || ne == 'E' || ne == 'D' || ne == 'H' ||
                  ne == 'P' || ne == 'G') {
                   Tiles[r][c]->attach("ne", Tiles[r-1][c+1]);
                }
                char sw = td->getSymbol(r+globStarX+1, c+globStarY-1);
                if (sw == '.' || sw == '@'|| sw == '\\' || sw == 'M' || sw == 'L'
                  || sw == 'O' || sw == 'W' || sw == 'E' || sw == 'D' || sw == 'H' ||
                  sw == 'P' || sw == 'G') {
                   Tiles[r][c]->attach("sw", Tiles[r+1][c-1]);
                }
                char se = td->getSymbol(r+globStarX+1, c+globStarY+1);
                if (se == '.' || se == '@'|| se == '\\' || se == 'M' || se == 'L'
                  || se == 'O' || se == 'W' || se == 'E' || se == 'D' || se == 'H' ||
                  se == '8' || se == '9') {
                   Tiles[r][c]->attach("se", Tiles[r+1][c+1]);
                }
             }
         }
     }
     if (num == 0) {
        Tiles[0][25]->attach("se", door1);
        Tiles[1][25]->attach("ea", door1);
        Tiles[2][25]->attach("ne", door1);
        Tiles[3][9]->attach("se", door2);
        Tiles[3][10]->attach("so", door2);
        Tiles[3][11]->attach("sw", door2);
     } else if (num == 1) {
        Tiles[0][0]->attach("sw", door1);
        Tiles[1][0]->attach("we", door1);
        Tiles[2][0]->attach("nw", door1);
        Tiles[3][3]->attach("se", door2);
        Tiles[3][4]->attach("so", door2);
        Tiles[3][5]->attach("sw", door2);
        Tiles[7][22]->attach("sw", door3);
        Tiles[8][22]->attach("we", door3);
        Tiles[9][22]->attach("nw", door3);
        Tiles[9][29]->attach("se", door4);
        Tiles[9][30]->attach("so", door4);
        Tiles[9][31]->attach("sw", door4);
     } else if (num == 2) {
        Tiles[0][4]->attach("ne", door1);
        Tiles[0][5]->attach("no", door1);
        Tiles[0][6]->attach("nw", door1);
        Tiles[2][4]->attach("se", door2);
        Tiles[2][5]->attach("so", door2);
        Tiles[2][6]->attach("sw", door2);
     } else if (num == 3) {
        Tiles[0][8]->attach("ne", door1);
        Tiles[0][9]->attach("no", door1);
        Tiles[0][10]->attach("nw", door1);
        Tiles[4][20]->attach("se", door2);
        Tiles[5][20]->attach("ea", door2);
        Tiles[6][20]->attach("ne", door2);
     } else {
        Tiles[0][31]->attach("ne", door1);
        Tiles[0][32]->attach("no", door1);
        Tiles[0][33]->attach("nw", door1);
        Tiles[3][5]->attach("ne", door2);
        Tiles[3][6]->attach("no", door2);
        Tiles[3][7]->attach("nw", door2);
        Tiles[3][0]->attach("sw", door3);
        Tiles[4][0]->attach("we", door3);
        Tiles[5][0]->attach("nw", door3);
     }
     for (int a = 0; a < row; ++a) {
         for (int b = 0; b < col; ++b) {
			 if(Tiles[a][b] != nullptr) {
				 if(Tiles[a][b]->getCharacter()) {
					 if(Tiles[a][b]->getCharacter()->getName() == "dragon") {
						 map<string, Cell *> myMap = Tiles[a][b]->getNeighbors();
						 for(auto p : myMap) {
							 if(p.second->getName().substr(0,4) == "gold") {
								Tiles[a][b]->getCharacter()->setHoard(p.second);
								p.second->setLinked();
								continue;
							 }
						 }
					 }
				 }
			 }
		 }
	 }
}

Chamber::~Chamber() {
     for (int i = 0; i < row; ++i) {
          for (int j = 0; j < col; ++j) {
              delete Tiles[i][j];
          }
          Tiles[i].clear();
     }
     Tiles.clear();
     for (unsigned int k = 0; k < Enemies.size(); ++k) {
         delete Enemies[k];
     }
     Enemies.clear();
}

int Chamber::getNum() {
    return num;
}

int Chamber::getRow() {
    return row;
}

int Chamber::getCol() {
    return col;
}

int Chamber::getGlobStarX() {
    return globStarX;
}

int Chamber::getGlobStarY() {
    return globStarY;
}

int Chamber::getTotal() {
    return total;
}

Cell *Chamber::getCell(int row, int col) {
    return Tiles[row][col];
}

void Chamber::addEm(Enemy *em) {
     Enemies.push_back(em);
}

void Chamber::setCell(int row, int col, Cell *cell){
	Tiles[row][col] = cell;
}

// sets all enemies acted to val
void Chamber::enemiesActed(bool val){
    for(auto enemy : Enemies){
        enemy->setActed(val);
    }
}

// all the enemies will look for a player to attack
void Chamber::enemiesAttack(){
    for(auto enemy : Enemies){
        if (!enemy->getActed()){
            Cell *enemyTile = enemy->getPosn();
            enemyTile->notifyObservers();
        }
    }
}


void Chamber::resetAct() {
     for (unsigned int i = 0; i < Enemies.size(); ++i) {
         Enemies[i]->setActed(false);
     }
}

void Chamber::setMarchantMad(){
	int total = Enemies.size();
	for(int i = 0; i < total; ++i) {
		if(Enemies[i]->getName() == "merchant") {
			Enemies[i]->setHostility(true);
		}
	}
	
}

void Chamber::moveEm() {
    for (unsigned int i = 0; i < Enemies.size(); ++i) {
        if ((Enemies[i]->getName() != "dragon") && (Enemies[i]->getName() != "dead") && (!Enemies[i]->getActed())) {
			Enemies[i]->setActed(true);
     	  	Cell *curEnemy = Enemies[i]->getPosn();
			vector<Cell *> possibleMove = curEnemy->validNeighbors();
			int moveNum = possibleMove.size();
			if(moveNum == 0) {
				//continue;
			} else {
				int randNum = rand() %moveNum;
				Cell * newEnemyPosn = possibleMove[randNum];
				curEnemy->setCharacter(nullptr);
				newEnemyPosn ->setCharacter(Enemies[i]);
				curEnemy ->setName("tile");
				newEnemyPosn ->setName("enemy");
				Enemies[i]->setPosn(newEnemyPosn);
				curEnemy ->setMovable(true);
				curEnemy ->setOccupied(false);
				newEnemyPosn ->setMovable(false);
				newEnemyPosn ->setOccupied(true);
				curEnemy->notifyObservers();
				newEnemyPosn ->notifyObservers();
			}
        }
    }
}
