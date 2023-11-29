
#include "Predef.h"
#include <SDL.h>
//#include <SDL_image.h>
#include <SDL_timer.h>
#include <functional>

#include "Logic.h"

#pragma comment (lib,"SDL2.lib")
#pragma comment (lib,"SDL2main.lib")




Logic lifelogic;


int main(int argc, char* argv[])
{
	srand((unsigned int)time(NULL));
	lifelogic.initlogic();

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow(AppName,
		300, 300,
		//SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_XSIZE, SCREEN_YSIZE, SDL_WINDOW_RESIZABLE);
	//SDL_WINDOW_RESIZABLE);

	SDL_Renderer* sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	SDL_RenderSetLogicalSize(sdl_renderer, SCREEN_XSIZE, SCREEN_YSIZE);
	SDL_RenderSetIntegerScale(sdl_renderer, SDL_TRUE);

	SDL_Texture* screen_texture = SDL_CreateTexture(sdl_renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		SCREEN_XSIZE, SCREEN_YSIZE);


	while (1)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) exit(0);

			switch (event.type)
			{
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_UP:
						break;

					case SDLK_DOWN:
						break;

					case SDLK_LEFT:
						lifelogic.placeTreasure();
						break;

					case SDLK_RIGHT:
						break;

					case SDLK_SPACE:
						lifelogic.stepsimul();
						break;
					}
					break;
				}
		}

		SDL_RenderClear(sdl_renderer);
		int *surface = lifelogic.getbuffer();
		if(surface != NULL)
			SDL_UpdateTexture(screen_texture, NULL, surface, SCREEN_XSIZE * 4);
		SDL_RenderCopy(sdl_renderer, screen_texture, NULL, NULL);
		SDL_RenderPresent(sdl_renderer);


	}



	return  0;
}
