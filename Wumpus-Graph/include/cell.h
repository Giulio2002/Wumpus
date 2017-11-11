/*cell script*/
//dependencies
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <float.h>

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
		char getSymbol();

		void setSymbol(char);

	private:

		//cell's type
		cellType type;
		//current symbol
		char symbol;




};
struct cellPair{

	cell previousCell;

	cell candidateCell;

	int cost;

};
