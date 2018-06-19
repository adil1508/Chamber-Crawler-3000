#include "textdisplay.h"
#include "cell.h"
using namespace std;

TextDisplay::TextDisplay(int row, int col, string content) : row{row}, col{col} { 
      char cur;
      if (content == "") { 
         content = "|-----------------------------------------------------------------------------||                                                                             || |--------------------------|        |-----------------------|               || |..........................|        |.......................|               || |..........................+########+.......................|-------|       || |..........................|   #    |...............................|--|    || |..........................|   #    |..................................|--| || |----------+---------------|   #    |----+----------------|...............| ||            #                 #############                |...............| ||            #                 #     |-----+------|         |...............| ||            #                 #     |............|         |...............| ||            ###################     |............|   ######+...............| ||            #                 #     |............|   #     |...............| ||            #                 #     |-----+------|   #     |--------+------| ||  |---------+-----------|     #           #          #              #        ||  |.....................|     #           #          #         |----+------| ||  |.....................|     ########################         |...........| ||  |.....................|     #           #                    |...........| ||  |.....................|     #    |------+--------------------|...........| ||  |.....................|     #    |.......................................| ||  |.....................+##########+.......................................| ||  |.....................|          |.......................................| ||  |---------------------|          |---------------------------------------| ||                                                                             ||-----------------------------------------------------------------------------|";
      }  
      istringstream ss{content};
      for (int i = 0; i < row; ++i) {
          vector<char> rowOfCh(col);
          for (int j = 0; j < col; ++j) {
              if (ss >> noskipws >> cur) {
                 rowOfCh[j] = cur;
              }
          }     
          theDisplay.emplace_back(rowOfCh);
      }
}

TextDisplay::~TextDisplay() {
       for (int i = 0; i < row; ++i) {
           theDisplay[i].clear();
       }
       theDisplay.clear();
}

void TextDisplay::notify(Cell &whoNotified) {
     if (whoNotified.getName() == "potion") {
        theDisplay[whoNotified.getX()][whoNotified.getY()] = 'P';
     } else if (whoNotified.getName().substr(0, 4) == "gold") {
        theDisplay[whoNotified.getX()][whoNotified.getY()] = 'G';
     } else if (whoNotified.getName().substr(0, 6) == "player") {
        theDisplay[whoNotified.getX()][whoNotified.getY()] = '@';
     } else if (whoNotified.getName() == "tile") {
        theDisplay[whoNotified.getX()][whoNotified.getY()] = '.';
     } else if (whoNotified.getName() == "stairs") {
        theDisplay[whoNotified.getX()][whoNotified.getY()] = '\\';
     } else if (whoNotified.getName() == "door") {
        theDisplay[whoNotified.getX()][whoNotified.getY()] = '+';
     } else if (whoNotified.getName() == "path") {
        theDisplay[whoNotified.getX()][whoNotified.getY()] = '#';
     }  else if (whoNotified.getName() == "enemy"){
        if (whoNotified.getCharacter()->getName() == "dragon") {
           theDisplay[whoNotified.getX()][whoNotified.getY()] = 'D';
        } else if (whoNotified.getCharacter()->getName() == "merchant") {
           theDisplay[whoNotified.getX()][whoNotified.getY()] = 'M';
        } else if (whoNotified.getCharacter()->getName() == "human") {
           theDisplay[whoNotified.getX()][whoNotified.getY()] = 'H';
        } else if (whoNotified.getCharacter()->getName() == "dwarf") {
           theDisplay[whoNotified.getX()][whoNotified.getY()] = 'W';
        } else if (whoNotified.getCharacter()->getName() == "elf") {
           theDisplay[whoNotified.getX()][whoNotified.getY()] = 'E';
        } else if (whoNotified.getCharacter()->getName() == "orcs") {
           theDisplay[whoNotified.getX()][whoNotified.getY()] = 'O';
        } else {
           theDisplay[whoNotified.getX()][whoNotified.getY()] = 'L';
        }
    }
}

char TextDisplay::getSymbol(int x, int y) {
     return theDisplay[x][y];
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
      for (int i = 0; i < td.row; ++i) {
           for (int j = 0; j < td.col; ++j) {
               out << td.theDisplay[i][j];
           }
           out << endl;
      }
      return out;
}
