#include "../include/Wumpus.h"


int main(void)
{
    initscr();
    std::string file = "Map";
    Map map(file);
    Wumpus wumpus(map);
     while(1){
       printw("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
       map.DisplayMap();
        wumpus.wantToMove(map);
        wumpus.Update(map);
     }
  }
