CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = cc3k
OBJECTS = main.o controller.o textdisplay.o floor.o object.o chamber.o character.o player.o enemy.o gold.o potion.o shade.o dragon.o human.o decorator.o potioneffect.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
