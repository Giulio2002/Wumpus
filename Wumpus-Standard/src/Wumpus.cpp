#include "../include/Wumpus.h"
//First Constructor
Wumpus::Wumpus(Map & map)
{

	//default spritesheet
	spritesheet[0] = '^';
	spritesheet[1] = '<';
	spritesheet[2] = '>';
	//default initial sprite
	currentsprite = '<';
	//setup axis
	x = 0;
	y = 0;
	//put the wumpus in the map  and make his first cell empty
	if (map.getCell(0, 0).getType() == Treasure) {
		//if the wumpus is on the treasure we will fix this
		map.ChangeCell(1, 0, currentsprite);

		map.getCell(x, y).setType(empty);

		//setup axis
		x = 1;
		y = 0;

	} else {
		//put the wumpus in the map  and make his first cell empty
		map.ChangeCell(0, 0, currentsprite);

		map.getCell(x, y).setType(empty);
	}

}

Wumpus::Wumpus(char _spritesheet[], Map & map)
{
	//setup the selected spritesheet
	for (int i = 0; i < MAXSPRITE; i++)

		spritesheet[1] = _spritesheet[i];
	//currentsprite is always equal to the first spritesheet element
	currentsprite = spritesheet[0];
	//setup axis
	x = 0;
	y = 0;
	//put in the map the wumpus
	if (map.getCell(0, 0).getType() == Treasure) {
		//if the wumpus is on the treasure we will fix this
		map.ChangeCell(1, 0, currentsprite);

		map.getCell(x, y).setType(empty);
		//setup axis
		x = y;
		y = 0;

	} else {

		map.ChangeCell(0, 0, currentsprite);

		map.getCell(x, y).setType(empty);

	}
}

void
Wumpus::Update(Map & map)
{
	//make his last cell empty
	map.ChangeCell(LastCell[0], LastCell[1], ' ');

	//and we update his position
	map.ChangeCell(x, y, currentsprite);

}
int Wumpus::AI_Verification(Map & map){


	if(map.getCell(x+1,y).getType() == Treasure ||
		map.getCell(x-1,y).getType() == Treasure ||
		map.getCell(x,y+1).getType() == Treasure ||
		map.getCell(x,y-1).getType() == Treasure){
		Update(map);
		map.DisplayMap();
		sleep(3);
		endwin();

		std::cout << "YOU WIN\n";

		exit(1);

	}else return 1;

	return 0;

}

