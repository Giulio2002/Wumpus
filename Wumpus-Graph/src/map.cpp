/* map's functions Definitions*/

#include "../include/Map.h"
//constructor
Map::Map(int _xDim, int _yDim)
{
//create the map with sizes of maps
	Build(_xDim, _yDim);
}

//constructor
Map::Map(std::string _FILEPATH)
{
//create tmp variables
	int Xtmp = 0;

	int Ytmp = 0;

	std::string Word;

	std::fstream file;
//open the selected file
	file.open(_FILEPATH.c_str());
//this is equal to our current characters
	char current_char;

//if the file was found
	if (file.is_open()) {
//count horizzontal cell
		while (file.get(current_char)) {

			if (current_char == 'X') {
				break;
			}
			Ytmp++;
		}
//count vertical cell
		while (std::getline(file, Word)) {

			Xtmp++;

		}
//setup dimensions
		Xtmp--;

		xDim = Xtmp;

		yDim = Ytmp;
//make tmps equal to default values
		Xtmp = 0;
		Ytmp = 0;
//create a new fstream
		std::fstream file_002;
		file_002.open(_FILEPATH.c_str());

		while (file_002.get(current_char)) {

			if (current_char != 'X') {
//read the map
				map[Xtmp - 1][Ytmp -1].setType(SwitchConditions(current_char));
				map[Xtmp - 1][Ytmp -1].x = Xtmp-1;
				map[Xtmp - 1][Ytmp -1].y = Ytmp-1;

//save Treasure position
				if (SwitchConditions(current_char) == Treasure) {
					XTreasure = Xtmp;
					YTreasure = Ytmp;
				}
//update axis
				Ytmp++;
//end of line
				Ytmp = 0;
				Xtmp++;
			}
		}

//we open it
}





}

//display the map
void Map::DisplayMap()
{
//Display process
	for (int x = 0; x < xDim; x++) {

		for (int y = 0; y < yDim; y++) {
//Display current cell's symbol
			printw("%c", map[x][y].getSymbol());

		}
//go to the next the line
		printw("\n");
	}

}

void Map::Build(int _xDim, int _yDim)
{
//dimension setup
	yDim = _yDim;
	xDim = _xDim;
//throw exceptions
	if (xDim > MAX) {
		std::
		    cout << "ERROR The limit is 256 yDim setted to 256" << std::
		    endl;
		std::cout << "to Prevent core dump" << std::endl;
		xDim = MAX;
	}
	if (yDim > MAX) {
		std::
		    cout << "ERROR The limit is 256 xDim setted to 256" << std::
		    endl;
		std::cout << "to Prevent core dump" << std::endl;
		yDim = MAX;

	}

//initialize random numbers
	srand(time(NULL));
//create the map
	for (int x = 0; x < yDim + 1; x++) {

		for (int y = 0; y < xDim + 1; y++) {
//with random numbers generator
			cellType tmp = (cellType) (rand() % DIFFICULT);
			if (tmp != Treasure){
				map[y][x].setType(tmp);
				map[y][x].y = x ;
				map[y][x].x = y ;
					if(x < xDim && ( map[y][x+1].getType() == empty || map[y][x+1].getType() == muddy) )

						map[y][x].LinkedCells.push_back(&map[y][x+1]);

					if(y < yDim && ( map[y+1][x].getType() == empty || map[y+1][x].getType() == muddy))

						map[y][x].LinkedCells.push_back(&map[y+1][x]);

					if(y > 0 && ( map[y-1][x].getType() == empty || map[y-1][x].getType() == muddy))

						map[y][x].LinkedCells.push_back(&map[y-1][x]);

					if(x > 0 && ( map[y][x-1].getType() == empty || map[y][x-1].getType() == muddy))

						map[y][x].LinkedCells.push_back(&map[y][x-1]);

			}
		}
	}
//create randomly the goal and set the treasure positin
	XTreasure = rand() % yDim;

	YTreasure = rand() % yDim;

	map[XTreasure++][YTreasure].setType(Treasure);

}

//return the x size
int Map::getxDim()
{
	return xDim;

};

//set x size
bool Map::setxDim(int _new)
{
//exception
	if (_new > MAX)
		return false;

	xDim = _new;
//recreate the map
	Build(xDim, yDim);
//return true
	return true;
};

//return y size
int Map::getyDim()
{

	return yDim;

};

//same thing of setxDim
bool Map::setyDim(int _new)
{

	if (_new > MAX)
		return false;

	yDim = _new;

	Build(xDim, yDim);

	return true;

};

//this change the symbol of one of the map's cell
bool Map::ChangeCell(int x, int y, char _new)
{
	if (x > xDim || y > yDim)
		return false;
	map[x][y].setSymbol(_new);
	return true;

}

//get a specific cell
cell Map::getCell(int x, int y)
{
	return map[x][y];

}

//say to what symbol the given char is equal to
cellType Map::SwitchConditions(char _object)
{

	switch (_object) {

	case '-':

		return occupied;

	case '*':

		return dangerous;

	case '~':

		return muddy;

	case '#':

		return Treasure;

	default:

		return empty;
	}

	return empty;

}

//get the treasure position
int Map::getXTreasure()
{

	return XTreasure;

}

int Map::getYTreasure()
{

	return YTreasure;

}
