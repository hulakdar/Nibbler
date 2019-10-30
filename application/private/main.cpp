#include <cstdio>
#include <dlfcn.h>

#include "GuiProvider.h"

constexpr IVec2 FieldSize	{20, 20};
constexpr IVec2 FieldCenter = FieldSize / 2;

enum EDirection
{
	EDirUP,
	EDirRIGHT,
	EDirDOWN,
	EDirLEFT,
};

struct Snake
{
	IVec2		Body[FieldSize.x * FieldSize.y] = {
		FieldCenter,
		FieldCenter + IVec2{0, 1},
		FieldCenter + IVec2{0, 2},
		FieldCenter + IVec2{0, 3},
		{0,0}
		};
	uint8_t		Length = 4;
	EDirection	Direction = EDirUP;
};

IVec2 RandomLocation()
{
	return glm::abs(IVec2{rand(), rand()}) % FieldSize;
}

int main(int argc, char **argv)
{
	const char *libs[EBackendCOUNT] = {
		"libgui_sfml.dylib",
		"libgui_sdl.dylib",
		"libgui_allegro.dylib",
	};
	EBackend currentBackend = EBackendCOUNT;
	EBackend wantedBackend = EBackendSDL;

	IGuiProvider *Gui = nullptr;
	void *lib = nullptr;

	auto cleanup = [&Gui, &lib] () {
		if (Gui)
		{
			Gui->Deinit();
		}
		if (lib)
		{
			dlclose(lib);
		}
	};

	IVec2 CurrentWindowSize {800, 800};

	Snake S;
	IVec2 Fruit = RandomLocation();

	float timer = 0;
	while (true)
	{
		IVec2 BlockSize = CurrentWindowSize / FieldSize;
		if (currentBackend != wantedBackend)
		{
			cleanup();

			lib = dlopen(libs[wantedBackend], 0);
			if (!lib)
				break;
			ProviderGetter GetGui = (ProviderGetter)dlsym(lib, "GetProvider");
			if (!GetGui)
				break;
			Gui = GetGui();
			if (!Gui)
				break;
			if (!Gui->Init(CurrentWindowSize, "Nibbler"))
				break;
			currentBackend = wantedBackend;
		}
		else
		{
			Gui->Tick();
			if (Gui->IsKeyDown(EKeyUP))
				S.Direction = EDirUP;
			else if (Gui->IsKeyDown(EKeyRIGHT))
				S.Direction = EDirRIGHT;
			else if (Gui->IsKeyDown(EKeyDOWN))
				S.Direction = EDirDOWN;
			else if (Gui->IsKeyDown(EKeyLEFT))
				S.Direction = EDirLEFT;

			if (timer > 0.33f)
			{
				// Move whole body 1 block.
				for (uint8_t i = S.Length; i > 0; i--)
					S.Body[i] = S.Body[i - 1];
				// Move head
				switch (S.Direction)
				{
				case EDirUP:
					S.Body[0].y -= 1;
					break;
				case EDirDOWN:
					S.Body[0].y += 1;
					break;
				case EDirRIGHT:
					S.Body[0].x += 1;
					break;
				case EDirLEFT:
					S.Body[0].x -= 1;
					break;
				default:
					break;
				}
				// wrap around
				if (S.Body[0].x < 0)
					S.Body[0].x += FieldSize.x;
				if (S.Body[0].y < 0)
					S.Body[0].y += FieldSize.y;
				S.Body[0] %= FieldSize;
				// Eat fruit
				if (S.Body[0] == Fruit)
				{
					S.Length++;
					Fruit = RandomLocation();
				}
				timer -= 0.25f;
			}
			// Draw background
			Gui->FillBackground({100, 100, 10, 255});
			// Draw snake head
			Gui->DrawRectangle(S.Body[0] * BlockSize, BlockSize, ColorGrey);
			// Draw snake body
			for (uint8_t i = 1; i < S.Length; i++)
				Gui->DrawRectangle(S.Body[i] * BlockSize, BlockSize, (i & 1) ? ColorGreen : ColorYellow);
			Gui->DrawRectangle(Fruit * BlockSize, BlockSize, ColorRed);
			Gui->EndFrame();
			if (Gui->ShouldExit() || Gui->IsKeyDown(EKeyESC))
				break;
			timer += 0.016f;
		}
	}
	cleanup();
	return 0;
}
