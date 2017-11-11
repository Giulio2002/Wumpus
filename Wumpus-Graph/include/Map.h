/*map's script*/

//dependencies
#include "cell.h"
#include <fstream>
#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>
#include <string>
#define DIFFICULT 20
//max value of the stack
#define MAX 256
//Map's class
class Map{

  public:
    //constructor
    Map(int,int);

    Map(std::string);
    //Display the created Map
    void DisplayMap();
    //gets and sets...
    int getxDim();

    bool setxDim(int);

    int getyDim();

    bool setyDim(int);

    int  getXTreasure();

    int  getYTreasure();

    bool ChangeCell(int,int,char);

    cell getCell(int,int);

    void Build(int,int);

  private:


    cellType SwitchConditions(char);
    //map dimensions
    int yDim;
    int xDim;

    int XTreasure;

    int YTreasure;
    //map
    cell map[MAX][MAX];



};
