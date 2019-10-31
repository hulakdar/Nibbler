#include "SigilGuiProvider.h"
#include <sl.h>
#include <string>

extern "C" {
	IGuiProvider *GetProvider() {
		static SigilGuiProvider lib;
		return &lib;
	}
}

bool SigilGuiProvider::Init(IVec2 WindowSize, const char *WindowName) {
	std::string FinalName = WindowName;
	FinalName += ", SIGIL";
	slWindow(WindowSize.x, WindowSize.y, FinalName.c_str(), 0);
	slSetBackColor(0.0, 0.0, 0.0);
	slSetAdditiveBlend(false);
    return true;
}

Image *SigilGuiProvider::LoadImage(const char *ImagePath) {
    int Texture;
	Texture = slLoadTexture(ImagePath);
	return (Image *)(size_t)Texture;
}

bool SigilGuiProvider::LoadFont(const char *FontPath) {
	int font = slLoadFont(FontPath);
	slSetFont(font, 80);
	slSetTextAlign(SL_ALIGN_LEFT);
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
void SigilGuiProvider::FreeImage(Image *I) {

}
void SigilGuiProvider::DrawImage(FVec2 Origin, FVec2 Size, Image *I) {
    int Texture = (size_t)I;
	slSetForeColor(1.0, 1.0, 1.0, 1.0);
	slSprite(Texture, Origin.x + Size.x / 2, Origin.y + Size.y / 2, Size.x, Size.y);
}
void SigilGuiProvider::DrawText(FVec2 Origin, const char* Text, Color C) {
	slPush();
	slScale(1, -1);
	slText(Origin.x, -Origin.y - slGetTextHeight(Text), Text);
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