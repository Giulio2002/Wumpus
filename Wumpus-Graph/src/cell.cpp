/* Definitions of cell's functions*/

//script
#include "../include/cell.h"

//default constructor
cell::cell()
{
//set everythin to default value(empty and " ")
	cost = 0;

	type = empty;

	symbol = ' ';

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

char cell::getSymbol()
{

	return symbol;

}

void cell::setType(cellType _newtype)
{
	type = _newtype;
//this switch set the right symbol considering type value
	switch (type) {
	case empty:
		cost = -9999;
		symbol = ' ';

		break;

	case occupied:
		cost = -1;
		symbol = '-';

		break;

	case dangerous:
		cost = -1;
		symbol = '*';

		break;

	case muddy:
		cost = -5000;
		symbol = '~';

		break;

	case Treasure:

		symbol = '#';

		break;
	default:
		cost = -1;
		symbol = ' ';

		type = empty;

		break;

	}

}

void cell::setSymbol(char _new)
{
	symbol = _new;

}
