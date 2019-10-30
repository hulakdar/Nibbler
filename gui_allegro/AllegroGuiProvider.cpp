#include "AllegroGuiProvider.h"

extern "C" {
	IGuiProvider *GetProvider() {
		static AllegroGuiProvider lib;
		return &lib;
	}
}

bool AllegroGuiProvider::Init(IVec2 WindowSize, const char *WindowName) {
    return true;
}
bool AllegroGuiProvider::IsKeyDown(EKey K) {
    return false;
}
bool AllegroGuiProvider::ShouldExit() {
    return false;
}
void AllegroGuiProvider::Tick() {
}
void AllegroGuiProvider::FillBackground(Color C) {
}
void AllegroGuiProvider::DrawRectangle(FVec2 Origin, FVec2 Size, Color C) {
}
void AllegroGuiProvider::DrawImage(FVec2 Origin, FVec2 Size, struct Image *I) {
}
void AllegroGuiProvider::DrawText(FVec2 Origin, const char* Text, Color C) {
}
void AllegroGuiProvider::EndFrame() {
}
void AllegroGuiProvider::Deinit() {
}
AllegroGuiProvider::~AllegroGuiProvider() {
}