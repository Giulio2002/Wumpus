#include "../include/Wumpus.h"
#include "../include/graph.h"

#define HEIGHT 400

#define WIDTH 700

#define YBASE 349

#define XBASE 26

#define BLOCKDISTANCE 51

#define NTIMES 50

#define MIN 40

#include <ctime>

void listenEvent(){
	SDL_Event e;
	for (;;) {
	    SDL_PollEvent(&e);
	    if (e.type == SDL_QUIT) {
	        SDL_Log("Il programma e' stato killato dopo %i ticks", e.quit.timestamp);
	        exit(1);
	        break;
	    }
	}
}

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface *surf = NULL;
	SDL_Window *window = NULL;
    window = SDL_CreateWindow(
        "Wumpus Graph",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
        SDL_WINDOW_OPENGL
    );
	SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,0);

    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    Graph graph;
    std::thread t(listenEvent);
    Point p;

    Map map(1,1);

	for(int i = MIN;i<NTIMES;i++){


		SDL_RenderClear(renderer);
		surf = SDL_GetWindowSurface(window);

		graph.displayGraph(surf);

		SDL_RenderPresent(renderer);

		SDL_UpdateWindowSurface(window);


		std::cout << "Test "<< i - (MIN-1) <<std::endl;

		map.setxDim(i);

		map.setyDim(i);

		Wumpus wumpus(map);

		int start_s=clock();

		wumpus.elaborateStrategy(map);

		int stop_s=clock();

		std::cout << "Time Lapse: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1<< std::endl;

		p.x = XBASE + (( i -(MIN-1)-1) * BLOCKDISTANCE);

		p.y = YBASE + (int)(((stop_s-start_s)/double(CLOCKS_PER_SEC)*1) * -BLOCKDISTANCE);

		graph.insertPoint(p);

	}

	SDL_Delay(999999);


}
