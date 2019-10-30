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

enum EGameState
{
	EAreYouReady,
	EGameplay,
	EYouLose,
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

	auto cleanup = [&Gui, &lib]() {
		if (Gui)
		{
			Gui->Deinit();
		}
		if (lib)
		{
			dlclose(lib);
		}
	};

	IVec2 CurrentWindowSize{800, 800};

	Snake S;
	IVec2 Fruit = RandomLocation();

	float timer = 0;
	EGameState CurrentGameState = EAreYouReady;

	auto lose = [&timer, &CurrentGameState]() {
		timer = 0.f;
		CurrentGameState = EYouLose;
	};
	while (true)
	{
		IVec2 BlockSize = CurrentWindowSize / FieldSize;
		if (CurrentBackend != WantedBackend)
		{
			cleanup();

			lib = dlopen(libs[WantedBackend], 0);
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
			CurrentBackend = WantedBackend;
		}

		Gui->Tick();
		if (CurrentGameState == EAreYouReady)
		{
			Gui->FillBackground({0, 100, 250, 255});
			if (Gui->IsKeyDown(EKeySPACE))
			{
				S = Snake();
				Fruit = RandomLocation();
				CurrentGameState = EGameplay;
				timer = 0;
			}
		}
		else if (CurrentGameState == EYouLose)
		{
			Gui->FillBackground({50, 5, 10, 255});
			if (timer > 1.f)
				CurrentGameState = EAreYouReady;
		}
		else if (CurrentGameState == EGameplay)
		{
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
				// Where do you want to move?
				IVec2 NewHeadPosition;
				switch (S.Direction)
				{
				case EDirUP:
					NewHeadPosition = S.Body[0] - IVec2{0, 1};
					break;
				case EDirDOWN:
					NewHeadPosition = S.Body[0] + IVec2{0, 1};
					break;
				case EDirRIGHT:
					NewHeadPosition = S.Body[0] + IVec2{1, 0};
					break;
				case EDirLEFT:
					NewHeadPosition = S.Body[0] - IVec2{1, 0};
					break;
				default:
					break;
				}
				// You can't move back
				if (NewHeadPosition == S.Body[1])
					NewHeadPosition += (S.Body[0] - NewHeadPosition) * 2;
				// Move whole body 1 block.
				for (uint8_t i = S.Length; i > 0; i--)
					S.Body[i] = S.Body[i - 1];
				// Move head
				S.Body[0] = NewHeadPosition;
				// Eat self
				for (uint8_t i = 2; i < S.Length; i++)
					if (S.Body[0] == S.Body[i])
						lose();
				// Hit perimeter
				if (S.Body[0].x < 0 || S.Body[0].y < 0 || S.Body[0].x >= FieldSize.x || S.Body[0].y > FieldSize.x)
					lose();
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
		}
		Gui->EndFrame();
		if (Gui->ShouldExit() || Gui->IsKeyDown(EKeyESC))
			break;
		timer += 0.016f;

		if (Gui->IsKeyDown(EKey1))
			WantedBackend = EBackendSFML;
		else if (Gui->IsKeyDown(EKey1))
			WantedBackend = EBackendSDL;
		else if (Gui->IsKeyDown(EKey1))
			WantedBackend = EBackendAllegro;
	}
	cleanup();
	return 0;
}
