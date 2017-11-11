/* Definitions of cell's functions*/

//script
#include "../include/cell.h"

//default constructor
cell::cell()
{
//set everythin to default value(empty and " ")
	cost = 0;

	type = empty;

	symbol = NULL;


}

//optional constructur for optional initial type
cell::cell(cellType _type)
{
	cost = 0;

	setType(_type);
}

//get and set functions...
cellType cell::getType()
{

	return type;

}

SDL_Surface * cell::getSymbol()
{

	return symbol;

}
void cell::blitCell(SDL_Surface * surf){
	SDL_Rect pox;

	pox.x = x * 50;

	pox.y = y * 50;

	SDL_BlitSurface(symbol,NULL,surf,&pox);

}
void cell::setType(cellType _newtype)
{
	type = _newtype;
//this switch set the right symbol considering type value
	switch (type) {
	case empty:
		cost = -9999;
		symbol = NULL;

		break;

	case occupied:
		cost = -1;
		symbol = SDL_LoadBMP("img/occupied.bmp");

		break;

	case dangerous:

		cost = -1;

		symbol = SDL_LoadBMP("img/dangerous.bmp");

		break;

	case muddy:
		cost = -5000;
		symbol = SDL_LoadBMP("img/Muddy.bmp");

		break;

	case Treasure:

		symbol = SDL_LoadBMP("img/Treasure.bmp");

		break;
	default:
		cost = -1;

		symbol = NULL;

		type = empty;

		break;

	}

}

void cell::setSymbol(SDL_Surface * _new)
{
	symbol = _new;

}
