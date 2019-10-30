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
	exit(-1);
}

bool SDLGuiProvider::Init(IVec2 WindowSize, const char *WindowName) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK) < 0)
		put_error(SDL_GetError());
	// if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
	// 	put_error(SDL_GetError());
	// if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	// 	put_error(SDL_GetError());
	// if (TTF_Init() < 0)
	// 	put_error(SDL_GetError());
	Window = SDL_CreateWindow(WindowName,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WindowSize.x, WindowSize.y, SDL_WINDOW_SHOWN);
	if (!Window)
		put_error(SDL_GetError());
    return true;
}
bool SDLGuiProvider::IsKeyDown(EKey K) {
    return false;
}
bool SDLGuiProvider::ShouldExit() {
    return false;
}
void SDLGuiProvider::Tick() {
}
void SDLGuiProvider::FillBackground(Color C) {
}
void SDLGuiProvider::DrawRectangle(FVec2 Origin, FVec2 Size, Color C) {
}
void SDLGuiProvider::DrawImage(FVec2 Origin, FVec2 Size, struct Image *I) {
}
void SDLGuiProvider::DrawText(FVec2 Origin, const char* Text, Color C) {
}
void SDLGuiProvider::EndFrame() {
}
void SDLGuiProvider::Deinit() {
}
SDLGuiProvider::~SDLGuiProvider() {
}