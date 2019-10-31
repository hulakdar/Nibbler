#include <cstdio>
#include <dlfcn.h>
#include <vector>
#include <string>

#include "GuiProvider.h"

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
	std::vector<IVec2> Body;
	uint8_t		Length = 4;
	EDirection	Direction = EDirUP;

	Snake (IVec2 FieldSize) : Body(FieldSize.x * FieldSize.y)
	{
		IVec2 FieldCenter = FieldSize / 2;
		Body[0] = FieldCenter;
		Body[1] = FieldCenter + IVec2{0, 1};
		Body[2] = FieldCenter + IVec2{0, 2};
		Body[3] = FieldCenter + IVec2{0, 3};
	}
};

IVec2 RandomLocation(Snake S, IVec2 FieldSize)
{
	IVec2 randomPlace = glm::abs(IVec2{rand(), rand()}) % FieldSize;
	bool fruitOverlapsBody;
	do {
		fruitOverlapsBody = false;
		for (auto & bodyPart : S.Body) {
			if (bodyPart == randomPlace) {
				randomPlace = glm::abs(IVec2{rand(), rand()}) % FieldSize;
				fruitOverlapsBody = true;
			}
		}
	} while (fruitOverlapsBody);
	return randomPlace;
}

IVec2 parseArgc(int argc, char **argv) {
	if (argc != 3) {
		printf("Usage: ./nibbler {width} {height}\n");
		exit(0);
	}
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);

	if (width < 10) {
		printf("Gameboard Width < 10\n");
		exit(0);
	}
	if (width > 30) {
		printf("Gameboard Width > 30\n");
		exit(0);
	}

	if (height < 10) {
		printf("Gameboard Height < 10\n");
		exit(0);
	}
	if (height > 30) {
		printf("Gameboard Width > 30\n");
		exit(0);
	}
	if (width != height) {
		printf("Gameboard Board is'nt round.\n");
		exit(0);
	}
	return {width, height};
}

int main(int argc, char **argv)
{
	const char *libs[EBackendCOUNT] = {
		"libgui_sfml.dylib",
		"libgui_sdl.dylib",
		"libgui_sigil.dylib",
	};
	EBackend CurrentBackend = EBackendCOUNT;
	EBackend WantedBackend = EBackendSigil;

	IGuiProvider	*Gui = nullptr;
	void			*lib = nullptr;
	// Image			*img = nullptr;

	auto cleanup = [&Gui, &lib]() {
		if (Gui)
		{
			// if (img)
			// {
			// 	Gui->FreeImage(img);
			// 	img = nullptr;
			// }
			Gui->Deinit();
			Gui = nullptr;
		}
		if (lib)
		{
			dlclose(lib);
			lib = nullptr;
		}
	};

	IVec2 CurrentWindowSize {800, 800};
	IVec2 FieldSize = parseArgc(argc, argv);

	Snake S(FieldSize);
	IVec2 Fruit = RandomLocation(S, FieldSize);

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
			{
				printf("Coudn't open library %s \n", libs[WantedBackend]);
				break;
			}
			ProviderGetter GetGui = (ProviderGetter)dlsym(lib, "GetProvider");
			if (!GetGui)
			{
				printf("Coudn't find function GetProvider \n");
				break;
			}
			Gui = GetGui();
			if (!Gui)
			{
				printf("Coudn't get entry point\n");
				break;
			}
			if (!Gui->Init(CurrentWindowSize, "Nibbler"))
			{
				printf("Coudn't Init lib\n");
				break;
			}
			if (!Gui->LoadImage("resources/slime_face_2.png")) {
				printf("Coudn't load image\n");
				break;
			}
			// if (!img)
			// {
			// 	printf("Coudn't load image\n");
			// 	break;
			// }
			if (!Gui->LoadFont("resources/future.ttf")) {
				printf("Coudn't load  font\n");
				break;
			}
			CurrentBackend = WantedBackend;
		}

		Gui->Tick();
		if (CurrentGameState == EAreYouReady)
		{	
			Gui->FillBackground({0, 100, 250, 255});
			if (Gui->IsKeyDown(EKeySPACE))
			{
				S = Snake(FieldSize);
				Fruit = RandomLocation(S, FieldSize);
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
				if (S.Body[0].x < 0 || S.Body[0].y < 0 || S.Body[0].x >= FieldSize.x || S.Body[0].y >= FieldSize.x)
					lose();
				// Eat fruit
				if (S.Body[0] == Fruit)
				{
					S.Length++;
					if (S.Length != FieldSize.x * FieldSize.y) {
						Fruit = RandomLocation(S, FieldSize);
					}
				}
				timer -= 0.25f;
			}
			// Draw background
			Gui->FillBackground({100, 100, 10, 255});
			// Draw snake head
			Gui->DrawImage(S.Body[0] * BlockSize, BlockSize);
			// Draw snake body
			for (uint8_t i = 1; i < S.Length; i++)
				Gui->DrawRectangle(S.Body[i] * BlockSize, BlockSize, (i & 1) ? ColorGreen : ColorYellow);
			Gui->DrawRectangle(Fruit * BlockSize, BlockSize, ColorRed);
			
			std::string score = "Score: ";
			score += std::to_string(S.Length - 3);
			Gui->DrawText({10,10}, score.c_str(), ColorRed);
		}
		Gui->EndFrame();
		if (Gui->ShouldExit() || Gui->IsKeyDown(EKeyESC))
			break;
		timer += 0.016f;

		if (Gui->IsKeyDown(EKey1))
			WantedBackend = EBackendSDL;
		else if (Gui->IsKeyDown(EKey2))
			WantedBackend = EBackendSFML;
		else if (Gui->IsKeyDown(EKey3))
			WantedBackend = EBackendSigil;
	}
	cleanup();
	return 0;
}
