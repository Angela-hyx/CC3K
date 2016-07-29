CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = cc3k 
MAINOBJ = main.o
FLOOROBJ = floor.o chamber.o
CHAROBJ = character.o player.o enemy.o
PLAYEROBJ = player/orc.o player/human.o player/elves.o player/dwarf.o player/student.o 
ENEMYOBJ = enemy/midterm.o enemy/dragon.o enemy/goblin.o enemy/merchant.o enemy/phoenix.o enemy/troll.o enemy/vampire.o enemy/werewolf.o
ITEMOBJ = item.o item/gold.o item/potion.o
OBJECTS = ${MAINOBJ} ${FLOOROBJ} ${CHAROBJ} ${PLAYEROBJ} ${ENEMYOBJ} ${ITEMOBJ}
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
		${CXX} ${CXXFLAGS} -g ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
		rm ${OBJECTS} ${EXEC} ${DEPENDS}
