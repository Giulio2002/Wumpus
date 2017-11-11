#include <SDL2/SDL.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <float.h>
#include <iostream>
#include <thread>
#define MAPSIZE 500
#define CELLSIZE 50


//this enum create type of cells type
enum cellType{empty,occupied,dangerous,muddy,Treasure};
//the cell's class
class cell{

	public:

		int x;

		int y;

		std::vector<cell *> LinkedCells;

		int cost;

		//constructors
		cell();

		cell(cellType);

		//gets and sets functions
		//this return the cell's type
		cellType getType();
		//this enable the opportunity yo change the cell's type
		void setType(cellType);
		//this get the current symbol
		SDL_Surface * getSymbol();

		void setSymbol(SDL_Surface *);

		void blitCell(SDL_Surface *);

	private:

		//cell's type
		cellType type;
		//current symbol
		SDL_Surface *symbol;

};
struct cellPair{

	cell previousCell;

	cell candidateCell;

	int cost;

};
