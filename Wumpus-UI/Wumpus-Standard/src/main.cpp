#include "../include/Wumpus.h"

int ch = 9999;

void listenEvent(){
	SDL_Event e;
	for (;;) {
	    SDL_PollEvent(&e);
	    if (e.type == SDL_QUIT) {

	    	SDL_Log("Il programma e' stato killato dopo %i ticks", e.quit.timestamp);

	    	exit(1);

	    }else if(e.type == SDL_KEYDOWN){
	    	switch(e.key.keysym.sym){

				case SDLK_w:
					ch = 97;
					usleep(100);
					break;
				case SDLK_s:
					ch = 100;
					usleep(100);
					break;
				case SDLK_a:
					ch = 119;
					usleep(100);
					break;
				case SDLK_d:
					ch = 115;
					usleep(100);
					break;
				default:
					ch = 9999;
	    	}
	    }
		ch = 9999;
	}
}

int main(){
	std::thread t1(listenEvent);
	SDL_Window *win = SDL_CreateWindow(
	        "Wumpus Graph",
	        SDL_WINDOWPOS_UNDEFINED,
	        SDL_WINDOWPOS_UNDEFINED,
			MAPSIZE,
			MAPSIZE,
	        SDL_WINDOW_OPENGL
	    );
	SDL_Surface *mainsurf = SDL_GetWindowSurface(win);
	SDL_Renderer *renderer = SDL_CreateRenderer(win,-1,0);

	Map map(10,10);
	Wumpus wumpus(map);
	bool isPlaying = true;

	while(isPlaying){
		update:
		wumpus.Update(map);
		wumpus.wantToMove(map,ch);
		mainsurf = SDL_GetWindowSurface(win);
		mainsurf = SDL_GetWindowSurface(win);
		SDL_UpdateWindowSurface(win);

		SDL_RenderClear(renderer);
		mainsurf = SDL_GetWindowSurface(win);



		SDL_UpdateWindowSurface(win);

		map.DisplayMap(mainsurf);

	}
	return 1;
}
