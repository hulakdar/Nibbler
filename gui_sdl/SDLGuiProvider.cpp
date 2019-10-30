#include "SDLGuiProvider.h"

extern "C" {
	IGuiProvider *GetProvider() {
		static SDLGuiProvider lib;
		return &lib;
	}
}

bool SDLGuiProvider::Init(IVec2 WindowSize, const char *WindowName) {
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