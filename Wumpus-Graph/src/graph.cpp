#include "../include/graph.h"

Graph::Graph(){

	BackGround = SDL_LoadBMP("img/BackGround.bmp");

	point = SDL_LoadBMP("img/Point.bmp");

	Point p;

	p.x = 0;

	p.y = 0;

	Points.push_back(p);
}


void Graph::displayGraph(SDL_Surface * surf){

	SDL_BlitSurface(BackGround,NULL,surf,NULL);

	for(int i = 0;i<Points.size()-1;i++){

		SDL_Rect position;

		position.x = Points[i+1].x;

		position.y = Points[i+1].y;

		SDL_BlitSurface(point,NULL,surf,&position);

	}

}

bool Graph::insertPoint(Point p){

	Points.push_back(p);

	return true;
}
