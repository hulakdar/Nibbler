#include "SigilGuiProvider.h"
#include <sl.h>

extern "C" {
	IGuiProvider *GetProvider() {
		static SigilGuiProvider lib;
		return &lib;
	}
}

bool SigilGuiProvider::Init(IVec2 WindowSize, const char *WindowName) {
	slWindow(WindowSize.x, WindowSize.y, "SIGIL Shapes Example", 0);
    return true;
}

bool SigilGuiProvider::LoadImage(const char *ImagePath) {
	return true;
}
bool SigilGuiProvider::IsKeyDown(EKey K) {
	switch (K)
	{
	// case EKey1:
	// 	return sf::Keyboard::isKeyPressed(sf::Keyboard::Num1);
	// case EKey2:
	// 	return sf::Keyboard::isKeyPressed(sf::Keyboard::Num2);
	// case EKey3:
	// 	return sf::Keyboard::isKeyPressed(sf::Keyboard::Num3);
	 case EKeySPACE:
	 	return slGetKey('W');
	// case EKeyUP:
	// 	return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	// case EKeyDOWN:
	// 	return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	// case EKeyLEFT:
	// 	return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	// case EKeyRIGHT:
	// 	return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	// case EKeyESC:
	// 	return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
	 default:
	 	break;
	}
    return false;
}
bool SigilGuiProvider::ShouldExit() {
    return slShouldClose();
}
void SigilGuiProvider::Tick() {
}
void SigilGuiProvider::FillBackground(Color C) {
	slSetBackColor(C.x / 255.f, C.y / 255.f, C.z / 255.f);
}
void SigilGuiProvider::DrawRectangle(FVec2 Origin, FVec2 Size, Color C) {
	slSetForeColor(0.5, 0.0, 0.0, 0.5);
	slRectangleFill(Origin.x, Origin.y, Size.x, Size.y);
}
void SigilGuiProvider::DrawImage(FVec2 Origin, FVec2 Size, struct Image *I) {
}
void SigilGuiProvider::DrawText(FVec2 Origin, const char* Text, Color C) {
}
void SigilGuiProvider::EndFrame() {
	slRender();
}
void SigilGuiProvider::Deinit() {
	slClose();
}
SigilGuiProvider::~SigilGuiProvider() {
}