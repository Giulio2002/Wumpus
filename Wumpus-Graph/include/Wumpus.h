#include "Map.h"
#include <ncurses.h>
#include <unistd.h>  /* only for sleep() */
#include <stdio.h>
#include <ncurses.h>
#include <vector>
#include <utility>
#define MAXSPRITE 4
//player class
class Wumpus{

  public:
      int StrategyLog [MAX * MAX];

      //coordinations in axis
      int x;

      int y;
      //constructors (they needs the map on which the wumpus will be created)
      Wumpus(Map & );

      Wumpus(char [],Map &);
      //Movements by hand
      void wantToMove(Map &);
      //Update the wumpus position
      void Update(Map &);
      void AIUpdate(Map &);

      //get the current sprite see constructors
      char getCurrentSprite();
      //set the current spritesheet
      void setCurrentSprite(char);

      bool elaborateStrategy(Map &);

      int AI_Verification(Map &);

      void applyStrategy(Map &);

    private:

      int calculate_cost(cellPair, std::vector<cellPair> & close);
      //Last Position
      int LastCell[2];
      //our spritesheet
      char spritesheet[MAXSPRITE];
      //the current sprite
      char currentsprite;


      int StrategyIndex;
};