//this function implement the movements made by user
void Wumpus::wantToMove(Map & map)
{
	//we record LastCell
	LastCell[0] = x;
	LastCell[1] = y;
	//ncurses settings
	cbreak();

	noecho();

	nodelay(stdscr, TRUE);

	scrollok(stdscr, TRUE);
	//we detect key press
	int ch = getch();
	//we see all case
	switch (ch) {
	case 119:		// this is w button
		//we change currentsprite
		setCurrentSprite(spritesheet[0]);
		//if is touching the border
		if (x == 0)
			return;
		//if he wants to move on an occupied cell
		if (map.getCell(x - 1, y).getType() == occupied)
			return;
		//if he wants to move on a dangerous cell
		if (map.getCell(x - 1, y).getType() == dangerous) {
			//lose conditions
			endwin();

			std::cout << "YOU LOSE\n";

			exit(1);
		}
		//if he won
		if (map.getCell(x - 1, y).getType() == Treasure) {
			//Victory condition
			endwin();

			std::cout << "YOU WIN\n";

			exit(1);
		}
		//change position
		x--;

		break;

	case 97:		//a
		//we change currentsprite
		setCurrentSprite(spritesheet[1]);
		//if is touching the border
		if (y == 0)
			return;
		//if he wants to move on an occupied cell
		if (map.getCell(x, y - 1).getType() == occupied)
			return;
		//if he wants to move on a dangerous cell
		if (map.getCell(x, y - 1).getType() == dangerous) {
			//lose conditions
			endwin();

			std::cout << "YOU LOSE\n";

			exit(1);

		}
		//win conditions
		if (map.getCell(x, y - 1).getType() == Treasure) {
			//Victory condition
			endwin();

			std::cout << "YOU WIN\n";

			exit(1);

		}
		//change position
		y--;

		break;

	case 115:		//this is button s
		//if is touching the border
		if (x == map.getxDim() - 1)
			return;
		//if he wants to move on an occupied cell
		if (map.getCell(x + 1, y).getType() == occupied)
			return;
		//if he wants to move on a dangerous cell
		if (map.getCell(x + 1, y).getType() == dangerous) {
			//lose conditions
			endwin();

			std::cout << "YOU LOSE\n";

			exit(1);

		}
		//win conditions
		if (map.getCell(x + 1, y).getType() == Treasure) {
			//Victory condition
			endwin();

			std::cout << "YOU WIN\n";

			exit(1);
		}
		//change position
		x++;

		break;
	case 100:		//d
		//we change currentsprite
		setCurrentSprite(spritesheet[2]);
		//if is touching the border
		if (y == map.getyDim() - 1)
			return;
		//if he wants to move on an occupied cell
		if (map.getCell(x, y + 1).getType() == dangerous) {
			//lose conditions
			endwin();

			std::cout << "YOU LOSE\n";

			exit(1);

		}
		//if he wants to move on an occupied cell
		if (map.getCell(x, y + 1).getType() == occupied)
			return;
		//win conditions
		if (map.getCell(x, y + 1).getType() == Treasure) {
			//Victory condition
			endwin();

			std::cout << "YOU WIN\n";

			exit(1);
		}
		//change position
		y++;
		break;

	}
}

//we check his current sprite
char Wumpus::getCurrentSprite()
{

	return currentsprite;

}

//we set his current sprite
void Wumpus::setCurrentSprite(char _new)
{
	currentsprite = _new;

}

int Wumpus::calculate_cost(cellPair _cell, std::vector<cellPair> & close){

	cellPair currentPair;

	currentPair = _cell;

	int totalcost = currentPair.candidateCell.cost;

	for(int i = 0;i<close.size();i++)

		if(close[i].candidateCell.x == currentPair.previousCell.x &&

				close[i].candidateCell.y == currentPair.previousCell.y	)

			totalcost += close[i].cost;

	return totalcost;

}


bool isClosed(cellPair _cell, std::vector<cellPair> & close){

	for(int i = 0;i<close.size();i++)
		if(close[i].candidateCell.x == _cell.candidateCell.x &&
			close[i].candidateCell.y == _cell.candidateCell.y)
				return true;
	return false;
}

