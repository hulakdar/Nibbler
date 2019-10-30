#include <cstdio>
#include <dlfcn.h>

#include "GuiProvider.h"


int main(int argc, char **argv)
{
	const char *libs[EBackendCOUNT] = {
		"libgui_sfml.dylib",
		"libgui_sdl.dylib",
		"libgui_allegro.dylib",
	};
	EBackend currentBackend = EBackendCOUNT;
	EBackend wantedBackend = EBackendDefault;

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
	while (true)
	{
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
			Gui->FillBackground({100, 100, 10, 255});
			Gui->DrawRectangle({100, 100}, {100, 50}, {100, 0, 0, 255});
			Gui->EndFrame();
			if (Gui->ShouldExit())
				break;
		}
	}
	cleanup();
	return 0;
}
