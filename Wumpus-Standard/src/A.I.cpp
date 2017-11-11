#include "../include/Wumpus.h"

int main(void)
{

	Map map(10,10);

	Wumpus wumpus(map);

	wumpus.elaborateStrategy(map);
	//sleep(1);
	initscr();
	sleep(1);
	while (1) {
		wumpus.Update(map);
		map.DisplayMap();
		wumpus.applyStrategy(map);
		wumpus.Update(map);
		sleep(1);
		printw("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		wumpus.Update(map);
		wumpus.AI_Verification(map);
		wumpus.Update(map);

	}

}