bool Wumpus::elaborateStrategy(Map & map)
{

	//initial setup
	int currPoint = 1;
	int totalcost = 0;
	std::vector<cellPair > open;
	std::vector<cellPair > close;

	cellPair Start;

	Start.previousCell = map.getCell(0,0);
	Start.candidateCell = map.getCell(0,0);
	Start.cost = 0;
	open.clear();
	close.clear();
	open.push_back(Start);
	std::vector<cellPair > temp;
	temp.push_back(Start);
	std::cout << "-----PROGRAM INFO-------" << std::endl;



	while(open.size() != 0){
		std::cout << "1" << std::endl;

		std::cout << "open size: "<< open.size() << std::endl;

		//we search the best solution
		int index = 0;

		int candidate_cost = open[0].candidateCell.cost;

		for(int i = 1; i < open.size() ; i++){
			if(open[i].candidateCell.cost < candidate_cost){

				open[i].cost = calculate_cost(open[i-1],close);

				candidate_cost = open[i-1].candidateCell.cost;
				//std::cout << open[i].cost << std::endl;
				//TODO DEBUG
				index = i;

			}

		}
		//std::cout << "a" << std::endl;
		if(isClosed(open[index],close)){
			open.erase(open.begin() + index);
			continue;
		}
		else
		close.push_back(open[index]);
		bool Found = false;
		//we try add the possible solution
		cellPair tmp;
		for(int i = 0;i<open[index].candidateCell.LinkedCells.size();i++){
			for(int j = 0; j < open.size(); j++){
				Found = false;
				//std::cout << open[j].candidateCell.x << " "<< open[j].candidateCell.LinkedCells[i]->x<< std::endl;
				if(open[index].candidateCell.LinkedCells[i]->x == open[j].candidateCell.x &&
						open[index].candidateCell.LinkedCells[i]->y == open[j].candidateCell.y){
					Found = true;

					tmp.previousCell = open[index].candidateCell;

					tmp.candidateCell.x = open[index].candidateCell.LinkedCells[i]->x;

					tmp.candidateCell.y = open[index].candidateCell.LinkedCells[i]->y;

					tmp.candidateCell.cost = open[index].candidateCell.LinkedCells[i]->cost;

					tmp.cost = calculate_cost(tmp,close);

					if(tmp.cost < open[j].cost){

						open.push_back(tmp);

					}
					break;
				}



			}
			if(!Found){
				tmp.previousCell = open[index].candidateCell;
				tmp.candidateCell = *open[index].candidateCell.LinkedCells[i];
				tmp.cost = calculate_cost(tmp,close);
				open.push_back(tmp);
			}
		}
		//TODO DEBUG

		//we transfer open[index] from open to close
		//erase should delete correctly our cellPair
		std::cout << open[index].candidateCell.getSymbol() << std::endl;
		int Tx = map.getXTreasure();
		int Ty = map.getYTreasure();

		open.erase(open.begin() + index);
	}

	std::cout << "Exit from first cycle" << std::endl;
	std::vector<cellPair> reverse;

	std::vector<cellPair> straight;
	int xGoal = map.getXTreasure();
	int yGoal = map.getYTreasure();

	reverse.clear();

	straight.clear();
	cellPair treasure;

	treasure.candidateCell = map.getCell(xGoal,yGoal);

	for(int i = 0;i<close.size();i++){

		treasure.candidateCell = map.getCell(xGoal,yGoal);

		if(close[i].candidateCell.x == treasure.candidateCell.x
				&& close[i].candidateCell.y == treasure.candidateCell.y){
			treasure = close[i];
			treasure.candidateCell = map.getCell(map.getXTreasure(),map.getYTreasure());
			break;
		}

	}
	reverse.push_back(treasure);

	cellPair curr = reverse.back();
	int Fx = reverse.back().candidateCell.x;
	int Fy = reverse.back().candidateCell.y;
	while(Fx != 0 || Fy != 0){

		for(int i = 0;i<close.size();i++){

			if(close[i].candidateCell.x == curr.previousCell.x &&

					close[i].candidateCell.y == curr.previousCell.y){

				curr = close[i];
				//std::cout << "Entro";
				reverse.push_back(close[i]);

				break;
			}
		}
		Fx = reverse.back().candidateCell.x;
		Fy = reverse.back().candidateCell.y;
	}
	std::cout << "reverse size: "<< reverse.size() << std::endl;
	std::cout << "open size: "<< open.size() << std::endl;
	std::cout << "close size: "<< close.size() << std::endl;
	std::cout << std::endl << "----LOG-----" << std::endl;

	int xLastCandidate = 0;
	int yLastCandidate = 0;

	int currIndex = 0;
	StrategyIndex = 0;

	for(int i = reverse.size() -1;i>0;i--){

		straight.push_back(reverse[i]);

	}
	straight.push_back(treasure);

	straight.erase(straight.begin() + 0);

	cellPair currentCell = straight[0];

	for(int i = 0;i<straight.size();i++){
		currentCell = straight[i];
		StrategyLog[i] = 0;

		if(currentCell.candidateCell.x > currentCell.previousCell.x){

			StrategyLog[i] = 0;

			std::cout << i << ' ' <<  StrategyLog[i] << std::endl;

		}else if(currentCell.candidateCell.x < currentCell.previousCell.x){

			StrategyLog[i] = 1;

			std::cout << i << ' ' <<  StrategyLog[i] << std::endl;

		}else if(currentCell.candidateCell.y > currentCell.previousCell.y){

			StrategyLog[i] = 2;

			std::cout << i << ' ' <<  StrategyLog[i] << std::endl;

		}else if(currentCell.candidateCell.y < currentCell.previousCell.y){

			StrategyLog[i] = 3;

			std::cout << i << ' ' <<  StrategyLog[i] << std::endl;

		}

	}


	return true;

}

