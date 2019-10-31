#include "SDLGuiProvider.h"
#include <iostream>

extern "C" {
	IGuiProvider *GetProvider() {
		static SDLGuiProvider lib;
		return &lib;
	}
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
	Renderer = SDL_CreateRenderer( Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

Image *SDLGuiProvider::LoadImage(const char *FilePath) {
	SDL_SetHint("SDL_HINT_RENDER_SCALE_QUALITY", 0);
    SDL_Surface* surface = IMG_Load( FilePath );
    if (!surface) {
        printf("Unable to load image %s! SDL_image Error: %s\n", FilePath, IMG_GetError());
		return nullptr;
    }
	SDL_Texture *Texture = SDL_CreateTextureFromSurface( Renderer, surface );
	if (!Texture) {
		printf("Unable to create texture from %s! SDL Error: %s\n", FilePath, SDL_GetError());
		return nullptr;
	}
    SDL_FreeSurface(surface);
	return (Image*)Texture;
}

bool SDLGuiProvider::LoadFont(const char *FontPath) {
	Font = TTF_OpenFont(FontPath, 12);
	return Font != nullptr;
}

void SDLGuiProvider::FreeImage(Image *Image)
{
	SDL_DestroyTexture((SDL_Texture*)Image);
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
	SDL_SetRenderDrawColor(Renderer, C.r, C.g, C.b, C.a);
	SDL_RenderClear(Renderer);
}
void SDLGuiProvider::DrawRectangle(FVec2 Origin, FVec2 Size, Color C) {
	SDL_SetRenderDrawColor(Renderer, C.r, C.g, C.b, C.a);
	SDL_Rect rect {(int)Origin.x, (int)Origin.y, (int)Size.x, (int)Size.y};
	SDL_RenderFillRect(Renderer, &rect);
}
void SDLGuiProvider::DrawImage(FVec2 Origin, FVec2 Size, Image *I) {
	SDL_Rect rect {(int)Origin.x, (int)Origin.y, (int)Size.x, (int)Size.y};
	SDL_RenderCopy(Renderer, (SDL_Texture *)I, NULL, &rect);
}
void SDLGuiProvider::DrawText(FVec2 Origin, const char* Text, Color C) {
}
void SDLGuiProvider::EndFrame() {
	SDL_RenderPresent(Renderer);
}
void SDLGuiProvider::Deinit() {
	TTF_CloseFont(Font);
	IMG_Quit();
	SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
	SDL_Quit();
}
SDLGuiProvider::~SDLGuiProvider() {
}