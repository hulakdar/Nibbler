#include "SigilGuiProvider.h"
#include <sl.h>

extern "C" {
	IGuiProvider *GetProvider() {
		static SigilGuiProvider lib;
		return &lib;
	}
}

bool SigilGuiProvider::Init(IVec2 WindowSize, const char *WindowName) {
	slWindow(WindowSize.x, WindowSize.y, WindowName, 0);
	slSetBackColor(0.0, 0.0, 0.0);
	slSetAdditiveBlend(false);
    return true;
}

bool SigilGuiProvider::LoadImage(const char *ImagePath) {
	Texture = slLoadTexture(ImagePath);
	return (true);
}

bool SigilGuiProvider::LoadFont(const char *FontPath) {
	Font = slLoadFont(FontPath);
	StartFont = slLoadFont(FontPath);
	// EndFont = slLoadFont(FontPath);
	return true;
}

bool SigilGuiProvider::IsKeyDown(EKey K) {
	switch (K)
	{
	case EKey1:
		return slGetKey(49);
	case EKey2:
		return slGetKey(50);
	case EKey3:
		return slGetKey(51);
	case EKeySPACE:
		return slGetKey(32);
	case EKeyUP:
		return slGetKey(265);
	case EKeyDOWN:
		return slGetKey(264);
	case EKeyLEFT:
		return slGetKey(263);
	case EKeyRIGHT:
		return slGetKey(262);
	case EKeyESC:
		return slGetKey(256);
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
	slSetForeColor(C.x / 255.f, C.y / 255.f, C.z / 255.f, 1);
	slRectangleFill(Origin.x + Size.x / 2, Origin.y + Size.y / 2, Size.x, Size.y);
}
void SigilGuiProvider::DrawImage(FVec2 Origin, FVec2 Size) {
	slSetForeColor(1.0, 1.0, 1.0, 1.0);
	slSprite(Texture, Origin.x + Size.x / 2, Origin.y + Size.y / 2, Size.x, Size.y);
}
void SigilGuiProvider::DrawText(FVec2 Origin, const char* Text, Color C) {
	slSetFont(Font, 80);
	slSetTextAlign(SL_ALIGN_LEFT);
	slPush();
	slScale(1, -1);
	slText(Origin.x, -Origin.y - slGetTextHeight(Text), Text);
	slPop();
}
void SigilGuiProvider::DrawStartScreen() {
	slSetForeColor(1.0, 1.0, 1.0, 1.0);
	slSetFont(StartFont, 40);
	slSetTextAlign(SL_ALIGN_CENTER);
	slPush();
	slScale(1, -1);
	slText(400, -400 - slGetTextHeight("Press space to play"), "Press space to play");
	slPop();
}

void SigilGuiProvider::DrawEndScreen() {
	slSetForeColor(1.0, 1.0, 1.0, 1.0);
	slSetFont(EndFont, 40);
	slSetTextAlign(SL_ALIGN_CENTER);
	slPush();
	slScale(1, -1);
	slText(400, -400 - slGetTextHeight("You lose"), "You lose");
	slPop();
}

void SigilGuiProvider::EndFrame() {
	slRender();
}
void SigilGuiProvider::Deinit() {
	slClose();
}
SigilGuiProvider::~SigilGuiProvider() {
}