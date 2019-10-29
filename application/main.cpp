#include <cstdio>
#include <dlfcn.h>

int main(int argc, char **argv)
{
	void *lib = dlopen("libgui_sdl.dylib", 0);
	void *(*func)(void) = (void *(*)(void))dlsym(lib, "library_ptr");

	if (func)
	{
		void *result = func();
		printf("lib: %p func:%p result: %i\n", lib, func, result);
	}
	else
	{
		printf("no func, sorry\n");
	}
	return 0;
}
