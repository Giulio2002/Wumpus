#include "map.h"
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

      Wumpus(SDL_Surface * [],Map &);
      //Movements by hand
      void wantToMove(Map &,int ch);
      //Update the wumpus position
      void Update(Map &);
      void AIUpdate(Map &);

      //get the current sprite see constructors
      SDL_Surface * getCurrentSprite();
      //set the current spritesheet
      void setCurrentSprite(SDL_Surface *);

      bool elaborateStrategy(Map &);

      int AI_Verification(Map &,SDL_Surface *);

      void applyStrategy(Map &);

    private:

      int calculate_cost(cellPair, std::vector<cellPair> & close);
      //Last Position
      int LastCell[2];
      //our spritesheet
      SDL_Surface * spritesheet[MAXSPRITE];
      //the current sprite
      SDL_Surface * currentsprite;


      int StrategyIndex;
};
