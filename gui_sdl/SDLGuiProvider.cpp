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
	WindowSurface = SDL_GetWindowSurface(Window);

	for (short i = 0; i < 255; i++) {
		keyStates[i] = false;
	}
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
	SDL_FillRect(WindowSurface, NULL, SDL_MapRGB(WindowSurface->format, C.r, C.g, C.b));
}
void SDLGuiProvider::DrawRectangle(FVec2 Origin, FVec2 Size, Color C) {
	SDL_Rect rect {(int)Origin.x, (int)Origin.y, (int)Size.x, (int)Size.y};
	SDL_FillRect(WindowSurface, &rect, SDL_MapRGB(WindowSurface->format, C.r, C.g, C.b));
}
void SDLGuiProvider::DrawImage(FVec2 Origin, FVec2 Size, struct Image *I) {
}
void SDLGuiProvider::DrawText(FVec2 Origin, const char* Text, Color C) {
}
void SDLGuiProvider::EndFrame() {
	SDL_UpdateWindowSurface(Window);
}
void SDLGuiProvider::Deinit() {
}
SDLGuiProvider::~SDLGuiProvider() {
}