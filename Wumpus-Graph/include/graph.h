#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <string>
#include <thread>


struct Point{
	int x;

	int y;

};

class Graph{
	public:

		Graph();

		void displayGraph(SDL_Surface * surf);

		bool insertPoint(Point);

	private:


		std::vector<Point> Points;

		SDL_Surface *BackGround;

		SDL_Surface * point;

};