//there is a bug maybe in righ and left case
void Wumpus::applyStrategy(Map & map)
{

	//we record LastCell
	//we record LastCell
	LastCell[0] = x;
	LastCell[1] = y;
	//ncurses settings
	cbreak();

	noecho();

	nodelay(stdscr, TRUE);

	scrollok(stdscr, TRUE);
	//we detect key press
	int ch = getch();
	//we see all case of movements considering StrategyLog
	switch (StrategyLog[StrategyIndex]) {
	case 1:		//up
		//we change currentsprite
		setCurrentSprite(spritesheet[0]);
		//if is touching the border
		if (x == 0) {
			return;
			StrategyIndex++;
		}
		//if he wants to move on an occupied cell
		if (map.getCell(x - 1, y).getType() == occupied) {
			return;
			StrategyIndex++;
		}
		//if he wants to move on a dangerous cell
		if (map.getCell(x, y).getType() == dangerous) {
			//lose conditions
			endwin();

			std::cout << "YOU LOSE\n";

			exit(1);
		}
		//if he won
		if (map.getCell(x, y).getType() == Treasure) {
			//Victory condition
			endwin();

			std::cout << "YOU WIN\n";

			exit(1);
		}
		//change position
		x--;

		break;

	case 3:		//left
		//we change currentsprite
		setCurrentSprite(spritesheet[1]);
		//if is touching the border
		if (y == 0) {
			return;
			StrategyIndex++;
		}
		//if he wants to move on an occupied cell
		if (map.getCell(x, y - 1).getType() == occupied) {
			StrategyIndex++;
			return;
		}
		//if he wants to move on a dangerous cell
		if (map.getCell(x, y).getType() == dangerous) {
			//lose conditions
			endwin();

			std::cout << "YOU LOSE\n";

			exit(1);

		}
		//win conditions
		if (map.getCell(x, y).getType() == Treasure) {
			//Victory condition
			endwin();

			std::cout << "YOU WIN\n";

			exit(1);

		}
		//change position
		y--;

		break;

	case 0:		//down
		//if is touching the border
		if (x == map.getxDim() - 1) {
			return;
			StrategyIndex++;
		}
		//if he wants to move on an occupied cell
		if (map.getCell(x + 1, y).getType() == occupied) {
			StrategyIndex++;
			return;
		}
		//if he wants to move on a dangerous cell
		if (map.getCell(x, y).getType() == dangerous) {
			//lose conditions
			endwin();

			std::cout << "YOU LOSE\n";

			exit(1);

		}
		//win conditions
		if (map.getCell(x, y).getType() == Treasure) {
			//Victory condition
			endwin();

			std::cout << "YOU WIN\n";

			exit(1);
		}
		//change position
		x++;

		break;
	case 2:		//right
		//we change currentsprite
		setCurrentSprite(spritesheet[2]);
		//if is touching the border
		if (y == map.getyDim()) {
			StrategyIndex++;
			return;
		}
		//if he wants to move on an occupied cell
		if (map.getCell(x, y).getType() == dangerous) {
			//lose conditions
			endwin();

			std::cout << "YOU LOSE\n";

			exit(1);

		}
		//if he wants to move on an occupied cell
		if (map.getCell(x, y + 1).getType() == occupied) {
			StrategyIndex++;
			return;
		}
		//win conditions
		if (map.getCell(x, y).getType() == Treasure) {
			//Victory condition
			endwin();

			std::cout << "YOU WIN\n";

			exit(1);
		}
		//change position
		y++;
		break;

	}
	StrategyIndex++;

}

/*
0   down
1   up
2   right >
3   left <
 */
