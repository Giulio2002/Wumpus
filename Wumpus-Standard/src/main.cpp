#include "../include/Wumpus.h"

int main(void)
{

    Map map(10,10);
    Wumpus wumpus(map);
    initscr();
      while(1){
        printw("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        map.DisplayMap();
        wumpus.wantToMove(map);
        wumpus.Update(map);

      }

}
