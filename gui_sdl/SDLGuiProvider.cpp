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
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}
	if (TTF_Init() < 0) {
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;
	}

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

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

bool SDLGuiProvider::LoadImage(const char *FilePath) {
	SDL_SetHint("SDL_HINT_RENDER_SCALE_QUALITY", 0);
	std::string path = FilePath;
	replace(path, ".png", ".bmp");
    SDL_Surface* surface = SDL_LoadBMP( path.c_str() );
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

bool SDLGuiProvider::LoadFont(const char *FontPath) {
	Font = TTF_OpenFont(FontPath, 28);
	return Font != nullptr;
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
void SDLGuiProvider::DrawImage(FVec2 Origin, FVec2 Size) {
	SDL_Rect rect {(int)Origin.x, (int)Origin.y, (int)Size.x, (int)Size.y};
	SDL_RenderCopy(Renderer, Texture, NULL, &rect);
}
void SDLGuiProvider::DrawText(FVec2 Origin, const char* Text, Color C) {
	SDL_Surface *ResultingText = TTF_RenderText_Solid(Font, Text, (SDL_Color){C.x, C.y, C.z, C.a});
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Renderer, ResultingText);
	SDL_Rect rect = {(int)Origin.x, (int)Origin.y, (int)strlen(Text) * 20, 50};
	SDL_RenderCopy(Renderer, Message, NULL, &rect);
	SDL_FreeSurface(ResultingText);
	ResultingText = nullptr;
}
void SDLGuiProvider::DrawStartScreen() {
	DrawText({210, 400}, "Press space to play", ColorWhite);
}
void SDLGuiProvider::DrawEndScreen() {
	DrawText({330, 400}, "You lost", ColorWhite);
}
void SDLGuiProvider::EndFrame() {
	SDL_RenderPresent(Renderer);
}
void SDLGuiProvider::Deinit() {
	TTF_CloseFont(Font);
	SDL_DestroyTexture(Texture);
	SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
SDLGuiProvider::~SDLGuiProvider() {
}