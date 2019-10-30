#include "SDLGuiProvider.h"
#include <iostream>

extern "C" {
	IGuiProvider *GetProvider() {
		static SDLGuiProvider lib;
		return &lib;
	}
}

SDL_Texture* SDLGuiProvider::loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( Renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

void put_error(std::string err) {
	std::cout << err << std::endl;
}

bool SDLGuiProvider::Init(IVec2 WindowSize, const char *WindowName) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK) < 0)
	{
		put_error(SDL_GetError());
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
		put_error(SDL_GetError());
	
	Window = SDL_CreateWindow(WindowName,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WindowSize.x, WindowSize.y, SDL_WINDOW_SHOWN);
	if (!Window)
	{
		put_error(SDL_GetError());
		return false;
	}
	SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1");
	// WindowSurface = SDL_GetWindowSurface(Window);
	Renderer = SDL_CreateRenderer( Window, -1, SDL_RENDERER_ACCELERATED );
	if (!Renderer)
	{
		put_error(SDL_GetError());
		return false;
	}
	

	for (short i = 0; i < 255; i++) {
		keyStates[i] = false;
	}
    return true;
}
bool SDLGuiProvider::LoadImage(const char *FilePath) {
    SDL_Surface* surface = IMG_Load( FilePath );
    if (!surface) {
        printf("Unable to load image %s! SDL_image Error: %s\n", FilePath, IMG_GetError());
		return false;
    }
	Texture = SDL_CreateTextureFromSurface( Renderer, surface );
	if (!Texture) {
		printf("Unable to create texture from %s! SDL Error: %s\n", FilePath, SDL_GetError());
		return false;
	}
    SDL_FreeSurface(surface);
	return true;
}
bool SDLGuiProvider::IsKeyDown(EKey K) {
	switch (K)
	{
	case EKey1:
		return keyStates[SDL_SCANCODE_1];
	case EKey2:
		return keyStates[SDL_SCANCODE_2];
	case EKey3:
		return keyStates[SDL_SCANCODE_3];
	case EKeySPACE:
		return keyStates[SDL_SCANCODE_SPACE];
	case EKeyUP:
		return keyStates[SDL_SCANCODE_UP];
	case EKeyDOWN:
		return keyStates[SDL_SCANCODE_DOWN];
	case EKeyLEFT:
		return keyStates[SDL_SCANCODE_LEFT];
	case EKeyRIGHT:
		return keyStates[SDL_SCANCODE_RIGHT];
	case EKeyESC:
		return keyStates[SDL_SCANCODE_ESCAPE];
	default:
		break;
	}
    return false;
}
bool SDLGuiProvider::ShouldExit() {
	return RequestingExit;
}
void SDLGuiProvider::Tick() {
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN
			&& e.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			RequestingExit = true;
		else if (e.type == SDL_KEYDOWN)
			keyStates[e.key.keysym.scancode] = true;
		else if (e.type == SDL_KEYUP)
			keyStates[e.key.keysym.scancode] = false;
	}
}
void SDLGuiProvider::FillBackground(Color C) {
	// SDL_FillRect(WindowSurface, NULL, SDL_MapRGB(WindowSurface->format, C.r, C.g, C.b));
}
void SDLGuiProvider::DrawRectangle(FVec2 Origin, FVec2 Size, Color C) {
	// SDL_Rect rect {(int)Origin.x, (int)Origin.y, (int)Size.x, (int)Size.y};
	// SDL_FillRect(WindowSurface, &rect, SDL_MapRGB(WindowSurface->format, C.r, C.g, C.b));
}
void SDLGuiProvider::DrawImage(FVec2 Origin, FVec2 Size, struct Image *I) {
	SDL_RenderClear(Renderer);
	SDL_Rect rect {(int)Origin.x, (int)Origin.y, (int)Size.x, (int)Size.y};
	SDL_RenderCopy( Renderer, Texture, NULL, &rect );
 
    // for ( const auto &p : enemies )
    //     SDL_RenderCopy( Renderer, enemyTexture, NULL, &p.pos );
}
void SDLGuiProvider::DrawText(FVec2 Origin, const char* Text, Color C) {
}
void SDLGuiProvider::EndFrame() {
	SDL_UpdateWindowSurface(Window);
	SDL_RenderPresent(Renderer);
}
void SDLGuiProvider::Deinit() {
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyTexture(Texture);
    SDL_DestroyWindow(Window);
	SDL_Quit();
}
SDLGuiProvider::~SDLGuiProvider() {
}