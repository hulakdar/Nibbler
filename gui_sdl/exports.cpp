#include <SDL.h>

extern "C" {
	void *library_ptr()
	{
		SDL_Init(SDL_INIT_VIDEO);
		SDL_Window *window = SDL_CreateWindow("nibbler", 640, 640, 0, 0, 0);
		SDL_Event e;

		static void *lib = (void*)42ULL;
		return lib;
	}
}
