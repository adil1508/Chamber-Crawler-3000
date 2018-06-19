CXX=g++-5
CXXFLAGS=-std=c++14 -Wall -MMD
OBJECTS=boostAtk.o boostDef.o cell.o chamber.o character.o decoratedTile.o enemy.o floor.o gold.o mainProg.o other.o player.o poisonHealth.o potion.o restoreHealth.o textdisplay.o tile.o woundAtk.o woundDef.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=cc3k

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm *.o *.d cc3k
.PHONY: clean
